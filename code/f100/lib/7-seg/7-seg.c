
#include "7-seg.h"

uint8_t SEG_Digits[] = {
        SEG_0, SEG_1, SEG_2, SEG_3, SEG_4, SEG_5, SEG_6, SEG_7,
        SEG_8, SEG_9, SEG_A, SEG_b, SEG_E, SEG_F, SEG_MINUS, SEG_t, SEG_CLR
};
int SEG_DigitCount = sizeof(SEG_Digits) / sizeof(SEG_Digits[0]);

/**
 * Initialize the GPIO pins for communication with the 74HC595.
 */
void SEG_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // Configure the GPIO pin parameters
    GPIO_InitStructure.Pin = SEG_PIN_CLK | SEG_PIN_DAT | SEG_PIN_WR;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;

    // Initialize the GPIO pins with the configuration
    HAL_GPIO_Init(SEG_GPIO_PORT, &GPIO_InitStructure);

    // Optionally reset the pins to a known state
    HAL_GPIO_WritePin(SEG_GPIO_PORT, SEG_PIN_CLK | SEG_PIN_DAT | SEG_PIN_WR, GPIO_PIN_RESET);
}

/**
 * Send a byte to the 74HC595 shift register.
 * @param byte The byte to send to the shift register.
 */
void SEG_SendByte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        // Set data pin according to the MSB of the byte
        HAL_GPIO_WritePin(SEG_GPIO_PORT, SEG_PIN_DAT, (byte & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        byte <<= 1;  // Shift byte left to get the next bit

        // Toggle the clock pin to store the current bit into the shift register
        HAL_GPIO_WritePin(SEG_GPIO_PORT, SEG_PIN_CLK, GPIO_PIN_SET);
        HAL_Delay(1);  // wait for data to be written
        HAL_GPIO_WritePin(SEG_GPIO_PORT, SEG_PIN_CLK, GPIO_PIN_RESET);
    }
}

/**
 * Latch the data on the shift register output by toggling the WR pin.
 */
void SEG_Latch(void) {
    HAL_GPIO_WritePin(SEG_GPIO_PORT, SEG_PIN_WR, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(SEG_GPIO_PORT, SEG_PIN_WR, GPIO_PIN_RESET);
}

void SEG_Send(uint8_t byte) {
    SEG_SendByte(byte);
    SEG_Latch();
}
// Example usage:
// In your main function, call SEG_Init() to initialize GPIOs,
// then use SEG_SendByte() to send data and SEG_Latch() to update the outputs.
