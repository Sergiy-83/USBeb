#include "S83_lcd_ILI9486.h"

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

    LCD_write_command(0xF9);  
    LCD_write_data(0x00); 
    LCD_write_data(0x08);
    
    LCD_write_command(0xC0);  
    LCD_write_data(0x19); 
    LCD_write_data(0x1A); 
     
    LCD_write_command(0xC1);  
    LCD_write_data(0x45); 
    LCD_write_data(0X00); 
    
    LCD_write_command(0xC2);  
    LCD_write_data(0x33); 
    
    LCD_write_command(0xC5);  
    LCD_write_data(0x00); 
    LCD_write_data(0x28); 
    
    LCD_write_command(0xB1);  
    LCD_write_data(0x90); 
    LCD_write_data(0x11); 
    
    LCD_write_command(0xB4);  
    LCD_write_data(0x02); 
    
    LCD_write_command(0xB6);  
    LCD_write_data(0x00); 
    LCD_write_data(0x42);
    LCD_write_data(0x3B);
    
    LCD_write_command(0xB7);  
    LCD_write_data(0x07); 
    
    LCD_write_command(0xE0); 
    LCD_write_data(0x1F); 
    LCD_write_data(0x25); 
    LCD_write_data(0x22); 
    LCD_write_data(0x0B); 
    LCD_write_data(0x06); 
    LCD_write_data(0x0A); 
    LCD_write_data(0x4E); 
    LCD_write_data(0xC6); 
    LCD_write_data(0x39); 
    LCD_write_data(0x00); 
    LCD_write_data(0x00); 
    LCD_write_data(0x00); 
    LCD_write_data(0x00); 
    LCD_write_data(0x00); 
    LCD_write_data(0x00); 
    
    LCD_write_command(0xE1); 
    LCD_write_data(0x1F); 
    LCD_write_data(0x3F); 
    LCD_write_data(0x3F); 
    LCD_write_data(0x0F); 
    LCD_write_data(0x1F); 
    LCD_write_data(0x0F); 
    LCD_write_data(0x46); 
    LCD_write_data(0x49); 
    LCD_write_data(0x31); 
    LCD_write_data(0x05); 
    LCD_write_data(0x09); 
    LCD_write_data(0x03); 
    LCD_write_data(0x1C); 
    LCD_write_data(0x1A); 
    LCD_write_data(0x00);  
    
    LCD_write_command(0xF1);   
    LCD_write_data(0x36);   
    LCD_write_data(0x04);
    LCD_write_data(0x00);
    LCD_write_data(0x3C);
    LCD_write_data(0x0F);
    LCD_write_data(0x0F);
    LCD_write_data(0xA4);
    LCD_write_data(0x02);
    
    LCD_write_command(0xF2);   
    LCD_write_data(0x18);   
    LCD_write_data(0xA3);
    LCD_write_data(0x12);
    LCD_write_data(0x02);
    LCD_write_data(0x32);
    LCD_write_data(0x12);
    LCD_write_data(0xFF);
    LCD_write_data(0x32);
    LCD_write_data(0x00);
    
    LCD_write_command(0xF4);   
    LCD_write_data(0x40);   
    LCD_write_data(0x00);
    LCD_write_data(0x08);
    LCD_write_data(0x91);
    LCD_write_data(0x04);   
      
    LCD_write_command(0xF8);   
    LCD_write_data(0x21);   
    LCD_write_data(0x04);
    
		
    LCD_write_command(0x36);   //Ориетация  и др
 
		#ifdef CONFIG_ORIENTATION_LANDSCAPE_01														
		LCD_write_data(0xa8);//Альбом 1 a8 (0x28)(0xF8)
		#endif
		
		#ifdef CONFIG_ORIENTATION_LANDSCAPE_02	
		LCD_write_data(0x78);//Альбом 2
		#endif
		
		#ifdef CONFIG_ORIENTATION_PORTRAIT_01 	
		LCD_write_data(0xD8);//Портрет 1
		#endif
		
		#ifdef CONFIG_ORIENTATION_PORTRAIT_02
		LCD_write_data(0x18);//Портрет 2
		#endif
		
		
    LCD_write_command(0x3A);   
    LCD_write_data(0x55);        
 
    LCD_write_command(0x11);    //Exit Sleep 
    delay(120); 
				
    LCD_write_command(0x29);    //Display on 

		return;	
		}
	