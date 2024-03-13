#include "internal.h"

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            HSE Frequency(Hz)              = 25MHz
 *            SYSCLK(Hz)                     = 400MHz (Cortex-M7 CPU Clock)
 *            AHB Prescaler                  = 2
 *            D1 APB3 Prescaler              = 2 (APB3 Clock  100MHz)
 *            D2 APB1 Prescaler              = 2 (APB1 Clock  100MHz)
 *            D2 APB2 Prescaler              = 2 (APB2 Clock  100MHz)
 *            D3 APB4 Prescaler              = 2 (APB4 Clock  100MHz)
 *            PLL_M                          = 5
 *            PLL_N                          = 160
 *            PLL_P                          = 2
 *            PLL_Q                          = 4
 *            PLL_R                          = 2
 *            VDD(V)                         = 3.3
 *            Flash Latency(WS)              = 4
 */

void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    // Supply configuration update enable
    HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

    // Configure the main internal regulator output voltage
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // Wait until the power supply is ready
    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) { }

    // Initializes the RCC Oscillators
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
    // High-Speed External oscillator
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    // Low-Speed Internal oscillator
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    // Phase-Locked Loop
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    // division for VC0 input clock
    RCC_OscInitStruct.PLL.PLLM = 2;     // 25Mhz / 2 = 12.5MHz
    // multiplication for VC0 output clock
    RCC_OscInitStruct.PLL.PLLN = 64;    // 12.5MHz * 64 = 800MHz
    // division for system clock
    RCC_OscInitStruct.PLL.PLLP = 2;     // 800MHz / 2 = 400MHz 
    // division for peripheral clocks
    RCC_OscInitStruct.PLL.PLLQ = 13;    // 800MHz / 13
    RCC_OscInitStruct.PLL.PLLR = 2;     // 800MHz / 2

    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3; // input is 12.5MHz
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;  // 200MHz
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2; // 100MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2; // 100MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2; // 100MHz
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2; // 100MHz

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
}
