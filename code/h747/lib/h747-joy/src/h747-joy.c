
#include "h747-joy.h"

/* Private declarations ------------------------------------------------------------------------ */
void JOYSTIC_NVIC_init(void);

/* Definitions --------------------------------------------------------------------------------- */
void JOYSTICK_GPIO_init(void)
{
    __HAL_RCC_GPIOK_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = JOY_ALL_PIN ;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

    HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

    // Setup interupts
    JOYSTIC_NVIC_init();
    // other methods
    // (void)HAL_EXTI_GetHandle(&hjoy_exti[joykey], JOY_EXTI_LINE[joykey]);
    // (void)HAL_EXTI_RegisterCallback(&hjoy_exti[joykey],  HAL_EXTI_COMMON_CB_ID, JoyCallback[joykey]);
}

/**
 * Setup 5 buttons of the Joystick for interrupt
*/
void JOYSTIC_NVIC_init(void)
{
    // Select
    HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    // Down
    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
    // Left
    HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
    // Right & UP
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

/**
 * Catch the external interrupt
*/
void EXTI2_IRQHandler(void) {

    HAL_GPIO_EXTI_IRQHandler(JOY_SEL_PIN);
}
void EXTI3_IRQHandler(void) {

    HAL_GPIO_EXTI_IRQHandler(JOY_DOWN_PIN);
}
void EXTI4_IRQHandler(void) {

    HAL_GPIO_EXTI_IRQHandler(JOY_LEFT_PIN);
}
void EXTI9_5_IRQHandler(void) {

    HAL_GPIO_EXTI_IRQHandler((JOY_RIGHT_PIN | JOY_UP_PIN));
}

/**
 * Handle the GPIO interrupt
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if ((GPIO_Pin & (JOY_ALL_PIN)) > 0) {
        // Handle the interrupt
    }
}
