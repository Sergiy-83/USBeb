#include "S83_lcd_ST7796S.h"

void LCD_Init_pins(void)
	{
	RST_SET;
	WR_SET;
	RD_SET;
	RS_SET;
	CS_RESET;
	}


//Запись комманды - регистра
void LCD_write_command(uint16_t arg_cmd)
	{
	RS_RESET;
	WRITE_DATA_FAST_1B(arg_cmd);
	RS_SET;
	}	
	
//Запись данных
void LCD_write_data (uint16_t arg_data)
	{
	WRITE_DATA_FAST_1B(arg_data);
	}
	

	
void LCD_Init(void)
	{	
	LCD_Init_pins(); 	
	delay(10);
	
 	RST_RESET; 				delay(100);
	RST_SET;					delay(100); 

	LCD_write_command(0xF0);
  LCD_write_data(0xC3);
		
  LCD_write_command(0xF0);
  LCD_write_data(0x96);
		
  LCD_write_command(0x36);
  LCD_write_data(0xE8);
		
  LCD_write_command(0x3A);
  LCD_write_data(0x05);
			
  LCD_write_command(0xB0);
  LCD_write_data(0x80);
		
  LCD_write_command(0xB6);
  LCD_write_data(0x20);
  LCD_write_data(0x02);  
	
  LCD_write_command(0xB5);
  LCD_write_data(0x02);
  LCD_write_data(0x03);
  LCD_write_data(0x00);
  LCD_write_data(0x04);
	
  LCD_write_command(0xB1);
  LCD_write_data(0x80);  
  LCD_write_data(0x10);  
	
  LCD_write_command(0xB4);
  LCD_write_data(0x00);
	
  LCD_write_command(0xB7);
  LCD_write_data(0xC6);
  LCD_write_command(0xC5);
  LCD_write_data(0x24);
	
  LCD_write_command(0xE4);
  LCD_write_data(0x31);
	
  LCD_write_command(0xE8);
  LCD_write_data(0x40);
  LCD_write_data(0x8A);
  LCD_write_data(0x00);
  LCD_write_data(0x00);
  LCD_write_data(0x29);
  LCD_write_data(0x19);
  LCD_write_data(0xA5);
  LCD_write_data(0x33);
	
  LCD_write_command(0xC2);
  LCD_write_command(0xA7);
  
  LCD_write_command(0xE0);
  LCD_write_data(0xF0);
  LCD_write_data(0x09);
  LCD_write_data(0x13);
  LCD_write_data(0x12);
  LCD_write_data(0x12);
  LCD_write_data(0x2B);
  LCD_write_data(0x3C);
  LCD_write_data(0x44);
  LCD_write_data(0x4B);
  LCD_write_data(0x1B);
  LCD_write_data(0x18);
  LCD_write_data(0x17);
  LCD_write_data(0x1D);
  LCD_write_data(0x21);

  LCD_write_command(0xE1);
  LCD_write_data(0xF0);
  LCD_write_data(0x09);
  LCD_write_data(0x13);
  LCD_write_data(0x0C);
  LCD_write_data(0x0D);
  LCD_write_data(0x27);
  LCD_write_data(0x3B);
  LCD_write_data(0x44);
  LCD_write_data(0x4D);
  LCD_write_data(0x0B);
  LCD_write_data(0x17);
  LCD_write_data(0x17);
  LCD_write_data(0x1D);
  LCD_write_data(0x21);

  LCD_write_command(0x36);
	
		#ifdef CONFIG_ORIENTATION_LANDSCAPE_01														
		LCD_write_data(0x28);//Альбом 1 28
		#endif
		
		#ifdef CONFIG_ORIENTATION_LANDSCAPE_02	
		LCD_write_data(0xE8);//Альбом 2
		#endif
		
		#ifdef CONFIG_ORIENTATION_PORTRAIT_01 	
		LCD_write_data(0x48);//Портрет 1 48
		#endif
		
		#ifdef CONFIG_ORIENTATION_PORTRAIT_02
		LCD_write_data(0x88);//Портрет 2 88
		#endif
	
	
	
  LCD_write_command(0xF0);
  LCD_write_data(0xC3);
	
  LCD_write_command(0xF0);
  LCD_write_data(0x69);
	
  LCD_write_command(0x13);
  LCD_write_command(0x11);
  LCD_write_command(0x29);
	
	LCD_write_command(0x2C);

	}
	
	// Установка области, к которую будут заноситься данные
void LCD_set_window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
	{
	LCD_write_command(0x2A);	
	LCD_write_data(x1>>8);
	LCD_write_data(x1);		
	LCD_write_data(x2>>8);
	LCD_write_data(x2);

	LCD_write_command(0x2B);	
	LCD_write_data(y1>>8);
	LCD_write_data(y1);		
	LCD_write_data(y2>>8);
	LCD_write_data(y2);

	LCD_write_command(0x2C);
	}
	