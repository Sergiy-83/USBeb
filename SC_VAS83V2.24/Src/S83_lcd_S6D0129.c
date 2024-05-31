#include "S83_lcd_S6D0129.h"
#include "stm32f1xx_hal.h"

#include "S83_configuration.h"

#ifdef CONFIG_LCD_S6D0129
	//Запись комманды
	void LCD_write_command(uint16_t arg_cmd)
		{
		RS_RESET;
		WRITE_DATA_FAST_1B(arg_cmd);	
		RS_SET;	
		}
		
	//Запись данных
	void LCD_write_data (uint16_t arg_data)
		{
		WRITE_DATA_FAST_2B(arg_data);
		}
	// Запись в регистр REG данных DATA
	void LCD_write_register(uint16_t arg_reg, uint16_t arg_data)
		{
		LCD_write_command (arg_reg);
		LCD_write_data (arg_data);
		}
	// Установка области, к которую будут заноситься данные
	void LCD_set_window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
		{
		//окно	
		LCD_write_register(0x46,((y2-1)<<8)|y1);

		LCD_write_register(0x47,x2-1);
		LCD_write_register(0x48,x1);
		
		LCD_write_register(0x20,y2-1);
		LCD_write_register(0x21,x1);
		
		LCD_write_command(0x22);// Начать запись данных в экранную память (Reg=0x22)
		}
	//Инициализация
	void LCD_Init_S6D0129(void)
		{
		LCD_Init_pins();
		RST_RESET; 	delay(100);
		RST_SET;		delay(100);

		LCD_write_register(0x00,0x0001); delay(100);
			//LCD_write_register(0x11,0x2E00);	//запускается и без этой строки
		LCD_write_register(0x14,0x040B);
			//LCD_write_register(0x10,0x1040); _delay_ms(10);		 //запускается и без этой строки
			//LCD_write_register(0x13,0x0040); _delay_ms(10);		 //запускается и без этой строки
			//LCD_write_register(0x13,0x0060); _delay_ms(10);		 //запускается и без этой строки

		LCD_write_register(0x13,0x0070); delay(6);
		LCD_write_register(0x11,0x3704);
		LCD_write_register(0x10,0x1600); delay(2);
		LCD_write_register(0x01,0x0927);
		LCD_write_register(0x02,0x0700);

	//	LCD_write_register(0x03,0b0101000000101000);//LCD_write_register(0x03,0b1000000000000000);
		LCD_write_register(0x03,0x5028);//LCD_write_register(0x03,0b1000000000000000);
		LCD_write_register(0x07,0x0004);
		LCD_write_register(0x08,0x0505);
		LCD_write_register(0x09,0x0000);
		LCD_write_register(0x0B,0x0000);
		LCD_write_register(0x0C,0x0000);

		LCD_write_register(0x40,0x0000);
		LCD_write_register(0x46,0xEF00);
		LCD_write_register(0x47,0x013F);
		LCD_write_register(0x48,0x0000); delay(5);

		LCD_write_register(0x30,0x0000);
		LCD_write_register(0x31,0x0006);
		LCD_write_register(0x32,0x0000);
		LCD_write_register(0x33,0x0000);
		LCD_write_register(0x34,0x0707);
		LCD_write_register(0x35,0x0700);
		LCD_write_register(0x36,0x0303);
		LCD_write_register(0x37,0x0007);
		LCD_write_register(0x38,0x1100);
		LCD_write_register(0x39,0x1100);

		//LCD_write_register(0x07,0x0015); _delay_ms(4); //запускается и без этой строки
		LCD_write_register(0x07,0x0017); delay(4); //здесь LCD включается (появляются хаотично разбросанные цветные точки)
		}

void LCD_Init_pins(void)
		{
		RST_SET;
		WR_RESET;
		RD_SET;
		RS_RESET;
		CS_RESET;
		}	
#endif
