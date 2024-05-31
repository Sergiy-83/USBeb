#ifndef S83_ENCODER_H_
#define S83_ENCODER_H_
#include "usb_device.h"


#define ENC_NO		0
#define ENC_LEFT	1
#define ENC_RIGHT	2

//Дескриптор энкодера
typedef struct
	{
	GPIO_TypeDef 	*enc_port;							//Порт к которому подключен энкодер
	uint16_t 			enc_pin_phase_A;				//Первый пин
	uint16_t 			enc_pin_phase_B;				//Второй пин
	uint32_t 			Pre_state;             	//предыдущее состояние энкодера
	uint32_t 			Current_state;         //текущее состояние энкодера
	}enc_descr;

int get_encoder(enc_descr *arg_encoder); //функция возвращает направление щелчка ENC_LEFT или ENC_RIGHT, если его небыло то возвращает ENC_NO. Вызывать переодически. Например 2ms


#endif
