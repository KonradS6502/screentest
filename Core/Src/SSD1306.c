/*
 * SSD1306.c
 *
 *  Created on: Jun 25, 2023
 *      Author: konra
 */
#include "SSD1306.h"

static uint8_t buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8];
I2C_HandleTypeDef *ssd1306_i2c;


void SSD1306_Command(uint8_t com)
{
	HAL_I2C_Mem_Write(ssd1306_i2c, 0x3C<<1, 0x00, 1, &com, sizeof(com), 100);
}




void SSD1306_Data(uint8_t dat)
{

	HAL_I2C_Mem_Write(ssd1306_i2c, 0x3C<<1, 0x40, 1, &dat, sizeof(dat), 100);
}


void SSD1306_DrawPixel(int16_t x, int16_t y, uint8_t Color)
{
	 if ((x < 0) || (x >= SSD1306_LCDWIDTH) || (y < 0) || (y >= SSD1306_LCDHEIGHT))
		 return;

	 switch(Color)
	 {
		 case WHITE:   buffer[x+ (y/8)*SSD1306_LCDWIDTH] |=  (1 << (y&7)); break;
		 case BLACK:   buffer[x+ (y/8)*SSD1306_LCDWIDTH] &= ~(1 << (y&7)); break;
		 case INVERSE: buffer[x+ (y/8)*SSD1306_LCDWIDTH] ^=  (1 << (y&7)); break;
	 }
}
uint8_t SSD1306_ReadPixel(int16_t x, int16_t y){
	return(buffer[x+ (y/8)*SSD1306_LCDWIDTH]);
}

void SSD1306_Clear(uint8_t Color)
{
	switch (Color)
	{
		case WHITE:
			memset(buffer, 0xFF, (SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8));
			break;
		case BLACK:
			memset(buffer, 0x00, (SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8));
			break;
	}
}


void SSD1306_Display(void)
{
	SSD1306_Command(0x22);
	SSD1306_Command(0x00);
	SSD1306_Command(0x07);
	HAL_I2C_Mem_Write(ssd1306_i2c, 0x3C<<1, 0x40, 1, (uint8_t*)&buffer, (SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8), 100);

}

void SSD1306_Init(void)
{
	SSD1306_Command(0xAE);  // Display Off

	SSD1306_Command(0x00);
	SSD1306_Command(0x10);
	SSD1306_Command(0x40);
	SSD1306_Command(0x20);  // Set addressing mode
	SSD1306_Command(0x00);  // Horizontal Addressing Mode

	SSD1306_Command(0xA6);  // Set Normal Display

	SSD1306_Command(0xA8);  // Select Multiplex Ratio
	SSD1306_Command(0x3F);  // Default => 0x3F (1/64 Duty)	0x1F(1/32 Duty)

	SSD1306_Command(0xD3);  // Setting Display Offset
	SSD1306_Command(0x00);  // 00H Reset

	SSD1306_Command(0xD5);  // SET DISPLAY CLOCK
	SSD1306_Command(0x80);  // 105HZ

	SSD1306_Command(0xD9);	// Set Pre-Charge period
	SSD1306_Command(0x22);

	SSD1306_Command(0xDA);  // Set COM Hardware Configuration
	SSD1306_Command(0x12);  // Alternative COM Pin---See IC Spec page 34
							// (0x02)=> A4=0;Sequential COM pin configuration;A5=0;Disable COM Left/Right remap

	SSD1306_Command(0xDB);	// Set Deselect Vcomh level
	SSD1306_Command(0x40);

	SSD1306_Command(0x8D);  // Set Charge Pump
	SSD1306_Command(0x14);  // Endable Charge Pump

	SSD1306_Command(0xA4);  // Entire Display ON
	SSD1306_Command(0xAF);
}

void SSD1306_I2cInit(I2C_HandleTypeDef *i2c)
{
	ssd1306_i2c = i2c;

	SSD1306_Init();
}
