
#include "lcd.h"

void LCD_InitGPIO(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIO Clocks
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    // Initialize data pins PC0..PC3 (LDC data pins 4-7)
    GPIO_InitStruct.Pin = LCD_DATA_PIN_MASK;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LCD_DATA_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DATA_PIN_MASK, GPIO_PIN_RESET);

    // Initialize Enable pin PA8
    GPIO_InitStruct.Pin = LCD_EN_PIN;
    HAL_GPIO_Init(LCD_EN_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);

    // Initialize RW pin PD2
    GPIO_InitStruct.Pin = LCD_RS_PIN;
    HAL_GPIO_Init(LCD_RS_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
}

void LCD_Init(void) {
    LCD_InitGPIO();  // Initialize GPIOs for LCD
    HAL_Delay(100);  // Wait for more VCC stabilization

    // Set to 8-bit mode initially
    LCD_SendCommand(0x03);
    HAL_Delay(5);    // Wait for more than 4.1 ms
    LCD_SendCommand(0x03);
    LCD_SendCommand(0x03);

    // Switch to 4-bit mode
    LCD_SendCommand(0x02);

    // Function set: 4-bit, 2 line, 5x8 font
    LCD_SendCommand(0x28);
    LCD_SendCommand(0x0F);
    LCD_SendCommand(0x06);

    // Clear display
    LCD_Clear();
}

void LCD_SendCommand(uint8_t command) {
    // RW low, write mode
    // RS low, command mode
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
    LCD_Send((command & 0xF0) >> 4);
    LCD_Send(command & 0x0F);
}

void LCD_SendData(uint8_t command) {
    // RW low, write mode - not done here
    // RS high, data mode
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_SET);
    LCD_Send((command & 0xF0) >> 4);
    LCD_Send(command & 0x0F);
}

void LCD_Send(uint8_t command) {
    // Reset data pins
    HAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DATA_PIN_MASK, GPIO_PIN_RESET);
    // Send 4-bit lower
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1);  // Short pulse

    HAL_GPIO_WritePin(LCD_DATA_PORT, (command & 0x0F), GPIO_PIN_SET);
    HAL_Delay(1);  // Allow time to process

    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);  // Short pulse
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01);  // Clear display command
    HAL_Delay(5);           // Clearing the display takes longer
}

void LCD_DisplayString(uint8_t *str) {
    while (*str != '\0') {  // Loop until the end of the string
        LCD_SendData(*str);  // Send the current character to the LCD
        str++;  // Increment the pointer to the next character
    }
}

void LCD_Row(char *str) {
    int i = 0;
    while (str[i] != '\0' && i < 20) {  // Ensure not to exceed 20 characters
        LCD_SendData(str[i++]);
    }

    while (i < 20) {  // Fill the rest of the line with spaces if shorter than 20 characters
        LCD_SendData(0x20);
        i++;
    }
}

void LCD_Char(char c) {
    LCD_SendData(c);
}

void LCD_Write(char *row1, char *row2) {
    LCD_SetCursor(0, 0);  // Set DDRAM address to 0 (first row)
    LCD_Row(row1);  // Write first row
    LCD_SetCursor(1, 0);  // Set DDRAM address to 0 (first row)
    LCD_Row(row2);  // Write second row
}

void LCD_SetCursor(int row, int col) {
    LCD_SendCommand(0x80 + ((((row) * 40) + (col)) & 0x7F));
}

void LCD_HideCursor(void) {
    LCD_SendCommand(0x0C);
}

void LCD_ShowCursor(void) {
    LCD_SendCommand(0x0F);
}
