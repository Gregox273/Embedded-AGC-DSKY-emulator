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

void mpu9250_thread(void *arg);

/* Interrupt callbacks for EXTI. */
void mpu9250_wakeup(void);//EXTDriver *extp, expchannel_t channel);

#endif /* __MPU9250_H__ */
