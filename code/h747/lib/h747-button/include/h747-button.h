#ifndef H747_BUTTON_H
#define H747_BUTTON_H

#include "stm32h7xx_hal.h"

// Button peripheral definition
#define BUTTONn                             1

#define BUTTON_WAKEUP_PIN                   GPIO_PIN_13
#define BUTTON_WAKEUP_GPIO_PORT             GPIOC
#define BUTTON_WAKEUP_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()
#define BUTTON_WAKEUP_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOC_CLK_DISABLE()
#define BUTTON_WAKEUP_EXTI_LINE             EXTI_LINE_13
#define BUTTON_WAKEUP_EXTI_IRQn             EXTI15_10_IRQn

#endif //H747_BUTTON_H
