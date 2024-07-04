
#ifndef B4M38AVS_CVUT_BMP3_CONFIG_H
#define B4M38AVS_CVUT_BMP3_CONFIG_H

#include <string.h>
#include <stdlib.h>
#include "hardware/i2c.h"

/* CAN defines */
#define PIO_NUM 0
#define PIO_IRQ PIO0_IRQ_0_IRQn
#define SYS_CLOCK 125000000

#define BMP_INT_PIN         3

#define BMP_SDA_PIN         26
#define BMP_SCK_PIN         27

#define BMP_I2C             i2c1

#endif //B4M38AVS_CVUT_BMP3_CONFIG_H
