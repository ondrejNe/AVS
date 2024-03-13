#include "periphery.h"

#define LEDn                             2

#define LED3_PIN                         GPIO_PIN_9           /* PC.09 */
#define LED3_GPIO_PORT                   GPIOC
#define LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()  
#define LED3_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()  

#define LED4_PIN                         GPIO_PIN_8           /* PC.08 */
#define LED4_GPIO_PORT                   GPIOC
#define LED4_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()  
#define LED4_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()  

/**
 * Sets LED GPIO pins
*/
void LED_GPIO_init(void) 
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // Set all to off
    LED_RED_Set();
    LED_BLUE_Set();
}

/**
 * Defines basic LED API control functions
*/
#define DEFINE_LED_FUNCTIONS(LED_COLOR, GPIO_PORT, GPIO_PIN) \
void LED_##LED_COLOR##_Toggle(void) { \
    HAL_GPIO_TogglePin(GPIO_PORT, GPIO_PIN); \
} \
void LED_##LED_COLOR##_Reset(void) { \
    HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, GPIO_PIN_RESET); \
} \
void LED_##LED_COLOR##_Set(void) { \
    HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, GPIO_PIN_SET); \
}

DEFINE_LED_FUNCTIONS(RED, GPIOC, LED3_PIN)
DEFINE_LED_FUNCTIONS(BLUE, GPIOC, LED4_PIN)
