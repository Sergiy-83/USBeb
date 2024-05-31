#ifndef __S83_KEYBOARD_H
#define __S83_KEYBOARD_H
#include "stdint.h"

//коды клавиш		
#define BUTTON_VOL_UP 	 (uint32_t)(1 << 0  ^ -1)
#define BUTTON_VOL_DOWN  (uint32_t)(1 << 1  ^ -1)
#define BUTTON_UP        (uint32_t)(1 << 2  ^ -1)
#define BUTTON_DN        (uint32_t)(1 << 3  ^ -1)
#define BUTTON_PLAY      (uint32_t)(1 << 4  ^ -1)
#define BUTTON_STOP      (uint32_t)(1 << 5  ^ -1)
#define BUTTON_NEXT			 (uint32_t)(1 << 6  ^ -1)	
#define BUTTON_PRE 			 (uint32_t)(1 << 7  ^ -1)	
#define BUTTON_FN1       (uint32_t)(1 << 8  ^ -1)
#define BUTTON_FN2       (uint32_t)(1 << 9  ^ -1)
#define BUTTON_PS        (uint32_t)(1 << 10 ^ -1)
#define BUTTON_NEXT_LONG (uint32_t)(1 << 11 ^ -1)
#define BUTTON_PREV_LONG (uint32_t)(1 << 12 ^ -1)
#define BUTTON_PLAY_LONG (uint32_t)(1 << 13 ^ -1)
#define BUTTON_STOP_LONG (uint32_t)(1 << 14 ^ -1)
#define BUTTON_UP_LONG   (uint32_t)(1 << 15 ^ -1) //Пока неиспользуется 
#define BUTTON_DN_LONG   (uint32_t)(1 << 16 ^ -1) //Пока неиспользуется

#define BUTTON_SW_NEXT   (uint32_t)(1 << 31 ^ -1) //Virtual
	
//READ_PINS
#define READ_PIN_CURSOR_UP  (uint32_t)(GPIOA->IDR & GPIO_PIN_9)


//формат данных клавиатуры
enum format_keys
    {//32 бита код кнопки
		IDX_TYPE=0,	
    IDX_BUTTONS_32_BIT = 1
    };
		
extern uint8_t TX_Buffer[65];	
		
#define TYPE							TX_Buffer[IDX_TYPE]
#define pBUTTONS_32_BIT		(uint32_t*)&TX_Buffer[IDX_BUTTONS_32_BIT]

void 			S83_volume_UP			(void);
void 			S83_volume_DOWN		(void);
void 			S83_cursor_UP			(void);
void 			S83_cursor_DOWN		(void);
uint32_t 	S83_buttons_read	(void);
void 			S83_buttons_send	(uint32_t buttons_out);

#endif
