
#ifndef _LCD_H
#define _LCD_H

#include "stm32f1xx_hal.h"

// Define pin mappings
#define LCD_DATA_PORT       GPIOC
#define LCD_DATA_PIN_MASK   (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3)  // PC0..PC3

#define LCD_EN_PORT GPIOA
#define LCD_EN_PIN GPIO_PIN_8  // PA8

#define LCD_RS_PORT GPIOD
#define LCD_RS_PIN GPIO_PIN_2  // PD2

void LCD_InitGPIO(void);

void LCD_Init(void);

void LCD_SendCommand(uint8_t command);

void LCD_SendData(uint8_t command);

void LCD_Send(uint8_t command);

void LCD_Clear(void);

void LCD_DisplayString(uint8_t *str);

void LCD_Row(char *str);

void LCD_Char(char c);

void LCD_Write(char *row1, char *row2);

void LCD_SetCursor(int row, int col);

void LCD_HideCursor(void);

void LCD_ShowCursor(void);

#endif //_LCD_H
