#include <stdbool.h>
#include "stdio.h"
#include "tim.h"

#include "S83_gui.h"
#include "S83_user_icons_24x20.h"
#include "S83_user_icons_48x48.h"
#include "S83_graphics.h"
#include "S83_main_data.h"
#include "S83_themes.h"

	
#define POS_Y_STR_DAC   250
#define POS_Y_STR_FILE  272
#define POS_Y_STR_TIME  294

uint16_t pre_sr_dac  	= -1;
uint16_t pre_dac_bit 	= -1;
uint16_t pre_freq_f 	= -1;
uint16_t pre_codec 		= -1;
uint16_t pre_flags 		=	-1;


//Напечатать интерфейс пользователя
void GUI_print_static_text(void)
		{	
		pre_sr_dac 	= -1;			
		pre_dac_bit = -1;
		pre_freq_f	= -1;
		pre_codec 	= -1;
		pre_flags 	=	-1;
			
		G_print_h_line(5,242,465,COLOR_GRAY);
		G_print_image(image_vol_24x20,24,20,250,POS_Y_STR_DAC-2);
		G_print_string_len_f8x16("ЦАП:",4,POS_Y_STR_DAC,4,curr_theme.color_txt_par,COLOR_BLACK);
		G_print_string_len_f8x16("Файл:",4,POS_Y_STR_FILE,5,curr_theme.color_txt_par,COLOR_BLACK);
		G_print_string_len_f8x16("Время:",4,POS_Y_STR_TIME,6,curr_theme.color_txt_par,COLOR_BLACK);
		G_print_string_len_f8x16("КГц.",120,POS_Y_STR_DAC,4,curr_theme.color_txt_par_value,COLOR_BLACK);
		G_print_string_len_f8x16("КГц.",120,POS_Y_STR_FILE,4,curr_theme.color_txt_par_value,COLOR_BLACK);
		G_print_string_len_f8x16("Дб.",340,POS_Y_STR_DAC,3,curr_theme.color_txt_par_value,COLOR_BLACK);
		G_print_string_len_f8x16("Бит.",200,POS_Y_STR_DAC,4,curr_theme.color_txt_par_value,COLOR_BLACK);
		G_print_string_len_f8x16("кб/с.",250,POS_Y_STR_FILE,5,curr_theme.color_txt_par_value,COLOR_BLACK);
		}
	
//Анимация - Загрузка
//#define CLEAR_SCREEN G_fill_rectangle(0,0,479,319,COLOR_BLACK)
void GUI_loading (void)
		{
		uint16_t x,y;
		uint16_t t=110; //Задержка между кадрами анимации.
		x=140;
		y=136;

		G_clear_screen(COLOR_BLACK);
		G_print_string_len_f8x16("ЗАГРУЗКА...",210,152,11,COLOR_WHITE,COLOR_BLACK);

		while(!flag_ready_gui_frame) //анимация пока не придет первый кадр
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
		G_clear_screen(COLOR_BLACK);	
		}



			
 char af_null[] =  {" Недоступно.     "};
 char af_flac[] =  {" Free Lossless.  "};
 char af_m4a[]  =  {"Apple Lossless.  "};
 char af_wav[] = 	{"Uncompressed PCM."};
 char af_ogg[] = 	{" Vorbis Audio.   "};
 char af_aac[] = 	{"AAC MPEG2 Audio. "};
 char af_ac3[] = 	{"AC3 Dolby Digital"};
 char af_mp3[] = 	{" MPEG Layer 3.   "};
 char af_wv[]  = 	{" WavPack Audio.  "};
 char af_wma[] = 	{" Windows Media.  "};
 char af_ape[] = 	{" Monkey's Audio. "};
 char af_mpc[] = 	{" MusePack Audio. "};
 char af_dsd[] = 	{"  DSD Audio.     "};
 char af_dts[] = 	{" DTS(DCA) Audio. "};
													


			
void GUI_print_interface(void)
	{
	char str_emp[]="                                            ";//44 пустая строка
	char *tmp_codec_str;
		
	#define STEP_Y			24	//растояние между строками
	#define POS_X_IMG  	3		//позиция x иконки 
	#define POS_X_STR  	29	//позиция x строки
		
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
					case ICON_BACK:				current_image = image_back_24x20; 	break;
					case ICON_FOLDER:			current_image = image_folder_24x20; break;
					case ICON_FILE:				current_image = image_spk_24x20; 		break;
					case ICON_PLAYING:		current_image = image_play_24x20; 	break;
					case ICON_PAUSE:			current_image = image_pause_24x20; break;
					case ICON_POFF:				current_image = image_POFF_24x20; break;
					
					}
				G_print_image(current_image,24,20,POS_X_IMG,POS_Y_IMG);
				G_print_string_len_f8x16(pDATA(i),POS_X_STR,POS_Y_STR,44,*pCOLOR(i),COLOR_BLACK);
				
				#ifdef CONFIG_VOL_ENCODER_MODE_2
					if (CURSOR(i))	
						{
							if (flag_mode_vol_encoder == VOLUME_ENC_MODE_CURSOR)	GUI_print_cursor(i);
							else 																								GUI_clear_cursor(i);
						}
					else	GUI_clear_cursor(i);
				#else 
					if (CURSOR(i))	GUI_print_cursor(i);
					else						GUI_clear_cursor(i);	
				#endif	
				}
		POS_Y_STR += STEP_Y;
		POS_Y_IMG += STEP_Y;
		}
		//Полоса прокрутки
		GUI_print_scroll_bar(percent_pos_cursor, percent_window);
		//Прогресбар времени
		GUI_print_time_PB(percent_time);
		
		//Время
		G_print_string_len_f8x16(pString_time,308,POS_Y_STR_TIME,17,curr_theme.color_txt_par_value,COLOR_BLACK);
		//Строка текстовая над временем
		
		
		
		
		
		//ЦАП Чачтота////////////////////////////////////////////////////////////////////////////////////////////
		char *tmp_str_sr_dac;
		uint16_t t_clr;
	
		if (pre_sr_dac != Dac_Freq)
			{
			if (Dac_Freq != File_Frec) t_clr = curr_theme.color_txt_par_value_wrng;
			else 											 t_clr = curr_theme.color_txt_par_value;
				
			switch(Dac_Freq)
				{
				case SR_32000:		tmp_str_sr_dac = (char*)sr_32000; break;
				case SR_44100:		tmp_str_sr_dac = (char*)sr_44100; break;
				case SR_48000:		tmp_str_sr_dac = (char*)sr_48000; break;
				case SR_88200:		tmp_str_sr_dac = (char*)sr_88200; break;
				case SR_96000:		tmp_str_sr_dac = (char*)sr_96000; break;
				case SR_176400:		tmp_str_sr_dac = (char*)sr_176400; break;
				case SR_192000:		tmp_str_sr_dac = (char*)sr_192000; break;
				case SR_352800:		tmp_str_sr_dac = (char*)sr_352800; break;
				case SR_384000:		tmp_str_sr_dac = (char*)sr_384000; break;
				default: 					tmp_str_sr_dac = (char*)sr_0; break;
				}
			G_print_string_len_f8x16(tmp_str_sr_dac,60,POS_Y_STR_DAC,5,t_clr,COLOR_BLACK);
			pre_sr_dac = Dac_Freq;	
			}
			
		//ЦАП Бит данных	/////////////////////////////////////////////////////////////////////////////////////////
			if(pre_dac_bit != Dac_Bit)
				{
					if (Dac_Bit != File_Bit) t_clr = curr_theme.color_txt_par_value_wrng;
					else 										 t_clr = curr_theme.color_txt_par_value; 
					switch(Dac_Bit)
						{
						case 16:					G_print_string_len_f8x16("16",170,POS_Y_STR_DAC,2,t_clr,COLOR_BLACK); break;
						case 24:					G_print_string_len_f8x16("24",170,POS_Y_STR_DAC,2,t_clr,COLOR_BLACK); break;
						case 32:					G_print_string_len_f8x16("32",170,POS_Y_STR_DAC,2,t_clr,COLOR_BLACK); break;
						default: 					G_print_string_len_f8x16(" 0",170,POS_Y_STR_DAC,2,t_clr,COLOR_BLACK); break;
						}
				pre_dac_bit = Dac_Bit;		
				}
		//Усиление в децибелах/////////////////////////////////////////////////////////////////////////////////////
		G_print_string_len_f8x16(pVolume_db,280,POS_Y_STR_DAC,5,curr_theme.color_txt_par_value,COLOR_BLACK);
		
		#ifdef CONFIG_VOL_ENCODER_MODE_2
		if (flag_mode_vol_encoder == VOLUME_ENC_MODE_CURSOR) GUI_clear_cursor_2();
		else																								 GUI_print_cursor_2();
		#endif	
			
  	//Файл - частота //////////////////////////////////////////////////////////////////////////////////////////
			
		char *tmp_str_sr_file;	
		if (pre_freq_f != File_Frec)
			{
			switch(File_Frec)
				{
				case SR_32000:		tmp_str_sr_file = (char*)sr_32000; break;
				case SR_44100:		tmp_str_sr_file = (char*)sr_44100; break;
				case SR_48000:		tmp_str_sr_file = (char*)sr_48000; break;
				case SR_88200:		tmp_str_sr_file = (char*)sr_88200; break;
				case SR_96000:		tmp_str_sr_file = (char*)sr_96000; break;
				case SR_176400:		tmp_str_sr_file = (char*)sr_176400; break;
				case SR_192000:		tmp_str_sr_file = (char*)sr_192000; break;
				case SR_352800:		tmp_str_sr_file = (char*)sr_352800; break;
				case SR_384000:		tmp_str_sr_file = (char*)sr_384000; break;
				case SR_705600:		tmp_str_sr_file = (char*)sr_705600; break;	
				default: 					tmp_str_sr_file = (char*)sr_0; break;
				}
			G_print_string_len_f8x16(tmp_str_sr_file,60,POS_Y_STR_FILE,5,curr_theme.color_txt_par_value,COLOR_BLACK);	
			pre_freq_f = File_Frec;	
			}
			
			//Файл - битрейт ////////////////////////////////////////////////////////////////////////////////////////
			G_print_string_len_f8x16(pFileBitrate,170,POS_Y_STR_FILE,7,curr_theme.color_txt_par_value,COLOR_BLACK);
			
			//Файл - Кодек //////////////////////////////////////////////////////////////////////////////////////////
			
			if (pre_codec != File_Codec)
				{
				switch (File_Codec)
					{
					case AF_FLAC: tmp_codec_str = (char*)af_flac; break; 
					case AF_M4A:	tmp_codec_str = (char*)af_m4a; break; 
					case AF_WAV:	tmp_codec_str = (char*)af_wav; break; 
					case AF_OGG:	tmp_codec_str = (char*)af_ogg; break; 
					case AF_AAC:	tmp_codec_str = (char*)af_aac; break; 
					case AF_AC3:  tmp_codec_str = (char*)af_ac3; break; 
					case AF_MP3:  tmp_codec_str = (char*)af_mp3; break; 
					case AF_WV:   tmp_codec_str = (char*)af_wv;	break; 
					case AF_WMA:  tmp_codec_str = (char*)af_wma; break; 
					case AF_APE:  tmp_codec_str = (char*)af_ape; break; 
					case AF_MPC:  tmp_codec_str = (char*)af_mpc; break; 
					case AF_DSD:	tmp_codec_str = (char*)af_dsd; break;  
					case AF_DTS:	tmp_codec_str = (char*)af_dts; break;  
					default : tmp_codec_str = (char*)af_null; break;
					}
				G_print_string_len_f8x16(tmp_codec_str,310,POS_Y_STR_FILE,17,curr_theme.color_txt_par_value,COLOR_BLACK);
				pre_codec = File_Codec;	
				}
				
			//Флаги

			#define clr_on curr_theme.color_txt_par_value
			#define clr_off COLOR_GRAY
				
			uint16_t clr_current;	
			
			if 	(pre_flags != Flags_data)
				{
				if (Flags_data &  F_REPEATE)	clr_current = clr_on;
				else clr_current = clr_off;
					
				G_print_string_len_f8x16("ПС.",380,POS_Y_STR_DAC,3,clr_current,COLOR_BLACK);	
				
				if (Flags_data &  F_RANDOM)		clr_current = clr_on;
				else clr_current = clr_off;
				
				G_print_string_len_f8x16("СП.",410,POS_Y_STR_DAC,3,clr_current,COLOR_BLACK);
				
				if (Flags_data &  F_EQ)	clr_current = clr_on;
				else clr_current = clr_off;	
				
				G_print_string_len_f8x16("ЭКВ.",440,POS_Y_STR_DAC,4,clr_current,COLOR_BLACK);		
					
				pre_flags = Flags_data;	
				}
	
	}
	

//Напечатать курсор
#define  x_start 0
#define  h_cursor 22 	//Высота курсора
#define  len 479-9 		//Длина курсора (координата конца)

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
	
//Напечатать курсор 2
#define  x_start_2 273
#define  h_cursor_2 22 	//Высота курсора
#define  len_2 92 		//Длина курсора (координата конца)	
void GUI_print_cursor_2(void)
	{
	unsigned char y; 	
	y=POS_Y_STR_DAC-5;

	G_print_h_line(x_start_2+1,y,len_2+1,COLOR_GRAY);
	G_print_h_line(x_start_2+2,y+1,len_2,COLOR_WHITE);
		
	G_print_h_line(x_start_2+1,y + h_cursor_2,len_2+1,COLOR_WHITE);
	G_print_h_line(x_start_2+1,y + h_cursor_2+1,len_2+1,COLOR_GRAY);

	//Лево
	G_print_v_line(x_start_2,y+1,h_cursor_2-1,COLOR_GRAY);
	G_print_v_line(x_start_2+1,y+1,h_cursor_2-2,COLOR_WHITE);
	//Право
	G_print_v_line(x_start_2+len_2+2,y+1,h_cursor_2-2,COLOR_WHITE);
	G_print_v_line(x_start_2+len_2+1+2,y+1,h_cursor_2-1,COLOR_GRAY);
	}	
//Напечатать курсор
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
	
//Стереть курсор 2
void GUI_clear_cursor_2(void)
	{
	unsigned char y; 	
	y=POS_Y_STR_DAC-5;

	G_print_h_line(x_start_2+1,y,len_2+1,COLOR_BLACK);
	G_print_h_line(x_start_2+2,y+1,len_2,COLOR_BLACK);
		
	G_print_h_line(x_start_2+1,y + h_cursor_2,len_2+1,COLOR_BLACK);
	G_print_h_line(x_start_2+1,y + h_cursor_2+1,len_2+1,COLOR_BLACK);

	//Лево
	G_print_v_line(x_start_2,y+1,h_cursor_2-1,COLOR_BLACK);
	G_print_v_line(x_start_2+1,y+1,h_cursor_2-2,COLOR_BLACK);
	//Право
	G_print_v_line(x_start_2+len_2+2,y+1,h_cursor_2-2,COLOR_BLACK);
	G_print_v_line(x_start_2+len_2+1+2,y+1,h_cursor_2-1,COLOR_BLACK);
	}
	
//Стереть строку
void GUI_clear_string(uint32_t index)
	{
	unsigned char y; 	
	y=index * (h_cursor+2);
	G_fill_rectangle(x_start, y, x_start+len+1+2, y+h_cursor+1, COLOR_BLACK);	
	}
	
#define POS_X_SB 	476	//координата по X
#define POS_Y_SB 	2	  //координата по Y
#define W_SB 			2				//ширина
#define H_SB 			237			//высота
#define CL_TS			0x5AEB					//цвет темных столбиков
//#define CL_SS	COLOR_WHITE			//цвет светлого столбика
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
		G_fill_rectangle(POS_X_SB,POS_Y_SB + y_pos_actst,POS_X_SB+W_SB,y_pos_actst + hactst, curr_theme.color_progress_bar);
		}
	}
	
#define xl 4	//Отступ слева
#define xr 476 //отступ справа
#define ypos 315
	
//прогресбар времени
void GUI_print_time_PB(uint32_t arg_percent)
	{	
	static uint32_t pre_percent = 200;
		
	if(arg_percent < pre_percent)		
	G_fill_rectangle(xl, ypos, xr, ypos+2,CL_TS);
	
	G_fill_rectangle(xl, ypos, xl + arg_percent * (xr-xl)/100, ypos+2,curr_theme.color_progress_bar);
	pre_percent = arg_percent;
	}	
	
//Узнать количество символов в строке	
uint32_t GUI_get_string_len(void)
	{
	return 45;
	}

void GUI_print_poff_screen(void)
	{
	G_clear_screen(COLOR_BLACK);
	G_print_string_len_f8x16("ЗАВЕРШЕНИЕ РАБОТЫ.",150,152,18,COLOR_WHITE,COLOR_BLACK);
	}
