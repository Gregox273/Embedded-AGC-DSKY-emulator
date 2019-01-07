/*
 * Raphael Taylor-Davies (CUSD) 2016
 */
#ifndef __MPU9250_H__
#define __MPU9250_H__

#include "ch.h"
#include "hal.h"

typedef struct mpu9250_data_t {
    int16_t accel[3];
    int16_t temp;
    int16_t gyro[3];
    int16_t magno[3];
} mpu9250_data_t;

void mpu9250_init(void);
void mpu9250_read(mpu9250_data_t *data);

#endif /* __MPU9250_H__ */
