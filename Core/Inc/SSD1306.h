/*
 * SSD1306.h
 *
 *  Created on: Jun 25, 2023
 *      Author: konra
 */

#ifndef INC_SSD1306_H_
#define INC_SSD1306_H_


#endif /* INC_SSD1306_H_ */
#include "main.h"

#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 64
#define BLACK 0
#define WHITE 1
#define INVERSE 2


void SSD1306_Command(uint8_t com);
void SSD1306_Data(uint8_t dat);
void SSD1306_DrawPixel(int16_t x, int16_t y, uint8_t Color);
uint8_t SSD1306_ReadPixel(int16_t x, int16_t y);
void SSD1306_Clear(uint8_t Color);
void SSD1306_Display(void);
void SSD1306_Init(void);
void SSD1306_I2cInit(I2C_HandleTypeDef *i2c);
