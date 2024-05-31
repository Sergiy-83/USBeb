#include "S83_encoder.h"


		
int get_encoder(enc_descr *arg_encoder)
		{	
		uint32_t tmp_state;
		
		tmp_state = 0xFFFFFFFF;
		if (0==(uint32_t)(arg_encoder->enc_port->IDR & arg_encoder->enc_pin_phase_A)) //читаем фазу А
			tmp_state &= 0xFFFFFFFE;
		if (0==(uint32_t)(arg_encoder->enc_port->IDR & arg_encoder->enc_pin_phase_B)) //Читаем фазу B
			tmp_state &= 0xFFFFFFFD;


		 //Читаем состояние всех входов энкодера
					
		//Работаем с энкодером        
		arg_encoder->Pre_state = arg_encoder->Current_state;   	//запомним предыдущее состояние энкодера
		arg_encoder->Current_state= tmp_state;       						//запоминаем новое состояние энкодера
    if(arg_encoder->Pre_state == 0xFFFFFFFF) 								//Если предыдущее состояние 11, то обрабатываем текущее сосотояние 
    if (arg_encoder->Current_state != 0xFFFFFFFF)						//Если текущее тоже 11 то щелчка небыло, ничего не делаем
			{ 
			if (arg_encoder->Current_state == 0xFFFFFFFE) return ENC_LEFT;
			if (arg_encoder->Current_state == 0xFFFFFFFD) return ENC_RIGHT;
			} 
		return  ENC_NO;           
	}

	