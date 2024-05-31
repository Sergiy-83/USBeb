#ifndef __S83_LCD_H
#define __S83_LCD_H

#include <stdint.h>
#include "S83_configuration.h"

#define delay(x)				HAL_Delay(x)
#define LCD_DATA_PORT 	GPIOA->ODR

#define RST_SET 		GPIOB->BSRR = GPIO_PIN_2 											
#define RST_RESET 	GPIOB->BSRR = (uint32_t)GPIO_PIN_2 << 16U

#define RD_SET 			GPIOB->BSRR = GPIO_PIN_11							
#define RD_RESET 		GPIOB->BSRR = (uint32_t)GPIO_PIN_11 << 16U

#define WR_SET 			GPIOC->BSRR = GPIO_PIN_13						
#define WR_RESET 		GPIOC->BSRR = (uint32_t)GPIO_PIN_13 << 16U

#define RS_SET 			GPIOC->BSRR = GPIO_PIN_15 						
#define RS_RESET 		GPIOC->BSRR = (uint32_t)GPIO_PIN_15 << 16U

#define CS_SET 			GPIOC->BSRR = GPIO_PIN_14 										
#define CS_RESET 		GPIOC->BSRR = (uint32_t)GPIO_PIN_14 << 16U

#define PULSE_WR						WR_RESET;  WR_SET
#define WRITE_DATA_FAST_2B(x) 	LCD_DATA_PORT = x>>8;  PULSE_WR; LCD_DATA_PORT = x; PULSE_WR
#define WRITE_DATA_FAST_1B(x) 	LCD_DATA_PORT = x; PULSE_WR



#ifdef CONFIG_LCD_ILI9481
	#include "S83_lcd_ILI9481.h"
#endif

#ifdef CONFIG_LCD_R61581
	#include "S83_lcd_R61581.h"
#endif

#ifdef CONFIG_LCD_ILI9486
	#include "S83_lcd_ILI9486.h"
#endif

#ifdef CONFIG_LCD_ILI9488
	#include "S83_lcd_ILI9488.h"
#endif

#ifdef CONFIG_LCD_ST7796S
	#include "S83_lcd_ST7796S.h"
#endif

#ifdef CONFIG_LCD_RM68090
	#include "S83_lcd_RM68090.h"
#endif

#ifdef CONFIG_LCD_ILI9325 //аналог RM68090
	#include "S83_lcd_RM68090.h"
#endif

#ifdef CONFIG_LCD_S6D0129
	#include "S83_lcd_S6D0129.h"
#endif

void LCD_Init(void);
void LCD_write_command(uint16_t arg_cmd);
void LCD_write_data(uint16_t arg_data);
void LCD_set_window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void lcd_backlight_off(void);
void lcd_backlight_on(void);
void set_lcd_brightness(uint8_t arg_brightness);

#endif
