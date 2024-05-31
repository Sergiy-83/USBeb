#include "S83_graphics.h"
#include "stm32f1xx_hal.h"
#include "S83_lcd.h"
#include "S83_configuration.h"

#ifdef CONFIG_S83_FONT_8x12
	#include "S83_font_8x12.h"
#endif

#ifdef CONFIG_S83_FONT_8x16
	#include "S83_font_8x16.h"
#endif

#ifdef CONFIG_S83_FONT_8x16
void G_print_sym_f8x16(uint8_t sym,uint16_t x,uint16_t y,uint16_t color,uint16_t b_color)
		{
		uint8_t  i,j,temp,temp2;
		char *startadr;
		startadr =	(char*)font_8x16 + (sym*16);			
		LCD_set_window(x,y,x+7,y+15); 
			
		for(i=0;i<16;i++)
				{
				temp = *startadr; 
				temp2=1;
				for (j=0;j<8;j++)
						{
						if(temp&temp2)
							{
							WRITE_DATA_FAST_2B(color);
							}
						else
							{
							WRITE_DATA_FAST_2B(b_color);
							}
						temp2<<=1;
						}
				startadr++;
				}
		}
//Напечатать строку
void G_print_string_len_f8x16(char *sym,uint16_t x,uint16_t y,uint16_t len,uint16_t color,uint16_t b_color)
	{
	unsigned int i, max;
	max=len*10; //шаг по иксу 8 пикс + 2

	for (i=0; i<max; i+=10)
		{
		 G_print_sym_f8x16(*sym,x+i,y,color,b_color);
		 sym++;
		}
	}		
#endif	
	
#ifdef CONFIG_S83_FONT_8x12		
void G_print_sym_f8x12(uint8_t sym,uint16_t x,uint16_t y,uint16_t color,uint16_t b_color)
		{
		uint8_t  i,j,temp,temp2;
		char *startadr;
		startadr =	(char*)font_8x12 + (sym*12);			
		LCD_set_window(x,y,x+7,y+11); 
			
		for(i=0;i<12;i++)
				{
				temp = *startadr; 
				temp2=1;
				for (j=0;j<8;j++)
						{
						if(temp&temp2)
							{
							WRITE_DATA_FAST_2B(color);
							}
						else
							{
							WRITE_DATA_FAST_2B(b_color);
							}
						temp2<<=1;
						}
				startadr++;
				}
		}		
		
		//Напечатать строку
void G_print_string_len_f8x12(char *sym,uint16_t x,uint16_t y,uint16_t len,uint16_t color,uint16_t b_color)
	{
	unsigned int i, max;
	max=len*10; //шаг по иксу 8 пикс + 2

	for (i=0; i<max; i+=10)
		{
		 G_print_sym_f8x12(*sym,x+i,y,color,b_color);
		 sym++;
		}
	}	
#endif		
	
			
//Нарисовать квадратик и залить его 	
void G_fill_rectangle(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t color)
	{
	uint32_t i,j;
	LCD_set_window(x0,y0,x1,y1);

	x1 = x1 - x0 + 1;
	y1 = y1 - y0 + 1;
	
		for (i=0; i<x1; i++)
		for (j=0; j<y1; j++)
				{
				WRITE_DATA_FAST_2B(color);
				}
	}			
// Очистить экран
void G_clear_screen(uint16_t arg_color)
	{
	G_fill_rectangle(0,0,X_MAX,Y_MAX,arg_color);
	}
	
	
//Вывод цветного изображения 
void G_print_image(const unsigned char *image,uint16_t size_x,uint16_t size_y,uint16_t x,uint16_t y)
	{
	char* max_addr;

	LCD_set_window(x,y,x+size_x-1,y+size_y-1);
	max_addr = (char*)image + size_y*size_x*2;   //2-х байтный цвет

	for(; image < max_addr; image++)
		{
		WRITE_DATA_FAST_1B(*image); 
		}	
	}


	
//Вывод серого изображения (пол. байта на пиксель)
void  G_print_image_gray_05(const char *image,unsigned int size_x, unsigned int size_y,unsigned int x,unsigned int y)
	{
	char HL;
	char* max_addr;

	LCD_set_window(x,y,x+size_x-1,y+size_y-1);
	max_addr = (char*)image + size_y*size_x/2;
	LCD_DATA_PORT=0;
	for(; image < max_addr; image++)
	{		
		HL = *image;
		//первый пиксель
		LCD_DATA_PORT = (HL & 0xF0) | (HL >> 5);
		PULSE_WR; 
		LCD_DATA_PORT = ((HL << 3) & 0x80 ) | ((HL & 0xf0) >>3); 
		PULSE_WR;
				
		//второй пиксель
		LCD_DATA_PORT = (HL << 4) | ((HL >> 1)& 0x07);
		PULSE_WR; 
		LCD_DATA_PORT = (HL << 7) | ((HL <<1) & 0x1F); 
		PULSE_WR;
		}
	}	
	
//Вывод серого изображения 
void G_print_image_gray(const unsigned char *image,uint16_t size_x, uint16_t size_y,uint16_t x,uint16_t y)
	{
	uint16_t volatile i,j,temp2;
	unsigned char color;
	LCD_set_window(x,y,x+size_x-1,y+size_y-1);

	temp2=size_y*size_x;

	for(i=0;i<temp2;i+=size_x) // шаг по игрЫку по строкам
		{
		for (j=0;j<size_x;j++) //шаг по иксу по столбцам
			{
				color = *(image+i+j);
				WRITE_DATA_FAST_1B((color & 0xF8) | (color >> 5));
				WRITE_DATA_FAST_1B(((color << 3) & 0xE0 ) | (color >>3));
			}
		}
	}
//Вывод серого изображения повернутого на 90 градусов 
void G_print_image_gray_r90grad(const unsigned char  *image,uint16_t size_x, uint16_t size_y,uint16_t x,uint16_t y)
		{
		uint16_t volatile i,j,temp2;
		unsigned char color;

		LCD_set_window(x,y,x+size_x-1,y+size_y-1);
		 
		for(i=0;i<size_x;i++) //x
			{
			for (j=size_y*size_x-size_x; j!=0; j-=size_x) //y
				{
				color=*(image+i+j);
				WRITE_DATA_FAST_1B((color & 0xF8) | (color >> 5) );
				WRITE_DATA_FAST_1B(((color << 3) & 0xE0 ) | (color >>3));
				}
			color = *(image+i+j);
			WRITE_DATA_FAST_1B((color & 0xF8) | (color >> 5));
			WRITE_DATA_FAST_1B(((color << 3) & 0xE0 ) | (color >>3));
			}
		}
//Вывод серого изображения повернутого на 180 градусов 
void G_print_image_gray_r180grad(const unsigned char   *image,uint16_t size_x, uint16_t size_y,uint16_t x,uint16_t y)
		{
		uint16_t volatile i,j,temp,temp2;
		unsigned char color;
		LCD_set_window(x,y,x+size_x-1,y+size_y-1);
		 
		for(i=size_y*size_x-size_x;i!=0;i-=size_x) // шаг по игрЫку по строкам
			{
			for (j=size_x-1;j!=0;j--) //шаг по иксу по столбцам
				{
				color = *(image+i+j);
				WRITE_DATA_FAST_1B( (color & 0xF8) | (color >> 5));
				WRITE_DATA_FAST_1B( ((color << 3) & 0xE0 ) | (color >>3));
				}
			color = *(image+i+j);
			WRITE_DATA_FAST_1B( (color & 0xF8) | (color >> 5));
			WRITE_DATA_FAST_1B(((color << 3) & 0xE0 ) | (color >>3));
			}
			
			for (j=size_x-1;j!=0;j--) //шаг по иксу по столбцам
				{
				color = *(image+i+j);
				WRITE_DATA_FAST_1B((color & 0xF8) | (color >> 5));
				WRITE_DATA_FAST_1B(((color << 3) & 0xE0 ) | (color >>3));
				}
			color = *(image+i+j);
			WRITE_DATA_FAST_1B((color & 0xF8) | (color >> 5)); 
			WRITE_DATA_FAST_1B(((color << 3) & 0xE0 ) | (color >>3));
		}
//Вывод серого изображения повернутого на 270 градусов 
void G_print_image_gray_r270grad(unsigned char *image,uint16_t size_x,uint16_t size_y,uint16_t x,uint16_t y)
		{
		uint16_t volatile i,j,temp2;
		unsigned char color;
		LCD_set_window(x,y,x+size_x-1,y+size_y-1);

		temp2=size_y*size_x;

		for(i=size_x-1; i!=0; i--) //x
			{
			for (j=0; j<temp2; j+=size_x) //y
				{
				color = *(image+i+j);
				WRITE_DATA_FAST_1B( (color & 0xF8) | (color >> 5));
				WRITE_DATA_FAST_1B( ((color << 3) & 0xE0 ) | (color >>3));
				}
			}
			for (j=0; j<temp2; j+=size_x) //y
				{
				color = *(image+i+j);
				WRITE_DATA_FAST_1B((color & 0xF8) | (color >> 5));
				WRITE_DATA_FAST_1B(((color << 3) & 0xE0 ) | (color >>3));
				}
		}

