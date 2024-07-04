
#ifndef B4M38AVS_CVUT_H747_USART_H
#define B4M38AVS_CVUT_H747_USART_H

#include <string.h>

#include "stm32h7xx_hal.h"

extern UART_HandleTypeDef huart1;

#define HAL_UART_MODULE_ENABLED

#define STLINK_TX_Pin           GPIO_PIN_10
#define STLINK_TX_GPIO_Port     GPIOA
#define STLINK_RX_Pin           GPIO_PIN_9
#define STLINK_RX_GPIO_Port     GPIOA

#define COM1_UART                      USART1
#define COM1_CLK_ENABLE()             __HAL_RCC_USART1_CLK_ENABLE()
#define COM1_CLK_DISABLE()            __HAL_RCC_USART1_CLK_DISABLE()

#define COM1_TX_PIN                   GPIO_PIN_9
#define COM1_TX_GPIO_PORT             GPIOA
#define COM1_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM1_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define COM1_TX_AF                    GPIO_AF7_USART1

#define COM1_RX_PIN                    GPIO_PIN_10
#define COM1_RX_GPIO_PORT              GPIOA
#define COM1_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM1_RX_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOA_CLK_DISABLE()
#define COM1_RX_AF                    GPIO_AF7_USART1
#define COM_POLL_TIMEOUT              1000

void UART_Init(void);
void UART_SendChar(char c);
void UART_SendString(char *string);
void HAL_UART_MspInit(UART_HandleTypeDef* huart);

extern void Error_Handler(void);

#endif //B4M38AVS_CVUT_H747_USART_H
