
#include "h747-led.h"

void LED_GPIO_Init(void)
{
    LED_GPIO_CLK_ENABLE();

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

void LED_RED_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOI, LED_RED_PIN);
}
void LED_RED_Reset(void)
{
    HAL_GPIO_WritePin(GPIOI, LED_RED_PIN, GPIO_PIN_RESET);
}
void LED_RED_Set(void)
{
    HAL_GPIO_WritePin(GPIOI, LED_RED_PIN, GPIO_PIN_SET);
}

void LED_BLUE_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOI, LED_BLUE_PIN);
}
void LED_BLUE_Reset(void)
{
    HAL_GPIO_WritePin(GPIOI, LED_BLUE_PIN, GPIO_PIN_RESET);
}
void LED_BLUE_Set(void)
{
    HAL_GPIO_WritePin(GPIOI, LED_BLUE_PIN, GPIO_PIN_SET);
}

void LED_GREEN_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOI, LED_GREEN_PIN);
}
void LED_GREEN_Reset(void)
{
    HAL_GPIO_WritePin(GPIOI, LED_GREEN_PIN, GPIO_PIN_RESET);
}
void LED_GREEN_Set(void)
{
    HAL_GPIO_WritePin(GPIOI, LED_GREEN_PIN, GPIO_PIN_SET);
}

void LED_ORANGE_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOI, LED_ORANGE_PIN);
}
void LED_ORANGE_Reset(void)
{
    HAL_GPIO_WritePin(GPIOI, LED_ORANGE_PIN, GPIO_PIN_RESET);
}
void LED_ORANGE_Set(void)
{
    HAL_GPIO_WritePin(GPIOI, LED_ORANGE_PIN, GPIO_PIN_SET);
}
