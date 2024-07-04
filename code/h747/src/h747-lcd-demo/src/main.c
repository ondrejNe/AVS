
#include "h747-lcd-demo.h"

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

//    // Initialize the LCD
//    BSP_LCD_Init();
//    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
//    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
//    BSP_LCD_DisplayOn();
//    BSP_LCD_Clear(LCD_COLOR_WHITE);  // Clear the screen with a white background
//
//    // Draw a rectangle
//    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//    BSP_LCD_FillRect(10, 10, 100, 50);  // Draw a blue rectangle

    // Main loop
    while (1)
    {
        HAL_Delay(500); // ms
        LED_RED_Toggle();
    }
}

