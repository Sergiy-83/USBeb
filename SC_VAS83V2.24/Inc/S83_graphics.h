#ifndef GRAPH_H
#define GRAPH_H
#include "stdint.h"
#include "S83_lcd.h"

#define COLOR_WHITE       0xFFFF
#define COLOR_BLACK      	0x0000	  
#define COLOR_BLUE       	0x001F  
#define COLOR_BRED        0xF81F
#define COLOR_GRED 			 	0xFFE0
#define COLOR_GBLUE			 	0x07FF
#define COLOR_RED         0xF800
#define COLOR_MAGENTA     0xF81F
#define COLOR_GREEN       0x07E0
#define COLOR_CYAN        0x7FFF
#define COLOR_YELLOW      0xFFE0
#define COLOR_BROWN 			0xBC40
#define COLOR_BRRED 			0xFC07
#define COLOR_GRAY  			0x8430

#define COLOR_DARKBLUE    0x01CF
#define COLOR_LIGHTBLUE   0x7D7C
#define COLOR_GRAYBLUE    0x5458
 
#define COLOR_LIGHTGREEN  0x841F
#define COLOR_LIGHTGRAY   0xEF5B
#define COLOR_LGRAY 			0xC618

#define COLOR_LGRAYBLUE   0xA651
#define COLOR_LBBLUE      0x2B12

#ifdef CONFIG_S83_FONT_8x12	
void G_print_sym_f8x12(uint8_t sym,uint16_t x,uint16_t y,uint16_t color,uint16_t b_color);
void G_print_string_len_f8x12(char *sym,uint16_t x,uint16_t y,uint16_t len,uint16_t color,uint16_t b_color);
#endif

#ifdef CONFIG_S83_FONT_8x16
void G_print_sym_f8x16(uint8_t sym,uint16_t x,uint16_t y,uint16_t color,uint16_t b_color);
void G_print_string_len_f8x16(char *sym,uint16_t x,uint16_t y,uint16_t len,uint16_t color,uint16_t b_color);
#endif

void G_fill_rectangle(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t color);
void G_clear_screen(uint16_t arg_color);
void G_print_image(const unsigned char *image,uint16_t size_x,uint16_t size_y,uint16_t x,uint16_t y);

#define	G_print_h_line(X,Y,L,C)			G_fill_rectangle(X,Y,X+L,Y,C)
#define	G_print_v_line(X,Y,L,C)			G_fill_rectangle(X,Y,X,Y+L,C)	

//void GUI_print_image(const char *image,unsigned int size_x,unsigned int size_y,unsigned int x,unsigned int y);
//void GUI_print_image_gray_05(const char *image,unsigned int size_x, unsigned int size_y,unsigned int x,unsigned int y);
//void GUI_CLEAR_SCREEN(uint32_t color);
//void GUI_FILL_RECTANGLE(uint32_t x0,uint32_t y0,uint32_t x1,uint32_t y1,uint32_t color);












#endif
