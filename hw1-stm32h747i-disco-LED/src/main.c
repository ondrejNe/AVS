
#include "internal.h"
#include "periphery.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}

int main(void)
{
    // Reset of all peripherals, Initializes the Flash interface and the Systick.
    HAL_Init();
    // Systems clocks init
    SystemClock_Config();
    // LED GPIO init
    LED_GPIO_init();
    // TIM6 HW timer init
    TIM6_init(LED_ORANGE_Toggle);
    // Joystick
    JOYSTICK_GPIO_init();
    // Wake up button
    BUTTON_WAKE_UP_GPIO_init();

    while (1)
    {
        HAL_Delay(2000); // ms
        LED_GREEN_Toggle();
    }
}
