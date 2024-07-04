
#ifndef B4M38AVS_CVUT_H747_LED_H
#define B4M38AVS_CVUT_H747_LED_H


#include "stm32h7xx_hal.h"

#define LED_GPIO_PORT                       GPIOI
#define LED_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOI_CLK_ENABLE()
#define LED_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOI_CLK_DISABLE()

#define LED1_PIN                            GPIO_PIN_12
#define LED1_GPIO_PORT                      GPIOI
#define LED_GREEN_PIN                       LED1_PIN

#define LED2_PIN                            GPIO_PIN_13
#define LED2_GPIO_PORT                      GPIOI
#define LED_ORANGE_PIN                      LED2_PIN

#define LED3_PIN                            GPIO_PIN_14
#define LED3_GPIO_PORT                      GPIOI
#define LED_RED_PIN                         LED3_PIN

#define LED4_PIN                            GPIO_PIN_15
#define LED4_GPIO_PORT                      GPIOI
#define LED_BLUE_PIN                        LED4_PIN

void LED_GPIO_Init(void);

void LED_RED_Toggle(void);
void LED_RED_Reset(void);
void LED_RED_Set(void);

void LED_BLUE_Toggle(void);
void LED_BLUE_Reset(void);
void LED_BLUE_Set(void);

void LED_GREEN_Toggle(void);
void LED_GREEN_Reset(void);
void LED_GREEN_Set(void);

void LED_ORANGE_Toggle(void);
void LED_ORANGE_Reset(void);
void LED_ORANGE_Set(void);

#endif //B4M38AVS_CVUT_H747_LED_H
