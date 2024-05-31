#include "S83_configuration.h"
#include "S83_graphics.h"
#include "S83_themes.h"

char sr_32000[] 	= {" 32.0 "};
char sr_44100[] 	= {" 44.1 "};
char sr_48000[] 	= {" 48.0 "};
char sr_88200[] 	= {" 88.2 "};
char sr_96000[] 	= {" 96.0 "};
char sr_176400[] 	= {"176.4 "};
char sr_192000[] 	= {"192.0 "};
char sr_352800[] 	= {"352.8 "};
char sr_384000[] 	= {"384.0 "};
char sr_705600[] 	= {"705.6 "};
char sr_0[] 			= {"  0.0 "};

void GUI_init(void)
	{
	//Раскраска интерфейса
	curr_theme.color_txt_par 						= COLOR_WHITE;
	curr_theme.color_txt_par_value 			= COLOR_YELLOW;
	curr_theme.color_txt_par_value_wrng = COLOR_BRRED;		
	curr_theme.color_progress_bar 			= COLOR_GREEN;
	}
	


#ifdef CONFIG_GUI_480x320
#define  H_CHAR 16  	//Ширина символов	
#define  X_MAXG 479
#define  Y_MAXG	319
#include "S83_gui_480x320.c"
#endif

#ifdef CONFIG_GUI_320x240
#define  H_CHAR 12  	//Ширина символов
#define  X_MAXG 319
#define  Y_MAXG	239	
#include "S83_gui_320x240.c"
#endif

#define  W_CHAR 10  	//Ширина символов	
#define  MG2_CHAR 6 	//Отступ в символах слева + справа 	
	
int toast_x = 50;
int toast_y = 50;
int toast_width = 200;
int toast_heith = 50;

uint8_t toast_ch_max = X_MAXG / W_CHAR - MG2_CHAR; //Максимальное количество символов	


	

void GUI_print_toast(char* arg_msg, uint8_t arg_len, uint16_t arg_color)
	{
	if (arg_len > toast_ch_max) 
		arg_len = toast_ch_max; //Проверка и коректировка длины сообщения
	flag_len_toast = arg_len;
	
	toast_width = (arg_len + 4) * W_CHAR; 							//Ширина окошка = ширина текста и по 2 символа слева и с права
	toast_y = (Y_MAXG - toast_heith) / 2;								//y - позиция сообщения
	toast_x = (X_MAXG - toast_width) / 2;     
	//Фон
	G_fill_rectangle(toast_x, toast_y, toast_x + toast_width, toast_y + toast_heith, COLOR_BLACK);
	//Текст
	#ifdef CONFIG_GUI_480x320
	G_print_string_len_f8x16(arg_msg, toast_x + W_CHAR * 2, toast_y + (toast_heith - H_CHAR)/2 , arg_len, arg_color, COLOR_BLACK);
	#endif
	#ifdef CONFIG_GUI_320x240
	G_print_string_len_f8x12(arg_msg, toast_x + W_CHAR * 2, toast_y + (toast_heith - H_CHAR)/2 , arg_len, arg_color, COLOR_BLACK);
	#endif
	//Обрамеление сообщения
	G_fill_rectangle(toast_x, toast_y, toast_x + toast_width, toast_y + 1, COLOR_WHITE);
	G_fill_rectangle(toast_x, toast_y + toast_heith - 1, toast_x + toast_width, toast_y + toast_heith, COLOR_WHITE);
	G_fill_rectangle(toast_x, toast_y, toast_x + 1, toast_y + toast_heith, COLOR_WHITE);
	G_fill_rectangle(toast_x + toast_width - 1, toast_y, toast_x + toast_width, toast_y + toast_heith, COLOR_WHITE);
	}
	
void GUI_clear_toast(void)
	{
	G_fill_rectangle(toast_x,toast_y, toast_x + toast_width, toast_y + toast_heith, COLOR_BLACK);
	
	}	