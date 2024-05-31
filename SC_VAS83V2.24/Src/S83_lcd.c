#include "S83_configuration.h"
#include "S83_lcd.h"
#include "S83_spi_software.h"
#include "stdbool.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"

#ifdef CONFIG_LCD_ILI9481
	#include "S83_lcd_ILI9481.c"
#endif

#ifdef CONFIG_LCD_R61581
	#include "S83_lcd_R61581.c"
#endif

#ifdef CONFIG_LCD_ILI9486
	#include "S83_lcd_ILI9486.c"
#endif

#ifdef CONFIG_LCD_ILI9488
	#include "S83_lcd_ILI9488.c"
#endif

#ifdef CONFIG_LCD_ST7796S
	#include "S83_lcd_ST7796S.c"
#endif

#ifdef CONFIG_LCD_RM68090
	#include "S83_lcd_RM68090.c"
#endif

#ifdef CONFIG_LCD_ILI9325  //аналог RM68090
	#include "S83_lcd_RM68090.c"
#endif







uint8_t brightness_lcd = 0;
bool 		lcd_on=0;
uint8_t no_kosiak(uint8_t arg_byte);

struct sspi_desc sspi_3 = 
		{
		.port 		= GPIOB,
		.pin_clk 	= GPIO_PIN_7,
		.pin_cs 	= GPIO_PIN_14,
		.pin_miso = 0,
		.pin_mosi = GPIO_PIN_8 	
		};

void set_data_595lcd(void)
	{
		uint8_t res,i,tmp_brightness;
				
		res = 0;
		
		//Вычисляем значение для яркости
		tmp_brightness = brightness_lcd / 3; 
		if (tmp_brightness > 31) tmp_brightness = 31;	
		
		res = no_kosiak(tmp_brightness); //функция исправляет небольшой, програмно поправимый косяк на печатной плате. Разряды r2r матрицы подключил зеркально.
		
		if (!lcd_on) //Если подсветка выключена
		res|= (uint8_t)0x80;		//то установим последний бит в 1 что закроет транзистор T1 (SI2301DS) 
		
					
		sspi_transfer(&sspi_3,&res,1);
	}
//Инвертирует зеркально биты
uint8_t no_kosiak(uint8_t arg_byte)
	{
	uint8_t	ret=0;
	if (arg_byte & 0x1)  ret |= 0x10;
	if (arg_byte & 0x2)  ret |= 0x8;
	if (arg_byte & 0x4)  ret |= 0x4;
	if (arg_byte & 0x8)  ret |= 0x2;
	if (arg_byte & 0x10) ret |= 0x1;
	return ret;	
	}	
//Установить яркость в процентах	
void set_lcd_brightness(uint8_t arg_brightness)
		{
		if (arg_brightness > 100)	brightness_lcd = 100;
		else 											brightness_lcd = arg_brightness;
		set_data_595lcd();
		}
		
//Включить подсветку	
void lcd_backlight_on(void)		
	{
	lcd_on = true;
	set_data_595lcd();
	}
	
//Выключить подсветку	
void lcd_backlight_off(void)		
	{
	lcd_on = false;
	set_data_595lcd();
	}	
	