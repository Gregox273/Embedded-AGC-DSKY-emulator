/*
 * Raphael Taylor-Davies (CUSF) 2016
 * Modified by Gregory Brooks 2018/19
 */

#include <stdlib.h>
#include <math.h>  // for self-test
#include <machine/endian.h>
//#include "calibration/mpu9250_calibration.h"

#include "ch.h"
#include "mpu9250.h"
//#include "badthinghandler.h"
//#include "compilermacros.h"
#include "mpu9250-reg.h"
//#include "messaging.h"
#include <string.h>
//#include "spalaxconf.h"

static const uint32_t mpu9250_send_over_can_count = 1000;
static const uint32_t mpu9250_send_over_usb_count = 0; // Will send 1 in every 100 samples

//static binary_semaphore_t mpu9250_semaphore;

#define I2C_MST_DLY 10
#define MPU9250_SPID SPID2

//// LOW-LEVEL COMMUNICATION ////

// mpu9250_read_u8 reads a single byte value from an 8-bit MPU9250 register
static uint8_t mpu9250_read_u8(uint8_t addr);

// mpu9250_read_multiple reads a multi-byte register from the MPU9250 into a
// memory buffer. The buffer pointed to by buf should have at least num bytes
// available.
static void mpu9250_read_multiple(uint8_t addr, uint8_t* buf, int num);

// mpu9250_write_u8 writes a single byte into an 8-bit MPU9250 register.
static void mpu9250_write_u8(uint8_t addr, uint8_t val);

//// HIGH-LEVEL OPERATIONS ////

// mpu9250_read_accel_temp_gyro will grab all the sensor data and writes it to out which
// must point to a buffer of at least 10 uint16_t-s. The values written are:
// ACCEL_XOUT, ACCEL_YOUT, ACCEL_ZOUT, TEMP_OUT, GYRO_XOUT, GYRO_YOUT, GYRO_ZOUT
// MAGNO_XOUT, MAGNO_YOUT, MAGNO_ZOUT
static void mpu9250_read_accel_temp_gyro(uint16_t *out);

static const SPIConfig spi_cfg = {
    .end_cb = NULL,
    .ssline = LINE_NCS_MPU,
    // CPOL, CPHA, MSB First, 8-bit frame
    // Clock rate should be <= 1 MHz for burst mode
    // I believe this sets it to 168000000 / 4 / 64 ~= 1MHz
    // TODO: Verify this
    .cr1 = SPI_CR1_BR_0 | SPI_CR1_CPOL | SPI_CR1_CPHA
};

//// INTERNAL FUNCTIONS ////

// mpu9250_self_test_to_factory_trim takes self-test register values and
// transforms them to the corresponding factory trim values which should match
// the sensor readings. (It is assumed that the full-scale select is 00 ==
// +/-250 deg/sec.) It appears non-trivial to find the application note which
// describes the self-test procedure. This formula was lifted from [1].
//
// [1] https://github.com/kriswiner/MPU-9250/blob/master/MPU9250BasicAHRS.ino
//static inline uint16_t mpu9250_self_test_to_factory_trim(uint8_t st_val) {
//    return (uint16_t)(2620.f * powf(1.01f, ((float)st_val) - 1.f));
//}

static uint8_t mpu9250_read_u8(uint8_t addr) {
    uint8_t read_val;
    mpu9250_read_multiple(addr, &read_val, 1);
    return read_val;
}

static void mpu9250_read_multiple(uint8_t addr, uint8_t* buf, int num) {
    // Set the read bit
    addr |= (1 << 7);

    spiAcquireBus(&MPU9250_SPID);
    spiStart(&MPU9250_SPID, &spi_cfg);

    spiSelect(&MPU9250_SPID);
    spiSend(&MPU9250_SPID, 1, (void*)&addr);
    spiReceive(&MPU9250_SPID, (size_t) num, (void*)buf);
    spiUnselect(&MPU9250_SPID);

    spiReleaseBus(&MPU9250_SPID);
}

static void mpu9250_write_u8(uint8_t addr, uint8_t val) {
    // Clear the read bit
    addr &= ~(1 << 7);

    uint8_t tx_buff[2];
    tx_buff[0] = addr;
    tx_buff[1] = val;

    spiAcquireBus(&MPU9250_SPID);
    spiStart(&MPU9250_SPID, &spi_cfg);

    spiSelect(&MPU9250_SPID);
    spiSend(&MPU9250_SPID, 2, (void*)&tx_buff);
    spiUnselect(&MPU9250_SPID);

    spiReleaseBus(&MPU9250_SPID);
}

static void mpu9250_read_accel_temp_gyro(uint16_t *out) {
    // Cast output to uint8_t buffer
    uint8_t *out_u8 = (uint8_t*)out;

    // Read accel, temp and gyro.
    mpu9250_read_multiple(MPU9250_REG_ACCEL_XOUT_H, out_u8, 14);

    // Convert buffer to host endian-ness
#if BYTE_ORDER != BIG_ENDIAN
    for(int i=0; i<14; i+=2) {
        uint8_t tmp = out_u8[i];
        out_u8[i] = out_u8[i+1];
        out_u8[i+1] = tmp;
    }
#endif
}

static void mpu9250_read_magno(int16_t out[3]) {
    uint8_t buff[8];

    // This should be updated every I2C_MST_DLY samples automatically
    mpu9250_read_multiple(MPU9250_REG_EXT_SENS_DATA_00, buff, 8);

    memcpy(out, &buff[1],6);
}

static bool mpu9250_spi_id_check(void) {
    uint8_t whoami = mpu9250_read_u8(MPU9250_REG_WHO_AM_I);
    return whoami == MPU9250_WHO_AM_I_RESET_VALUE;
}

void mpu9250_init(void) {

    while (!mpu9250_spi_id_check()) {
	    chThdSleepMilliseconds(50);
    }

    ///
    // MPU9250 Setup
    ///

    // Register/value pairs to reset/initialise MPU9250
    uint8_t init_sequence[][2] = {
        { MPU9250_REG_PWR_MGMT_1, 0x80 }, // Reset
        { MPU9250_REG_PWR_MGMT_1, 0x01 }, // Select best clock source
        { MPU9250_REG_PWR_MGMT_2, 0x00 }, // Enable gyro & accel
        { MPU9250_REG_USER_CTRL,   0b00110010 }, // SPI only, disable FIFO, Enable the I2C Master Module
        { MPU9250_REG_INT_PIN_CFG, 0b00110000}, // Latch Interrupt and clear on read
        { MPU9250_REG_INT_ENABLE,  0b00000001}, // Enable interrupt on data ready
        { MPU9250_REG_I2C_MST_CTRL, 0b01011000}, // Set I2C clock rate to 400kHz, delay DRDY interrupt until External sensor data is ready
        { MPU9250_REG_I2C_MST_DELAY_CTRL, 0b00000001}, // Only sample Slave 0 every 1 + I2C_MST_DLY samples
        { MPU9250_REG_I2C_SLV4_CTRL, (I2C_MST_DLY & 0x1F)}, // Set I2C_MST_DLY
        { MPU9250_REG_SMPLRT_DIV, 0x0}, // Set Maximum Sample Rate



            // Set full gyro scale to +500dps
            // We enable a digital low pass filter with:
            // - bandwidth 184Hz on gyroscope
            // - bandwidth 188Hz on temperature
            // Note: this reduces ODR to 1 kHz and adds a 2.9ms delay
        { MPU9250_REG_CONFIG, 0b00000001}, // Disable FSync and set DLPF_CFG to 1
        { MPU9250_REG_GYRO_CONFIG, 0b00001000},

            // Set full accelerometer scale to +16g
            // Enable a 184Hz low pass filter on accelerometer
            // Note: this reduces ODR to 1kHz and adds a 5.8ms delay
        { MPU9250_REG_ACCEL_CONFIG, 0b00011000},
        { MPU9250_REG_ACCEL_CONFIG_2, 0b00000001}
    };

    // Perform initial reset
    for(size_t i=0; i < sizeof(init_sequence)/sizeof(init_sequence[0]); ++i) {
        mpu9250_write_u8(init_sequence[i][0], init_sequence[i][1]);
        chThdSleepMilliseconds(10);
    }

    ///
    // Magnetometer Setup
    ///

    // Reset Magnetometer
    mpu9250_write_u8(AK8963_REG_CNTL2, 0x01);

    // First set mode to power down
    mpu9250_write_u8(AK8963_REG_CNTL1, 0b00000000);
    // Then can set to continuous 16-bit measurement at 100Hz
    mpu9250_write_u8(AK8963_REG_CNTL1, 0b00010110);

    // Configure automatic magnetometer read
    mpu9250_write_u8(MPU9250_REG_I2C_SLV0_ADDR, AK893_I2C_ADDR | 0x80);
    mpu9250_write_u8(MPU9250_REG_I2C_SLV0_REG, AK8963_REG_ST1);
    mpu9250_write_u8(MPU9250_REG_I2C_SLV0_CTRL, 0b10001000); // Read 8 bytes (we must read ST1 and ST2)

    while (!mpu9250_spi_id_check()) {
        chThdSleepMilliseconds(50);
    }
}


void mpu9250_read(mpu9250_data_t *data) {
  mpu9250_read_accel_temp_gyro((uint16_t*)data);
  mpu9250_read_magno(data->magno);
}
