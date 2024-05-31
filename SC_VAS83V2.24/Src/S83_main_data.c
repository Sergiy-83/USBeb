//Основные данные и функции для программы


#include "S83_main_data.h"
#include "S83_spi_software.h"

uint8_t RX_Buffer[TYPE_NUM_LAST][65]; //Массив приема
uint8_t TX_Buffer[65];								//Массив отправки


volatile int  t2_mode = T2_MODE_USBDATA; 
void T2_add_mode(uint32_t arg_mode, int arg_time) 	
	{
	if (arg_mode == T2_MODE_DISPMSG) count_toast_reset(arg_time);	
	if (arg_mode == T2_MODE_W_RESET) count_w_reset(arg_time);
	if (arg_mode == T2_MODE_ENCVOLM) count_enc2mode_reset(arg_time);
	t2_mode |= 	arg_mode;
	}	
	
volatile uint8_t  flag_len_toast 			= 100;	
volatile bool flag_ready_gui_frame 		= false;
volatile bool flag_ready_spi_data 		= false;
volatile bool flag_ready_lcd_brig 		= false;
volatile bool flag_ready_get_version 	= false;
volatile bool flag_ready_gui_colors 	= false;
volatile bool flag_ready_msg_toast 		= false;
volatile bool flag_ready_usbhid_data 	= false;	//Пришли данные по USB



volatile int  flag_count_sec_toast 	= 5;
void count_toast_reset(int arg_sec)
	{	
	if (arg_sec > 10 )	arg_sec = 2;
	flag_count_sec_toast = arg_sec;
	}

volatile int  flag_count_sec_w = 5; 
void count_w_reset(int arg_sec)
	{
	if (arg_sec > 50 )	arg_sec = 5;
	if (arg_sec < 0 )	  arg_sec = 5;
	flag_count_sec_w = arg_sec; 			
	}

volatile int flag_count_enc2mode = ENC_MODE2_SEC;
void count_enc2mode_reset(int arg_sec)
	{
	if (arg_sec > 50 )	arg_sec = 5;
	if (arg_sec < 0 )	  arg_sec = 5;
	flag_count_enc2mode = arg_sec; 
	}
	
//nodata
volatile int flag_count_sec_nodata = 4;		 //Значение счетчика для "неприходят данные"
void count_nodata_reset(void)
	{
	flag_count_sec_nodata = 4;	
	}	

int count_down(volatile int* arg_counter)
	{
	if (*arg_counter) (*arg_counter)--; 			
	return *arg_counter;
	}		
	
volatile int  flag_screen_mode 			= PRINT_SCREEN_MODE_GUI;
volatile int  flag_screen_mode_pre 	= PRINT_SCREEN_MODE_GUI;

void set_print_screen_mode(int arg_new_mode)
			{
			flag_screen_mode_pre = flag_screen_mode;
			flag_screen_mode = arg_new_mode;
			}
			

			

			
volatile bool flag_mode_vol_encoder = VOLUME_ENC_MODE_VOLUME;  //Изначально в режиме регулировки громкости. Если скомпилировано в обычном режиме то переменная не используется

