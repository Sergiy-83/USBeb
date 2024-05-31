//Программный SPI  (только вывод пока)
#ifndef _SSPI_H_
#define _SSPI_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"

//Дескриптор однонаправленного прорамного порта SPI 
struct sspi_desc
	{
	GPIO_TypeDef *port;	//Порт (GPIOB)
	uint16_t pin_clk;		//Пин клок		
	uint16_t pin_mosi;	//Пин данные выход
	uint16_t pin_miso;	//Пин данные вход
	uint16_t pin_cs;		//Пин чип селект
	};
	
//Пока только на передачу
//Передать arg_nbytes байт 
void sspi_transfer(struct sspi_desc *arg_sspi, uint8_t *arg_pdata, uint32_t arg_nbytes);

	//Сдесь надобы сделать функцию инициализации порта. Но ЖПИО инициализируются в файле gpio.c




#endif