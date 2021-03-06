/*
 * Raphael Taylor-Davies (CUSF) 2016
 */
// mpu9250-reg.h contains human-readable name to register mapping for the
// MPU9250. It also contains useful constants for setting/interpreting those
// register contents.
#pragma once
#ifndef __MPU9250_REG_H__
#define __MPU9250_REG_H__

// MPU9250 registers
enum {
    // R/W registers unless noted otherwise

    MPU9250_REG_SELF_TEST_X_GYRO = 0,
    MPU9250_REG_SELF_TEST_Y_GYRO = 1,
    MPU9250_REG_SELF_TEST_Z_GYRO = 2,

    MPU9250_REG_SELF_TEST_X_ACCEL = 13,
    MPU9250_REG_SELF_TEST_Y_ACCEL = 14,
    MPU9250_REG_SELF_TEST_Z_ACCEL = 15,

    MPU9250_REG_XG_OFFSET_H = 19,
    MPU9250_REG_XG_OFFSET_L = 20,
    MPU9250_REG_YG_OFFSET_H = 21,
    MPU9250_REG_YG_OFFSET_L = 22,
    MPU9250_REG_ZG_OFFSET_H = 23,
    MPU9250_REG_ZG_OFFSET_L = 24,

    MPU9250_REG_SMPLRT_DIV = 25,

    MPU9250_REG_CONFIG = 26,
    MPU9250_REG_GYRO_CONFIG = 27,
    MPU9250_REG_ACCEL_CONFIG = 28,
    MPU9250_REG_ACCEL_CONFIG_2 = 29,
    MPU9250_REG_LP_ACCEL_ODR = 30,
    MPU9250_REG_WOM_THR = 31,

    MPU9250_REG_FIFO_EN = 35,

    MPU9250_REG_I2C_MST_CTRL = 36,
    MPU9250_REG_I2C_SLV0_ADDR = 37,
    MPU9250_REG_I2C_SLV0_REG = 38,
    MPU9250_REG_I2C_SLV0_CTRL = 39,
    MPU9250_REG_I2C_SLV1_ADDR = 40,
    MPU9250_REG_I2C_SLV1_REG = 41,
    MPU9250_REG_I2C_SLV1_CTRL = 42,
    MPU9250_REG_I2C_SLV2_ADDR = 43,
    MPU9250_REG_I2C_SLV2_REG = 44,
    MPU9250_REG_I2C_SLV2_CTRL = 45,
    MPU9250_REG_I2C_SLV3_ADDR = 46,
    MPU9250_REG_I2C_SLV3_REG = 47,
    MPU9250_REG_I2C_SLV3_CTRL = 48,
    MPU9250_REG_I2C_SLV4_ADDR = 49,
    MPU9250_REG_I2C_SLV4_REG = 50,
    MPU9250_REG_I2C_SLV4_DO = 51,
    MPU9250_REG_I2C_SLV4_CTRL = 52,
    MPU9250_REG_I2C_SLV4_DI = 53, // read-only

    MPU9250_REG_I2C_MST_STATUS = 54, // read-only

    MPU9250_REG_INT_PIN_CFG = 55,
    MPU9250_REG_INT_ENABLE = 56,
    MPU9250_REG_INT_STATUS = 58, // read-only

    // Read only output registers

    MPU9250_REG_ACCEL_XOUT_H = 59,
    MPU9250_REG_ACCEL_XOUT_L = 60,
    MPU9250_REG_ACCEL_YOUT_H = 61,
    MPU9250_REG_ACCEL_YOUT_L = 62,
    MPU9250_REG_ACCEL_ZOUT_H = 63,
    MPU9250_REG_ACCEL_ZOUT_L = 64,

    MPU9250_REG_TEMP_OUT_H = 65,
    MPU9250_REG_TEMP_OUT_L = 66,

    MPU9250_REG_GYRO_XOUT_H = 67,
    MPU9250_REG_GYRO_XOUT_L = 68,
    MPU9250_REG_GYRO_YOUT_H = 69,
    MPU9250_REG_GYRO_YOUT_L = 70,
    MPU9250_REG_GYRO_ZOUT_H = 71,
    MPU9250_REG_GYRO_ZOUT_L = 72,

    // EXT_SENS_... registers are all read-only
    MPU9250_REG_EXT_SENS_DATA_00 = 73,
    MPU9250_REG_EXT_SENS_DATA_01,
    MPU9250_REG_EXT_SENS_DATA_02,
    MPU9250_REG_EXT_SENS_DATA_03,
    MPU9250_REG_EXT_SENS_DATA_04,
    MPU9250_REG_EXT_SENS_DATA_05,
    MPU9250_REG_EXT_SENS_DATA_06,
    MPU9250_REG_EXT_SENS_DATA_07,
    MPU9250_REG_EXT_SENS_DATA_08,
    MPU9250_REG_EXT_SENS_DATA_09,
    MPU9250_REG_EXT_SENS_DATA_10,
    MPU9250_REG_EXT_SENS_DATA_11,
    MPU9250_REG_EXT_SENS_DATA_12,
    MPU9250_REG_EXT_SENS_DATA_13,
    MPU9250_REG_EXT_SENS_DATA_14,
    MPU9250_REG_EXT_SENS_DATA_15,
    MPU9250_REG_EXT_SENS_DATA_16,
    MPU9250_REG_EXT_SENS_DATA_17,
    MPU9250_REG_EXT_SENS_DATA_18,
    MPU9250_REG_EXT_SENS_DATA_19,
    MPU9250_REG_EXT_SENS_DATA_20,
    MPU9250_REG_EXT_SENS_DATA_21,
    MPU9250_REG_EXT_SENS_DATA_22,
    MPU9250_REG_EXT_SENS_DATA_23,

    MPU9250_REG_I2C_SLV0_DO = 99,
    MPU9250_REG_I2C_SLV1_DO,
    MPU9250_REG_I2C_SLV2_DO,
    MPU9250_REG_I2C_SLV3_DO,

    MPU9250_REG_I2C_MST_DELAY_CTRL = 103,

    // R/W again from here unless otherwise noted

    MPU9250_REG_SIGNAL_PATH_RESET = 104,
    MPU9250_REG_MOT_DETECT_CTRL = 105,
    MPU9250_REG_USER_CTRL = 106,
    MPU9250_REG_PWR_MGMT_1 = 107,
    MPU9250_REG_PWR_MGMT_2 = 108,

    MPU9250_REG_FIFO_COUNTH = 114,
    MPU9250_REG_FIFO_COUNTL = 115,
    MPU9250_REG_FIFO_R_W = 116,

    MPU9250_REG_WHO_AM_I = 117, // read-only

    MPU9250_REG_XA_OFFSET_H = 119,
    MPU9250_REG_XA_OFFSET_L = 120,
    MPU9250_REG_YA_OFFSET_H = 122,
    MPU9250_REG_YA_OFFSET_L = 123,
    MPU9250_REG_ZA_OFFSET_H = 125,
    MPU9250_REG_ZA_OFFSET_L = 126,
};

enum {
    AK8963_REG_WHO_AM_I = 0x00,
    AK8963_REG_INFO     = 0x01,
    AK8963_REG_ST1      = 0x02,
    AK8963_REG_XOUT_L	= 0x03,
    AK8963_REG_XOUT_H	= 0x04,
    AK8963_REG_YOUT_L	= 0x05,
    AK8963_REG_YOUT_H	= 0x06,
    AK8963_REG_ZOUT_L	= 0x07,
    AK8963_REG_ZOUT_H	= 0x08,
    AK8963_REG_ST2      = 0x09,
    AK8963_REG_CNTL1    = 0x0A,
    AK8963_REG_CNTL2    = 0x0A,
    AK8963_REG_ASTC     = 0x0C,
    AK8963_REG_I2CDIS   = 0x0F,
    AK8963_REG_ASAX     = 0x10,
    AK8963_REG_ASAY     = 0x11,
    AK8963_REG_ASAZ     = 0x12,
};

// MPU9250 reset values. All register have a reset value of 0x00 apart from the
// ones noted below.
#define MPU9250_DEFAULT_RESET_VALUE 0x00
#define MPU9250_PWR_MGMT_1_RESET_VALUE 0x01
#define MPU9250_WHO_AM_I_RESET_VALUE 0x71

// bytes_to_uint16 is a macro for taking a high and low byte value and forming a
// uint16_t value from them.
#define bytes_to_uint16(high, low) \
    ( (((uint16_t)(high)) << 8) | ((uint16_t)(low)) )

// bytes_to_int16 is a macro for taking a high and low byte value and forming a
// int16_t value from them.
#define bytes_to_int16(high, low) \
    ( (((int16_t)(high)) << 8) | ((int16_t)(low)) )

// The I2C address of the AK8963 embedded within the MPU9250.
#define AK893_I2C_ADDR 0x0c
#define AK893_WHO_AM_I_RESET_VALUE 0x48

#endif // __MPU9250_REG_H__
