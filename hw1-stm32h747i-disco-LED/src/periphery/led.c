#include "periphery.h"

#define LED_PERIPHERY           GPIOI

#define LED_GPIO_GREEN_PIN      GPIO_PIN_12
#define LED_GPIO_ORANGE_PIN     GPIO_PIN_13
#define LED_GPIO_RED_PIN        GPIO_PIN_14
#define LED_GPIO_BLUE_PIN       GPIO_PIN_15

/**
 * Sets LED GPIO pins
*/
void LED_GPIO_init(void) 
{
    __HAL_RCC_GPIOI_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 ;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    // Set all to off
    LED_RED_Set();
    LED_BLUE_Set();
    LED_GREEN_Set();
    LED_ORANGE_Set();
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

DEFINE_LED_FUNCTIONS(RED, GPIOI, LED_GPIO_RED_PIN)
DEFINE_LED_FUNCTIONS(BLUE, GPIOI, LED_GPIO_BLUE_PIN)
DEFINE_LED_FUNCTIONS(GREEN, GPIOI, LED_GPIO_GREEN_PIN)
DEFINE_LED_FUNCTIONS(ORANGE, GPIOI, LED_GPIO_ORANGE_PIN)
