#include "S83_keyboard.h"
#include "S83_main_data.h"
#include "usbd_customhid.h"
#include "usb_device.h"
#include "S83_configuration.h"

uint32_t buttons_out;
uint32_t btn_no_press_code = 0xFFFFFFFF;


void S83_volume_UP(void)
	{		
	buttons_out = btn_no_press_code;	
	buttons_out &= BUTTON_VOL_UP;
	S83_buttons_send(buttons_out);
	}

void S83_volume_DOWN(void)
	{
	buttons_out = btn_no_press_code;	
	buttons_out &= BUTTON_VOL_DOWN;
	S83_buttons_send(buttons_out);
	}

void S83_cursor_UP(void)
	{
	buttons_out = btn_no_press_code;	
	buttons_out &= BUTTON_UP;
	S83_buttons_send(buttons_out);
	}

void S83_cursor_DOWN(void)
	{
	buttons_out = btn_no_press_code;	
	buttons_out &= BUTTON_DN;
	S83_buttons_send(buttons_out);
	}
	
	
uint32_t S83_buttons_read (void)
	{
	uint32_t buttons_out;
	buttons_out = btn_no_press_code;	

	#ifdef  CONFIG_UPDOWN_BUTTONS
	if (0==(uint32_t)(GPIOA->IDR & GPIO_PIN_9))  	buttons_out &= BUTTON_UP;
	if (0==(uint32_t)(GPIOA->IDR & GPIO_PIN_10))  buttons_out &= BUTTON_DN;
	#endif
		
	if (0==(uint32_t)(GPIOB->IDR & GPIO_PIN_6))  	buttons_out &= BUTTON_PLAY;
	if (0==(uint32_t)(GPIOB->IDR & GPIO_PIN_5))  	buttons_out &= BUTTON_STOP;
	if (0==(uint32_t)(GPIOA->IDR & GPIO_PIN_8))  	buttons_out &= BUTTON_NEXT;
	if (0==(uint32_t)(GPIOB->IDR & GPIO_PIN_12))  buttons_out &= BUTTON_PRE;		
	if (0==(uint32_t)(GPIOB->IDR & GPIO_PIN_4))  	buttons_out &= BUTTON_FN2;
	if (0==(uint32_t)(GPIOB->IDR & GPIO_PIN_3))  	buttons_out &= BUTTON_FN1;
	if (0==(uint32_t)(GPIOA->IDR & GPIO_PIN_15))  buttons_out &= BUTTON_PS;
		
	return buttons_out;		
	}
	
void S83_buttons_send (uint32_t buttons_out)
	{
	if(btn_no_press_code == buttons_out) return; 
		
	TYPE = TYPE_KEYBOARD_DATA;			//Тип сообщения - данные от клавиатуры
	*pBUTTONS_32_BIT = buttons_out;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,TX_Buffer,65);		//Отправляем по USB
	}
