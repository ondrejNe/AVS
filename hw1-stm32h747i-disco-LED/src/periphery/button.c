#include "periphery.h"
#include "stm32h7xx_hal_gpio.h"

#define BUTTON_WAKEUP_PIN                   GPIO_PIN_13
#define BUTTON_WAKEUP_GPIO_PORT             GPIOC
#define BUTTON_WAKEUP_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()
#define BUTTON_WAKEUP_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOC_CLK_DISABLE()
#define BUTTON_WAKEUP_EXTI_IRQn             EXTI15_10_IRQn
#define BUTTON_WAKEUP_EXTI_LINE             EXTI_LINE_13

/* Private declarations ------------------------------------------------------------------------ */
void BUTTON_WAKE_UP_NVIC_init(void);
void BUTTON_WAKEUP_EXTI_Callback(void);

/* Definitions --------------------------------------------------------------------------------- */
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

/**
 * Setup WAKE UP button for interrupt
*/
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
    LED_RED_Toggle();
}
