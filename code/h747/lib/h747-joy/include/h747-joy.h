
#ifndef B4M38AVS_CVUT_H747_JOY_H
#define B4M38AVS_CVUT_H747_JOY_H

#include "stm32h7xx_hal.h"

// Joystick peripheral definition
#define JOY_SEL_PIN                         GPIO_PIN_2 // EXTI2
#define JOY_DOWN_PIN                        GPIO_PIN_3 // EXTI3
#define JOY_LEFT_PIN                        GPIO_PIN_4 // EXTI4
#define JOY_RIGHT_PIN                       GPIO_PIN_5 // EXTI5 - IRQ9..5
#define JOY_UP_PIN                          GPIO_PIN_6 // EXTI6 - IRQ9..5
#define JOY_ALL_PIN                         GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6

#define JOY_GPIO_PORT                       GPIOK
#define JOY_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOK_CLK_ENABLE()
#define JOY_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOK_CLK_DISABLE()

#define JOY_SEL_EXTI_IRQn                   EXTI2_IRQn
#define JOY_DOWN_EXTI_IRQn                  EXTI3_IRQn
#define JOY_LEFT_EXTI_IRQn                  EXTI4_IRQn
#define JOY_RIGHT_EXTI_IRQn                 EXTI9_5_IRQn
#define JOY_UP_EXTI_IRQn                    EXTI9_5_IRQn

#endif //B4M38AVS_CVUT_H747_JOY_H
