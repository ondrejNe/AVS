
#include "h747-usart-demo.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
        LED_RED_Toggle();
        HAL_Delay(100);
    }
}

int main(void)
{
    // Initialize the HAL Library
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Initialize all configured peripherals (GPIO in this case)
    LED_GPIO_Init();

    UART_Init();

    // Main loop
    while (1)
    {
        HAL_Delay(2000); // ms
        LED_GREEN_Toggle();
        LED_RED_Toggle();
        printf("Hello World!\r\n");
    }
}

