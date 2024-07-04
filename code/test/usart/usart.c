
#include "usart.h"

UART_HandleTypeDef UartHandle;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = "\n\r ****UART-Hyperterminal communication based on DMA****\n\r Enter 10 characters using keyboard :\n\r";

/* Buffer used for reception */
uint8_t aRxBuffer[RXBUFFERSIZE];

void USART_Init(void) {
    /*##-1- Configure the UART peripheral ######################################*/
    /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
    /* UART configured as follows:
        - Word Length = 8 Bits
        - Stop Bit    = One Stop bit
        - Parity      = ODD parity
        - BaudRate    = 9600 baud
        - Hardware flow control disabled (RTS and CTS signals) */
    UartHandle.Instance        = USARTx;

    UartHandle.Init.BaudRate   = 9600;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits   = UART_STOPBITS_1;
    UartHandle.Init.Parity     = UART_PARITY_ODD;
    UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode       = UART_MODE_TX_RX;

    if (HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        /* Initialization Error */
        while (1) {
            /* error */
        }
    }
    /*##-2- Start the transmission process #####################################*/
    /* User start transmission data through "TxBuffer" buffer */
    if (HAL_UART_Transmit_DMA(&UartHandle, (uint8_t *)aTxBuffer, TXBUFFERSIZE) != HAL_OK)
    {
        /* Transfer error in transmission process */
        while (1) {
            /* error */
        }
    }

    /*##-3- Put UART peripheral in reception process ###########################*/
    /* Any data received will be stored in "RxBuffer" buffer : the number max of
       data received is 10 */
    if (HAL_UART_Receive_DMA(&UartHandle, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)
    {
        /* Transfer error in reception process */
        while (1) {
            /* error */
        }
    }

    /*##-4- Wait for the end of the transfer ###################################*/
    /*  Before starting a new communication transfer, you need to check the current
        state of the peripheral; if it�s busy you need to wait for the end of current
        transfer before starting a new one.
        For simplicity reasons, this example is just waiting till the end of the
        transfer, but application may perform other tasks while transfer operation
        is ongoing. */
    while (HAL_UART_GetState(&UartHandle) != HAL_UART_STATE_READY)
    {
    }

    /*##-5- Send the received Buffer ###########################################*/
    if (HAL_UART_Transmit_DMA(&UartHandle, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)
    {
        /* Transfer error in transmission process */
        while (1) {
            /* error */
        }
    }

    /*##-6- Wait for the end of the transfer ###################################*/
    /*  Before starting a new communication transfer, you need to check the current
        state of the peripheral; if it�s busy you need to wait for the end of current
        transfer before starting a new one.
        For simplicity reasons, this example is just waiting till the end of the
        transfer, but application may perform other tasks while transfer operation
        is ongoing. */
    while (HAL_UART_GetState(&UartHandle) != HAL_UART_STATE_READY)
    {
    }
}

/**
  * @brief  This function handles DMA interrupt request.
  * @param  None
  * @retval None
  * @Note   This function is redefined in "main.h" and related to DMA stream
  *         used for USART data transmission
  */
void USARTx_DMA_RX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(UartHandle.hdmarx);
}

/**
  * @brief  This function handles DMA interrupt request.
  * @param  None
  * @retval None
  * @Note   This function is redefined in "main.h" and related to DMA stream
  *         used for USART data reception
  */
void USARTx_DMA_TX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(UartHandle.hdmatx);
}

/**
  * @brief  This function handles UART interrupt request.
  * @param  None
  * @retval None
  * @Note   This function is redefined in "main.h" and related to DMA
  *         used for USART data transmission
  */
void USARTx_IRQHandler(void)
{
    HAL_UART_IRQHandler(&UartHandle);
}
