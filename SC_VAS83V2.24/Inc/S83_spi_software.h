//����������� SPI  (������ ����� ����)
#ifndef _SSPI_H_
#define _SSPI_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"

//���������� ����������������� ���������� ����� SPI 
struct sspi_desc
	{
	GPIO_TypeDef *port;	//���� (GPIOB)
	uint16_t pin_clk;		//��� ����		
	uint16_t pin_mosi;	//��� ������ �����
	uint16_t pin_miso;	//��� ������ ����
	uint16_t pin_cs;		//��� ��� ������
	};
	
//���� ������ �� ��������
//�������� arg_nbytes ���� 
void sspi_transfer(struct sspi_desc *arg_sspi, uint8_t *arg_pdata, uint32_t arg_nbytes);

	//����� ������ ������� ������� ������������� �����. �� ���� ���������������� � ����� gpio.c




#endif