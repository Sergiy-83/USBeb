#ifndef S83_THEMES_H_
#define S83_THEMES_H_

#include "stdint.h"

struct va_theme
	{
	uint16_t color_txt_par;				//Цвет имени параметра
	uint16_t color_txt_par_value;		//Значение параметра
	uint16_t color_txt_par_value_wrng;	//Выделенное значение	
	uint16_t color_progress_bar;	//Цвет колонки прогресбара				
	};

extern struct va_theme curr_theme; 

#endif