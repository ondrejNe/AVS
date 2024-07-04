
#ifndef B4M38AVS_CVUT_RP2040_BNO_DEMO_H
#define B4M38AVS_CVUT_RP2040_BNO_DEMO_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#include "bno055.h"
#include "bno055_common.h"
#include "bno055_config.h"

#include "rp2040_time.h"

#define FREQUENCY           1
#define FREQUENCY_MILLIS    (1000 / FREQUENCY)

struct bno055_all_float_s
{
    struct bno055_accel_float_t         accel;      /* Accelerometer data */
    struct bno055_mag_float_t           mag;        /* Magnetometer data */
    struct bno055_gyro_float_t          gyro;       /* Gyroscope data */
    struct bno055_euler_float_t         euler;      /* Euler angle data */
    struct bno055_linear_accel_float_t  lin_accel;  /* Linear acceleration data */
    struct bno055_gravity_float_t       grav_accel; /* Gravity acceleration data */
};

int bno055_setup(struct bno055_t *bno055);

#endif //B4M38AVS_CVUT_RP2040_BNO_DEMO_H
