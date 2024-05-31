#ifndef _S83_LCD_ILI9481_H_
#define _S83_LCD_ILI9481_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "S83_configuration.h"

typedef unsigned char byte;

#define X_MAX 479
#define Y_MAX 319


	#ifdef 	CONFIG_ORIENTATION_PORTRAIT_01
		#define X_MAX 319
		#define Y_MAX 479
	#endif

	#ifdef 	CONFIG_ORIENTATION_PORTRAIT_02
		#define X_MAX 319
		#define Y_MAX 479
	#endif

	#ifdef 	CONFIG_ORIENTATION_LANDSCAPE_01
		#define X_MAX 479
		#define Y_MAX 319
	#endif

	#ifdef 	CONFIG_ORIENTATION_LANDSCAPE_02
		#define X_MAX 479
		#define Y_MAX 319
	#endif




#define delay(x)		HAL_Delay(x)
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

void LCD_Init_ILI9481(void);
void LCD_write_command(uint8_t arg_cmd);
void LCD_write_data(uint8_t arg_data);
void LCD_set_window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);

#endif
