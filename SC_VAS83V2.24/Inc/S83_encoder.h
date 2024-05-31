#ifndef S83_ENCODER_H_
#define S83_ENCODER_H_
#include "usb_device.h"


#define ENC_NO		0
#define ENC_LEFT	1
#define ENC_RIGHT	2

//���������� ��������
typedef struct
	{
	GPIO_TypeDef 	*enc_port;							//���� � �������� ��������� �������
	uint16_t 			enc_pin_phase_A;				//������ ���
	uint16_t 			enc_pin_phase_B;				//������ ���
	uint32_t 			Pre_state;             	//���������� ��������� ��������
	uint32_t 			Current_state;         //������� ��������� ��������
	}enc_descr;

int get_encoder(enc_descr *arg_encoder); //������� ���������� ����������� ������ ENC_LEFT ��� ENC_RIGHT, ���� ��� ������ �� ���������� ENC_NO. �������� ������������. �������� 2ms


#endif
