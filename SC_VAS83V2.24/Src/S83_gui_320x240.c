#include "S83_gui.h"
#include "S83_user_icons_16x16.h"
#include "S83_user_icons_48x48.h"
#include "S83_graphics.h"
#include "S83_main_data.h"


#define POS_X_STR_2 4


//Напечатать интерфейс пользователя
void GUI_print_static_text(void)
	{
		//GUI_print_time_PB(50);
		//G_print_string_len_f8x12("Файл:",4,204,5,COLOR_WHITE,COLOR_BLACK);
		//G_print_image_gray(boot_0_grad,48,48,100,100);
		G_print_string_len_f8x12("Время:",POS_X_STR_2,220,6,COLOR_WHITE,COLOR_BLACK);
	}
	

	//Анимация - Загрузка
void GUI_loading (void)
{
uint16_t x,y,t=110;
x=80;
y=96;

G_fill_rectangle(0,0,319,239,COLOR_BLACK);
G_print_string_len_f8x12("ЗАГРУЗКА...",140,115,11,COLOR_WHITE,COLOR_BLACK);

while(!flag_ready_gui_frame)
    {
		G_print_image_gray(boot_0_grad,48,48,x,y);
		delay(t);
		G_print_image_gray(boot_45_grad,48,48,x,y);
		delay(t);
		G_print_image_gray_r90grad(boot_0_grad,48,48,x,y);
		delay(t);
		G_print_image_gray_r90grad(boot_45_grad,48,48,x,y);
		delay(t);
		G_print_image_gray_r180grad(boot_0_grad,48,48,x,y);
		delay(t);
		G_print_image_gray_r180grad(boot_45_grad,48,48,x,y);
		delay(t);
		G_print_image_gray_r270grad(boot_0_grad,48,48,x,y);
		delay(t);
		G_print_image_gray_r270grad(boot_45_grad,48,48,x,y);
		delay(t);
		}
G_fill_rectangle(0,0,319,239,COLOR_BLACK);		
}



void GUI_print_interface(void)
	{ 
	char str_emp[]="                                ";//32
	#define STEP_Y	20
	
	#define POS_X_IMG  3	
	#define POS_X_STR  22
	
	#define POS_Y_STR_INFO 204
		
	#define DISPLAY_DAC 0
	#define DISPLAY_FILE 1
	#define DISPLAY_GAIN 2
	#define DISPLAY_RANDOM 3
	#define DISPLAY_REPEATE 4
	#define DISPLAY_EQ 5	
		
	uint16_t POS_Y_STR = 4;
	uint16_t POS_Y_IMG = 2;

	const unsigned char *current_image;
	uint8_t i;
	
	//рисуем строки и иконки
	for (i=0;i<10;i++)
		{	
		if(ZEROSTRING(i))
			{
			GUI_clear_string(i);
			}
		else	
				{			
				//выбираем иконку
				switch (ICON(i))
					{
					case ICON_BACK:				current_image = image_back_16x16; break;
					case ICON_FOLDER:			current_image = image_folder_16x16; break;
					case ICON_FILE:				current_image = image_file_16x16; break;
					case ICON_PLAYING:		current_image = image_play_16x16; 	break;
					case ICON_PAUSE:			current_image = image_pause_16x16; break;
					case ICON_POFF:				current_image = image_POFF_16x16; break;
					
					}
				G_print_image(current_image,16,16,POS_X_IMG,POS_Y_IMG);
				G_print_string_len_f8x12(pDATA(i),POS_X_STR,POS_Y_STR,29,*pCOLOR(i),COLOR_BLACK);
				if (CURSOR(i))	GUI_print_cursor(i);
				else						GUI_clear_cursor(i);
				}
		POS_Y_STR += STEP_Y;
		POS_Y_IMG += STEP_Y;
		}
		//Полоса прокрутки
		GUI_print_scroll_bar(percent_pos_cursor, percent_window);
		//Прогресбар времени
		GUI_print_time_PB(percent_time);
		//Время
		G_print_string_len_f8x12(pString_time,149,220,17,COLOR_YELLOW,COLOR_BLACK);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		#define DALAY_SEC 7	//задержка в количествах кадров (секундах) кадр приходит не поз же одного раза в секунду
		static uint16_t frame_counter=0;
		frame_counter++;
		if (frame_counter == DALAY_SEC) frame_counter = 0;
		
		static uint16_t type_string_for_display;
		
		//Определим что за чем показывать в информационной строке
		if (frame_counter == 0) 
			{
				switch (type_string_for_display)
					{
					case DISPLAY_DAC:		type_string_for_display = DISPLAY_FILE; break;
					case DISPLAY_FILE:	type_string_for_display = DISPLAY_DAC;	break;
					default: type_string_for_display = DISPLAY_FILE;
					}
			}
		
		static uint32_t pre_random = -1;
		if ((Flags_data &  F_RANDOM) != pre_random)	
			{
			frame_counter = 1;	
			type_string_for_display = DISPLAY_RANDOM;
			pre_random = (Flags_data &  F_RANDOM);	
			}
			
		static uint32_t pre_repeate = -1;
		if ((Flags_data &  F_REPEATE) != pre_repeate)	
			{
			frame_counter = 1;	
			type_string_for_display = DISPLAY_REPEATE;
			pre_repeate = (Flags_data &  F_REPEATE);	
			}
			
		static uint32_t pre_eq = -1;
		if ((Flags_data &  F_EQ) != pre_eq)	
			{
			frame_counter = 1;	
			type_string_for_display = DISPLAY_EQ;	
			pre_eq = (Flags_data &  F_EQ);	
			}
			
		static uint32_t pre_db = -1;		
		if (pre_db != *((uint32_t*)pVolume_db))	
			{
			type_string_for_display = DISPLAY_GAIN;
			frame_counter = 1;
			pre_db = *((uint32_t*)pVolume_db);
			}	
			
		
			
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		
			
		if (type_string_for_display == DISPLAY_DAC)	
				{
				uint16_t t_clr;
				t_clr = COLOR_WHITE;
				//ЦАП
				G_print_string_len_f8x12("ЦАП: ",POS_X_STR_2,POS_Y_STR_INFO,5,COLOR_WHITE,COLOR_BLACK);
				//ЦАП Чачтота
				if (Dac_Freq != File_Frec) t_clr = COLOR_BRRED;
				switch(Dac_Freq)
					{
					case SR_32000:		G_print_string_len_f8x12((char*)sr_32000,POS_X_STR_2+50,POS_Y_STR_INFO,6,t_clr,COLOR_BLACK); break;
					case SR_44100:		G_print_string_len_f8x12((char*)sr_44100,POS_X_STR_2+50,POS_Y_STR_INFO,6,t_clr,COLOR_BLACK); break;
					case SR_88200:		G_print_string_len_f8x12((char*)sr_88200,POS_X_STR_2+50,POS_Y_STR_INFO,6,t_clr,COLOR_BLACK); break;	
					case SR_176400:		G_print_string_len_f8x12((char*)sr_176400,POS_X_STR_2+50,POS_Y_STR_INFO,6,t_clr,COLOR_BLACK); break;
					case SR_352800:		G_print_string_len_f8x12((char*)sr_352800,POS_X_STR_2+50,POS_Y_STR_INFO,6,t_clr,COLOR_BLACK); break;
						
					case SR_48000:		G_print_string_len_f8x12((char*)sr_48000,POS_X_STR_2+50,POS_Y_STR_INFO,6,t_clr,COLOR_BLACK); break;
					case SR_96000:		G_print_string_len_f8x12((char*)sr_96000,POS_X_STR_2+50,POS_Y_STR_INFO,6,t_clr,COLOR_BLACK); break;
					case SR_192000:		G_print_string_len_f8x12((char*)sr_192000,POS_X_STR_2+50,POS_Y_STR_INFO,6,t_clr,COLOR_BLACK); break;
					case SR_384000:		G_print_string_len_f8x12((char*)sr_384000,POS_X_STR_2+50,POS_Y_STR_INFO,6,t_clr,COLOR_BLACK); break;
						
					default: 					G_print_string_len_f8x12((char*)sr_0,POS_X_STR_2+50,POS_Y_STR_INFO,6,t_clr,COLOR_BLACK); break;
					}
				G_print_string_len_f8x12("КГц. ",POS_X_STR_2+110,POS_Y_STR_INFO,5,COLOR_YELLOW,COLOR_BLACK);	
					
				//ЦАП Бит данных	
				switch(Dac_Bit)
					{
					case 16:					G_print_string_len_f8x12("16 ",POS_X_STR_2+160,POS_Y_STR_INFO,3,COLOR_WHITE,COLOR_BLACK); break;
					case 24:					G_print_string_len_f8x12("24 ",POS_X_STR_2+160,POS_Y_STR_INFO,3,COLOR_WHITE,COLOR_BLACK); break;
					case 32:					G_print_string_len_f8x12("32 ",POS_X_STR_2+160,POS_Y_STR_INFO,3,COLOR_WHITE,COLOR_BLACK); break;
					default: 					G_print_string_len_f8x12(" 0 ",POS_X_STR_2+160,POS_Y_STR_INFO,3,COLOR_WHITE,COLOR_BLACK); break;
					}
				G_print_string_len_f8x12("Бит.        ",POS_X_STR_2+190,POS_Y_STR_INFO,12,COLOR_YELLOW,COLOR_BLACK);		
				}	
				
		if (type_string_for_display == DISPLAY_FILE)	
				{
				G_print_string_len_f8x12("Файл: ",POS_X_STR_2,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK);
				//Файл - частота
				
					switch(File_Frec)
						{
						case SR_32000:		G_print_string_len_f8x12((char*)sr_32000,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;
						case SR_48000:		G_print_string_len_f8x12((char*)sr_48000,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;
						case SR_96000:		G_print_string_len_f8x12((char*)sr_96000,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;
						case SR_192000:		G_print_string_len_f8x12((char*)sr_192000,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;
						case SR_384000:		G_print_string_len_f8x12((char*)sr_384000,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;

						case SR_44100:		G_print_string_len_f8x12((char*)sr_44100,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;
						case SR_88200:		G_print_string_len_f8x12((char*)sr_88200,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;
						case SR_176400:		G_print_string_len_f8x12((char*)sr_176400,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;
						case SR_352800:		G_print_string_len_f8x12((char*)sr_352800,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;
						case SR_705600:		G_print_string_len_f8x12((char*)sr_705600,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;	
							
						default: 					G_print_string_len_f8x12((char*)sr_0,POS_X_STR_2+60,POS_Y_STR_INFO,6,COLOR_WHITE,COLOR_BLACK); break;
						}
				G_print_string_len_f8x12("КГц. ",POS_X_STR_2+120,POS_Y_STR_INFO,5,COLOR_YELLOW,COLOR_BLACK);	
				//файл битрейт
				G_print_string_len_f8x12(pFileBitrate,POS_X_STR_2+170,POS_Y_STR_INFO,7,COLOR_WHITE,COLOR_BLACK);
				G_print_string_len_f8x12(" кб/с. ",POS_X_STR_2+240,POS_Y_STR_INFO,7,COLOR_YELLOW,COLOR_BLACK);		
				}
				
			//Усиление в децибелах
			if (type_string_for_display == DISPLAY_GAIN)	
				{
				//G_print_string_len_f8x12("*",POS_X_STR_2+310,POS_Y_STR_INFO,1,COLOR_WHITE,COLOR_BLACK);	
				G_print_string_len_f8x12("Усиление: ",POS_X_STR_2,POS_Y_STR_INFO,10,COLOR_WHITE,COLOR_BLACK);					
				G_print_string_len_f8x12(pVolume_db,POS_X_STR_2+100,POS_Y_STR_INFO,5,COLOR_WHITE,COLOR_BLACK);
				G_print_string_len_f8x12(" Дб.            ",POS_X_STR_2+150,POS_Y_STR_INFO,16,COLOR_YELLOW,COLOR_BLACK);
				}		
				
			//Случайный порядок	
			#define clr_on COLOR_GREEN
			#define clr_off COLOR_RED	
			uint16_t clr_current;	
			if (type_string_for_display == DISPLAY_RANDOM)
				{
				G_print_string_len_f8x12("Случайный порядок: ",POS_X_STR_2,POS_Y_STR_INFO,19,COLOR_WHITE,COLOR_BLACK);			
				
				if (Flags_data &  F_RANDOM)		
					{
					clr_current = clr_on;
					G_print_string_len_f8x12("Включено.    ",POS_X_STR_2+190,POS_Y_STR_INFO,12,clr_current,COLOR_BLACK);
					}
				else 													
					{
					clr_current = clr_off;
					G_print_string_len_f8x12("Выключено.   ",POS_X_STR_2+190,POS_Y_STR_INFO,12,clr_current,COLOR_BLACK);
					}
				}
				
				
				//Повтор списка
				if (type_string_for_display == DISPLAY_REPEATE)
					{
					G_print_string_len_f8x12("Повтор списка: ",POS_X_STR_2,POS_Y_STR_INFO,15,COLOR_WHITE,COLOR_BLACK);			
					
					if (Flags_data &  F_REPEATE)		
						{
						clr_current = clr_on;
						G_print_string_len_f8x12("Включено.        ",POS_X_STR_2+150,POS_Y_STR_INFO,16,clr_current,COLOR_BLACK);
						}
					else 													
						{
						clr_current = clr_off;
						G_print_string_len_f8x12("Выключено.       ",POS_X_STR_2+150,POS_Y_STR_INFO,16,clr_current,COLOR_BLACK);
						}
					}
					
					
				//Эквалайзер
				if (type_string_for_display == DISPLAY_EQ)
					{
					G_print_string_len_f8x12("Эквалайзер: ",POS_X_STR_2,POS_Y_STR_INFO,12,COLOR_WHITE,COLOR_BLACK);			
					
					if (Flags_data &  F_EQ)		
						{
						clr_current = clr_on;
						G_print_string_len_f8x12("Включено.          ",POS_X_STR_2+120,POS_Y_STR_INFO,19,clr_current,COLOR_BLACK);
						}
					else 													
						{
						clr_current = clr_off;
						G_print_string_len_f8x12("Выключено.         ",POS_X_STR_2+120,POS_Y_STR_INFO,19,clr_current,COLOR_BLACK);
						}
					}
}
	

//Напечатать курсор
#define  x_start 0
#define  h_cursor 18 	//Высота курсора
#define  len 319-9 		//Длина курсора (координата конца)
//Напечатать курсор
void GUI_print_cursor(uint32_t index)
	{
	unsigned char y; 	
	y=index * (h_cursor+2);

		G_print_h_line(x_start+1,y,len+1,COLOR_GRAY);
	G_print_h_line(x_start+2,y+1,len,COLOR_WHITE);
		
	G_print_h_line(x_start+1,y + h_cursor,len+1,COLOR_WHITE);
	G_print_h_line(x_start+1,y + h_cursor+1,len+1,COLOR_GRAY);

	//Лево
	G_print_v_line(x_start,y+1,h_cursor-1,COLOR_GRAY);
	G_print_v_line(x_start+1,y+1,h_cursor-2,COLOR_WHITE);
	//Право
	G_print_v_line(x_start+len+2,y+1,h_cursor-2,COLOR_WHITE);
	G_print_v_line(x_start+len+1+2,y+1,h_cursor-1,COLOR_GRAY);
	}
	
//Стереть курсор
void GUI_clear_cursor(uint32_t index)
	{
	unsigned char y; 	
	y=index * (h_cursor+2);

	G_print_h_line(x_start+1,y,len+1,COLOR_BLACK);
	G_print_h_line(x_start+2,y+1,len,COLOR_BLACK);
		
	G_print_h_line(x_start+1,y + h_cursor,len+1,COLOR_BLACK);
	G_print_h_line(x_start+1,y + h_cursor+1,len+1,COLOR_BLACK);

	//Лево
	G_print_v_line(x_start,y+1,h_cursor-1,COLOR_BLACK);
	G_print_v_line(x_start+1,y+1,h_cursor-2,COLOR_BLACK);
	//Право
	G_print_v_line(x_start+len+2,y+1,h_cursor-2,COLOR_BLACK);
	G_print_v_line(x_start+len+1+2,y+1,h_cursor-1,COLOR_BLACK);
	}
	
//Стереть строку
void GUI_clear_string(uint32_t index)
	{
	unsigned char y; 	
	y=index * (h_cursor+2);
	G_fill_rectangle(x_start, y, x_start+len+1+2, y+h_cursor+1, COLOR_BLACK);	
	}
	
#define POS_X_SB 316	//координата по X
#define POS_Y_SB 2	  //координата по Y
#define W_SB 2				//ширина
#define H_SB 198			//высота
#define CL_TS	0x5AEB					//цвет темных столбиков
#define CL_SS	COLOR_WHITE			//цвет светлого столбика
void GUI_print_scroll_bar(uint8_t arg_p_pos_cursor, uint8_t arg_p_window)	
	{
	uint32_t hactst;
	uint32_t y_pos_actst;
	uint32_t H_SB_max;//Высота бара за вычетом высоты активного столбика
	
	//Вычислим высоту активного столбика
	hactst =	(arg_p_window * H_SB)/100;
	if (hactst<4) hactst =4 ; //минимальная высота - чтобы было его видно когда много файлов
	H_SB_max = H_SB - hactst; 
	
	//вычисляем координату по y от начала столбика
	
	y_pos_actst = (arg_p_pos_cursor * H_SB_max)/100;
	if(arg_p_window == 100) 
		{
		//стираем бар	
		G_fill_rectangle(POS_X_SB,POS_Y_SB,POS_X_SB+W_SB,POS_Y_SB + H_SB,COLOR_BLACK);
		}
	else
		{
		//стираем бар серым	
		G_fill_rectangle(POS_X_SB,POS_Y_SB,POS_X_SB+W_SB,POS_Y_SB + H_SB,CL_TS);
		//рисуем светлый столбик
		G_fill_rectangle(POS_X_SB,POS_Y_SB + y_pos_actst,POS_X_SB+W_SB,y_pos_actst + hactst,CL_SS);
		}
	}
	
#define xl 4
#define xr 316
#define ypos 235
	
void GUI_print_time_PB(uint32_t arg_percent)
	{
	static uint32_t pre_percent;
		
	if(arg_percent < pre_percent)	
	G_fill_rectangle(xl, ypos, xr, ypos+2,CL_TS);
	
	
	G_fill_rectangle(xl, ypos, xl + arg_percent * (xr-xl)/100, ypos+2,COLOR_GREEN);
	pre_percent = arg_percent;
	}	
	
//Узнать разрешение экрана	в символах
uint32_t GUI_get_string_len(void)
	{
	return 30;
	}

void GUI_print_poff_screen(void)
	{
	G_clear_screen(COLOR_BLACK);
	G_print_string_len_f8x12("ЗАВЕРШЕНИЕ РАБОТЫ.",80,115,18,COLOR_WHITE,COLOR_BLACK);	
	}