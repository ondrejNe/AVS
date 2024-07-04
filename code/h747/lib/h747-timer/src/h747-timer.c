
#include "h747-timer.h"

TIM_HandleTypeDef htim6;

__weak void_function htim6_tick_function = noop;

/* Private declarations ------------------------------------------------------------------------ */
void TIM6_NVIC_init(void);

/* Definitions --------------------------------------------------------------------------------- */
/**
 * Basic 16bit timer
 *
 * @param operation Function that should be performed upon timer tick
 * @periphery APB1
*/
void TIM6_init(void_function tick_function)
{
    // What should be performed
    htim6_tick_function = tick_function;

    __HAL_RCC_TIM6_CLK_ENABLE();

    htim6.Instance = TIM6;
    // 100 Mhz APB1 - Prescaler to downscale the clock to 10 kHz
    htim6.Init.Prescaler = 9999;
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
    // Auto-reload value to achieve a 1-second period
    htim6.Init.Period = 9999;
    htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    // Init & Start
    HAL_TIM_Base_Init(&htim6);
    HAL_TIM_Base_Start_IT(&htim6);

    // Setup interupt on the timer
    TIM6_NVIC_init();
}

/**
 * Setup the TIM6 interupt
*/
void TIM6_NVIC_init(void)
{
    // Set interrupt priority
    HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 5, 0);
    // Enable the TIM6 interrupt in the NVIC
    HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

/**
 * Catch the TIM6 interupt
*/
void TIM6_DAC_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim6);
}

/**
 * Handle the TIM6 interupt
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        htim6_tick_function();
    }
}