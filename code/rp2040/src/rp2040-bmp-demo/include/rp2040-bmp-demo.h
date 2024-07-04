
#ifndef B4M38AVS_CVUT_RP2040_BMP_DEMO_H
#define B4M38AVS_CVUT_RP2040_BMP_DEMO_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#include "bmp3.h"
#include "bmp3_defs.h"
#include "bmp3_config.h"
#include "bmp3_common.h"

#include "rp2040_time.h"

#define FREQUENCY           1
#define FREQUENCY_MILLIS    (1000 / FREQUENCY)

int bmp388_setup(struct bmp3_dev *bmp388);

#endif //B4M38AVS_CVUT_RP2040_BMP_DEMO_H
