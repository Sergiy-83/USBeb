#include "S83_lcd_R61581.h"

//Команда
void LCD_write_command(uint16_t arg_cmd) 
		{
		RS_RESET;	//команда

		WRITE_DATA_FAST_1B(arg_cmd);
		
		RS_SET;	//данные
		}
//Данные
void LCD_write_data(uint16_t arg_data)
		{
		WRITE_DATA_FAST_1B(arg_data);
		}
	

//Рабочее окно

void LCD_set_window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
		{
		LCD_write_command(0x2a);
		LCD_write_data(x1>>8);
		LCD_write_data(x1);
		LCD_write_data(x2>>8);
		LCD_write_data(x2);
		
		LCD_write_command(0x2b);
		LCD_write_data(y1>>8);
		LCD_write_data(y1);
		LCD_write_data(y2>>8);
		LCD_write_data(y2);
		
		LCD_write_command(0x2c); 							 
		}
	
void LCD_Init_pins(void)
		{
		RST_SET;
		WR_SET;
		RD_SET;
		RS_SET;
		CS_SET;
		}
	
void LCD_Init(void)
		{  
		LCD_Init_pins();
		
    delay(5); 
    RST_RESET;
    delay(15);
    RST_SET;
    delay(15);

    CS_RESET;
	
		LCD_write_command(0xB0);
    LCD_write_data(0x1E); 		//Manufacturer Command Access Protect Согласно даташиту (стр. 153), значение имеют только два младших бита. 
															//В 0x1E они имеют значение xxxxxx10 – разрешение всех команд производителя, кроме 0xC0-0xFF.
	
		LCD_write_command(0xB0);
    LCD_write_data(0x00); 		//Manufacturer Command Access Protect Младшие биты имеют значение xxxxxx00 – разрешение всех команд производителя
	
    LCD_write_command(0xB3); 	//Frame Memory Access and Interface Setting
    LCD_write_data(0x02);
    LCD_write_data(0x00);
    LCD_write_data(0x00);
    LCD_write_data(0x10);

    LCD_write_command(0xB4);	//Display Mode and Frame Memory Write Mode Setting
    LCD_write_data(0x00);		//0X10 

   // LCD_write_command(0xB9); 	//PWM PWM Settings for Brightness Control Disabled by default. 0xFF = Max brightness 
   // LCD_write_data(0x01);
   // LCD_write_data(0xFF); 	//FF brightness
   // LCD_write_data(0xFF);
   // LCD_write_data(0x18);

    
    LCD_write_command(0xC0); //Panel Driving Setting
    LCD_write_data(0x02);
    LCD_write_data(0x3B);
    LCD_write_data(0x00);
    LCD_write_data(0x00);
    LCD_write_data(0x00);
    LCD_write_data(0x01);
    LCD_write_data(0x00);	//NW
    LCD_write_data(0x43);

    LCD_write_command(0xC1); //Display Timing Setting for Normal Mode
    LCD_write_data(0x08);
    LCD_write_data(0x15);  	 //CLOCK
    LCD_write_data(0x08);
    LCD_write_data(0x08);

    LCD_write_command(0xC4); //Source/VCOM/Gate Driving Timing Setting
    LCD_write_data(0x15);
    LCD_write_data(0x03);
    LCD_write_data(0x03);
    LCD_write_data(0x01);
    
    LCD_write_command(0xC6);/*Interface Setting*/
    //LCD_write_data((R61581_DPL << 0) | (R61581_EPL << 1) | (R61581_HSPL << 4) | (R61581_VSPL << 5));
    LCD_write_data(0xC2);
	    
    LCD_write_command(0xC8); /*Gamma Set*/
    LCD_write_data(0x0c);
    LCD_write_data(0x05);
    LCD_write_data(0x0A);
    LCD_write_data(0x6B);
    LCD_write_data(0x04);
    LCD_write_data(0x06);
    LCD_write_data(0x15);
    LCD_write_data(0x10);
    LCD_write_data(0x00);
    LCD_write_data(0x31);


    LCD_write_command(0x36); //set_address_mode //Ориентации
    //if(R61581_ORI == 0) LCD_write_data(0xE0);
    //else LCD_write_data(0x20);
		LCD_write_data(0x0A);

    LCD_write_command(0x0C); //get_pixel_format
    LCD_write_data(0x55);

    LCD_write_command(0x3A); //set_pixel_format
    LCD_write_data(0x55);

    LCD_write_command(0x38); //exit_idle_mode

    LCD_write_command(0xD0); //Power Setting (Common Setting)
    LCD_write_data(0x07);
    LCD_write_data(0x07);
    LCD_write_data(0x14);
    LCD_write_data(0xA2);

    LCD_write_command(0xD1); //VCOM Setting
    LCD_write_data(0x03);
    LCD_write_data(0x5A);
    LCD_write_data(0x10);

    LCD_write_command(0xD2); //Power Setting for Normal Mode
    LCD_write_data(0x03);
    LCD_write_data(0x04);
    LCD_write_data(0x04);

    LCD_write_command(0x11); //exit_sleep_mode
    delay(150);

    LCD_write_command(0x2A); //set_column_address
    LCD_write_data(0x00);
    LCD_write_data(0x00);
    //LCD_write_data(((R61581_HOR_RES - 1) >> 8) & 0XFF);
    //LCD_write_data((R61581_HOR_RES - 1) & 0XFF);
		LCD_write_data(0x01);
    LCD_write_data(0xDF);

	
    LCD_write_command(0x2B); //set_page_address
    LCD_write_data(0x00);
    LCD_write_data(0x00);
   // LCD_write_data(((R61581_VER_RES - 1) >> 8) & 0XFF);
    //LCD_write_data((R61581_VER_RES - 1) & 0XFF);
		LCD_write_data(0x01);
    LCD_write_data(0x3F);

    delay(10);

    LCD_write_command(0x29); //set_display_on
    delay(5);

    LCD_write_command(0x2C); //write_memory_start
    delay(5);
	
	
}