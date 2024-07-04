
#ifndef B4M38AVS_CVUT_BNO055_CONFIG_H
#define B4M38AVS_CVUT_BNO055_CONFIG_H

#include <string.h>
#include <stdlib.h>
#include "hardware/i2c.h"

/* CAN defines */
#define PIO_NUM 0
#define PIO_IRQ PIO0_IRQ_0_IRQn
#define SYS_CLOCK 125000000

#define BNO_INT_PIN         2

#define CAN_RX_PIN          4
#define CAN_TX_PIN          5

#define BNO_RST_PIN         6

#define BNO_SDA_PIN         26
#define BNO_SCK_PIN         27

#define BNO_I2C             i2c1

#endif //B4M38AVS_CVUT_BNO055_CONFIG_H
