#ifndef PERIPHERY_H
#define PERIPHERY_H

#include "stm32f1xx_hal.h"

/* LED custom API -------------------------------------------------------------------------- */
void LED_GPIO_init(void);

#define DECLARE_LED_FUNCTIONS(LED_COLOR) \
void LED_##LED_COLOR##_Toggle(void); \
void LED_##LED_COLOR##_Reset(void); \
void LED_##LED_COLOR##_Set(void);

DECLARE_LED_FUNCTIONS(RED)
DECLARE_LED_FUNCTIONS(BLUE)

#endif // PERIPHERY_H