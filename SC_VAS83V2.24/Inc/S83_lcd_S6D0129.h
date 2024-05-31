#ifndef __S83_LCD_S6D0129_H
#define __S83_LCD_S6D0129_H

#include "stdint.h"
#include "S83_configuration.h"

#ifdef CONFIG_LCD_S6D0129
	typedef unsigned char byte;

	#define X_MAX 320
	#define Y_MAX 240

	#define delay(x)	HAL_Delay(x)
	#define LCD_DATA_PORT GPIOA->ODR

	#define RST_SET 		GPIOB->BSRR = GPIO_PIN_2 				//оранж						
	#define RST_RESET 	GPIOB->BSRR = (uint32_t)GPIO_PIN_2 << 16U		

	#define RD_SET 			GPIOB->BSRR = GPIO_PIN_11								//красный		
	#define RD_RESET 		GPIOB->BSRR = (uint32_t)GPIO_PIN_11 << 16U		

	#define WR_SET 			GPIOC->BSRR = GPIO_PIN_13										//зеленый
	#define WR_RESET 		GPIOC->BSRR = (uint32_t)GPIO_PIN_13 << 16U	

	#define RS_SET 			GPIOC->BSRR = GPIO_PIN_15 									//белый
	#define RS_RESET 		GPIOC->BSRR = (uint32_t)GPIO_PIN_15 << 16U	

	#define CS_SET 			GPIOC->BSRR = GPIO_PIN_14 										
	#define CS_RESET 		GPIOC->BSRR = (uint32_t)GPIO_PIN_14 << 16U		//синий

	#define PULSE_WR		 WR_SET; WR_RESET
	#define WRITE_DATA_FAST_2B(x) 	LCD_DATA_PORT = x>>8; PULSE_WR; LCD_DATA_PORT = x; PULSE_WR
	#define WRITE_DATA_FAST_1B(x) 	LCD_DATA_PORT = x; PULSE_WR
	
	void LCD_Init_S6D0129(void);
	void LCD_write_command(uint16_t arg_cmd);
	void LCD_write_data(uint16_t arg_data);
	void LCD_write_register (uint16_t arg_reg, uint16_t arg_data);
	void LCD_set_window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
	void LCD_Init_pins(void);
#endif



#endif