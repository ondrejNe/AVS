
#ifndef TEST_7_SEG_H
#define TEST_7_SEG_H

#include "stm32f1xx_hal.h"

#include <stdint.h>

// Define the GPIO pins connected to the 74HC595
#define SEG_PIN_DAT GPIO_PIN_6  // 74HC595 Data pin
#define SEG_PIN_CLK GPIO_PIN_8  // 74HC595 Clock pin
#define SEG_PIN_WR  GPIO_PIN_7  // 74HC595 Write pin

// GPIO port
#define SEG_GPIO_PORT GPIOC

typedef enum {
    SEG_0 = 0x03,       // 0b00000011
    SEG_1 = 0x9F,       // 0b10011111
    SEG_2 = 0x25,       // 0b00100101
    SEG_3 = 0x0D,       // 0b00001101
    SEG_4 = 0x99,       // 0b10011001
    SEG_5 = 0x49,       // 0b01001001
    SEG_6 = 0x41,       // 0b01000001
    SEG_7 = 0x1F,       // 0b00011111
    SEG_8 = 0x01,       // 0b00000001
    SEG_9 = 0x09,       // 0b00001001
    SEG_A = 0x11,       // 0b00010001
    SEG_b = 0xC1,       // 0b11000001
    SEG_E = 0x61,       // 0b01100001
    SEG_F = 0x71,       // 0b01110001
    SEG_MINUS = 0xFD,   // 0b11111101
    SEG_t = 0xE1,       // 0b11100001
    SEG_CLR = 0xFF      // 0b11111111
} SEG_Digit;


extern uint8_t SEG_Digits[];
extern int SEG_DigitCount;

// Function prototypes
void SEG_Init(void);
void SEG_SendByte(uint8_t byte);
void SEG_Latch(void);
void SEG_Send(uint8_t byte);

#endif //TEST_7_SEG_H
