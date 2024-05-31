#include "S83_spi_software.h"
#include "stm32f1xx_hal.h"

#define PIN_MOSI_SET 		HAL_GPIO_WritePin(arg_sspi->port,arg_sspi->pin_mosi,GPIO_PIN_SET)
#define PIN_MOSI_RESET	HAL_GPIO_WritePin(arg_sspi->port,arg_sspi->pin_mosi,GPIO_PIN_RESET)

#define PIN_CLK_SET			HAL_GPIO_WritePin(arg_sspi->port,arg_sspi->pin_clk,GPIO_PIN_SET)
#define PIN_CLK_RESET		HAL_GPIO_WritePin(arg_sspi->port,arg_sspi->pin_clk,GPIO_PIN_RESET)

#define PIN_CS_SET			HAL_GPIO_WritePin(arg_sspi->port,arg_sspi->pin_cs,GPIO_PIN_SET)
#define PIN_CS_RESET		HAL_GPIO_WritePin(arg_sspi->port,arg_sspi->pin_cs,GPIO_PIN_RESET)


void sspi_transfer(struct sspi_desc *arg_sspi, uint8_t *arg_pdata, uint32_t arg_nbytes)
	{
		uint32_t i;
		uint8_t *pdata = arg_pdata;
		uint8_t transfer_byte;
		uint8_t nbit;
		
		PIN_CS_RESET;

		for (i=0;i<arg_nbytes;i++,pdata++) 		//выводим байты
						{
						transfer_byte = *pdata;
						for (nbit=0; nbit<8; nbit++)		//выводим биты
							{
							if (transfer_byte & 0x80)	PIN_MOSI_SET; 
							else                			PIN_MOSI_RESET;
							PIN_CLK_RESET;
							PIN_CLK_SET;
												
							transfer_byte<<=1;    //сдедующий бит
							}								
						}
						
		PIN_CS_SET;
	}
