#include "S83_encoder.h"


		
int get_encoder(enc_descr *arg_encoder)
		{	
		uint32_t tmp_state;
		
		tmp_state = 0xFFFFFFFF;
		if (0==(uint32_t)(arg_encoder->enc_port->IDR & arg_encoder->enc_pin_phase_A)) //������ ���� �
			tmp_state &= 0xFFFFFFFE;
		if (0==(uint32_t)(arg_encoder->enc_port->IDR & arg_encoder->enc_pin_phase_B)) //������ ���� B
			tmp_state &= 0xFFFFFFFD;


		 //������ ��������� ���� ������ ��������
					
		//�������� � ���������        
		arg_encoder->Pre_state = arg_encoder->Current_state;   	//�������� ���������� ��������� ��������
		arg_encoder->Current_state= tmp_state;       						//���������� ����� ��������� ��������
    if(arg_encoder->Pre_state == 0xFFFFFFFF) 								//���� ���������� ��������� 11, �� ������������ ������� ���������� 
    if (arg_encoder->Current_state != 0xFFFFFFFF)						//���� ������� ���� 11 �� ������ ������, ������ �� ������
			{ 
			if (arg_encoder->Current_state == 0xFFFFFFFE) return ENC_LEFT;
			if (arg_encoder->Current_state == 0xFFFFFFFD) return ENC_RIGHT;
			} 
		return  ENC_NO;           
	}

	