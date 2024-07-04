
#include "h747-button.h"

void BUTTON_WAKE_UP_NVIC_init(void);
void BUTTON_WAKEUP_EXTI_Callback(void);

void BUTTON_WAKE_UP_GPIO_init(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // Setup interrupt
    BUTTON_WAKE_UP_NVIC_init();
}

void BUTTON_WAKE_UP_NVIC_init(void)
{
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void) {

    BUTTON_WAKEUP_EXTI_Callback();
}

void BUTTON_WAKEUP_EXTI_Callback(void)
{
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
}
