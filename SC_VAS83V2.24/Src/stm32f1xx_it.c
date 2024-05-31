#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"

#include "S83_keyboard.h"
#include "S83_configuration.h"
#include "S83_encoder.h"
#include "S83_main_data.h"

#ifdef CONFIG_UPDOWN_ENCODER
enc_descr encoder_updown = 
{
.enc_port = GPIOA,										//Порт A
.enc_pin_phase_A = GPIO_PIN_9,				//Первый пин энкодера
.enc_pin_phase_B = GPIO_PIN_10				//Второй пин энкодера
};
#endif

enc_descr encoder_volume =
{
.enc_port = GPIOB,									//Порт B
.enc_pin_phase_A = GPIO_PIN_0,			//Первый пин энкодера
.enc_pin_phase_B = GPIO_PIN_1				//Второй пин энкодера
};

//отключаем прерывания на кнопках
void Disable_EXT_IRQ_buttons(void)
	{
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);	
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);	
	HAL_NVIC_DisableIRQ(EXTI3_IRQn);
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	
	}
	
//Включаем прерывания на кнопках 
void Enable_EXT_IRQ_buttons(void)
	{
  // очищаем бит EXTI_PR (бит прерывания)
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);		
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);		
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
		
		
	//очищаем бит NVIC_ICPRx (бит очереди)
	NVIC_ClearPendingIRQ(EXTI9_5_IRQn); 
	NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	NVIC_ClearPendingIRQ(EXTI3_IRQn);
	NVIC_ClearPendingIRQ(EXTI4_IRQn);

		
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);	
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);	
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);	
	}	
	
//Включить таймер 
void Enable_TIMER(TIM_HandleTypeDef *arg_timer)
	{
	HAL_TIM_Base_Start(arg_timer);
	HAL_TIM_Base_Start_IT(arg_timer);
	}
//Выключить таймер 
void Disable_TIMER(TIM_HandleTypeDef *arg_timer)
	{
	HAL_TIM_Base_Stop(arg_timer);
	arg_timer->Instance->CNT = 0;
	HAL_TIM_Base_Stop_IT(arg_timer);
	}

//Для третьего таймера
#define PROPUSK_NUM 1 
#define PROPUSK_NUM_SEEK 3  //Количество несрабатываний обработчика прерываний для позицианирования. (задержка)

int flag_propusk_tim3 		 = 0;	
int flag_propusk_tim3_seek = 0;	
int flag_propusk_tim3_stop = 0;
int flag_propusk_tim3_play = 0;	

	
int flag_btn_next_pressed = 0;	
int flag_btn_prev_pressed = 0;	
int flag_btn_play_pressed = 0;	
int flag_btn_stop_pressed = 0;		

	

	
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_FS;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;


/******************************************************************************/
/*            Cortex-M3 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Prefetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{

}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{

}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles EXTI line0 interrupt.
*/
void EXTI0_IRQHandler(void)
{
	//Обработчик прерывания энкодера
	Enable_TIMER(&htim1); 			//Запускаем таймер опроса энкодера
	
  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
* @brief This function handles EXTI line3 interrupt.
*/
void EXTI3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI3_IRQn 0 */
	// Прерывание кнопки FN2
	Disable_EXT_IRQ_buttons();						//отключаем прерывания на кнопках
	S83_buttons_send(S83_buttons_read());	//Читаем и отправляем состояние кнопок коммандеру
	Enable_TIMER(&htim3);									//вКлючаем таймер клавиатуры для проверки удержания кнопки
	
  /* USER CODE END EXTI3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  /* USER CODE BEGIN EXTI3_IRQn 1 */

  /* USER CODE END EXTI3_IRQn 1 */
}

/**
* @brief This function handles EXTI line4 interrupt.
*/
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */
	// Прерывание кнопки FN1
	Disable_EXT_IRQ_buttons();						//отключаем прерывания на кнопках
	
	

	#ifdef CONFIG_SWITCH_CURSOR_FN1	
			if (flag_mode_vol_encoder == VOLUME_ENC_MODE_VOLUME)
				flag_mode_vol_encoder = VOLUME_ENC_MODE_CURSOR; //Переключаемя в режим курсора
			else
				flag_mode_vol_encoder = VOLUME_ENC_MODE_VOLUME; //Переключаемя в режим рег громкости
			
			flag_ready_gui_frame = true; //Перерисовать кадр немедленно
	#endif
	
	
	S83_buttons_send(S83_buttons_read());	//Читаем и отправляем состояние кнопок коммандеру
	Enable_TIMER(&htim3);					//вКлючаем таймер клавиатуры для проверки удержания кнопки
	
  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
* @brief This function handles USB low priority or CAN RX0 interrupts.
*/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN USB_LP_CAN1_RX0_IRQn 0 */

  /* USER CODE END USB_LP_CAN1_RX0_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
  /* USER CODE BEGIN USB_LP_CAN1_RX0_IRQn 1 */

  /* USER CODE END USB_LP_CAN1_RX0_IRQn 1 */
}




//This function handles EXTI line[9:5] interrupts.
//Прерывание кнопок PLAY STOP NEXT UP
void EXTI9_5_IRQHandler(void)
	{
	#ifdef CONFIG_UPDOWN_ENCODER //если на кнопках UP DOWN энкодер подключен
		if (0 == READ_PIN_CURSOR_UP ) //Если прерывание от входа кнопки CURSOR UP  
			{
			Enable_TIMER(&htim1); 			//Запускаем таймер опроса второго энкодера который в этом режиме на кнопках Up Down
			}
	#endif
		
#ifdef CONFIG_VOL_ENCODER_MODE_2		
		#ifndef CONFIG_SWITCH_CURSOR_FN1			
				if (0==(uint32_t)(GPIOB->IDR & GPIO_PIN_6)) //Если прерывание от входа кнопки PLAY, в режиме CONFIG_VOL_ENCODER_MODE_2 мы вместо обычной кнопки исплользуем кнопку энкодера громкости 
				{
				count_enc2mode_reset(ENC_MODE2_SEC);//Сбросить счетчик таймера 2 в исходное
					
				if (flag_mode_vol_encoder == VOLUME_ENC_MODE_VOLUME)
					{
					flag_mode_vol_encoder = VOLUME_ENC_MODE_CURSOR; //Переключаемя в режим курсора
					Disable_EXT_IRQ_buttons();											//отключаем прерывания на кнопках
					Enable_TIMER(&htim3);												//вКлючаем таймер клавиатуры для проверки удержания кнопки
					flag_propusk_tim3 = PROPUSK_NUM;						//Задержку ему изначально	
					flag_ready_gui_frame = true; 								//Перерисовать кадр немедленно	
					T2_add_mode(T2_MODE_ENCVOLM,ENC_MODE2_SEC); //вКлючаем таймер 2 который через ~10сек переведет в режим VOLUME_ENC_MODE_VOLUME
					goto fin_EXTI9_5;
					}
				if (flag_mode_vol_encoder == VOLUME_ENC_MODE_CURSOR)
					{
					Enable_TIMER(&htim3);
					}
				}
		#endif		
#endif
		//нажата какая то кнопка
		Disable_EXT_IRQ_buttons();							//отключаем прерывания на кнопках
		uint32_t btn_state = S83_buttons_read();//Читаем состояние кнопок коммандеру
		
                                                                   
		switch(btn_state)
			{
			case BUTTON_NEXT:	flag_btn_next_pressed  = 1; //если следующий или предыдущий  	
												flag_propusk_tim3 		 = 1;		
												flag_propusk_tim3_seek = PROPUSK_NUM_SEEK;
												break;
			case BUTTON_PRE:	flag_btn_prev_pressed  = 1;
												flag_propusk_tim3 		 = 1;		
												flag_propusk_tim3_seek = PROPUSK_NUM_SEEK;
												break;
			case BUTTON_PLAY:	flag_btn_play_pressed  = 1;
												flag_propusk_tim3 		 = 0;		
												flag_propusk_tim3_play = 4;
												break;
			case BUTTON_STOP:	flag_btn_stop_pressed  = 1;
												flag_propusk_tim3 		 = 0;		
												flag_propusk_tim3_stop = 4;
												break;
			default: 					S83_buttons_send(btn_state);	//Отправляем состояние кнопок коммандеру
			}
		
		Enable_TIMER(&htim3);						//вКлючаем таймер клавиатуры для проверки удержания кнопки
	
		fin_EXTI9_5:
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
	}


void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */
	//Таймер опроса энкодеров 

	static int counter_dis = 0;
	int enc_state_1;
	enc_state_1 = get_encoder(&encoder_volume);
	
	if (enc_state_1 == ENC_LEFT)	
		{
		if (flag_mode_vol_encoder == VOLUME_ENC_MODE_VOLUME) S83_volume_UP();
		if (flag_mode_vol_encoder == VOLUME_ENC_MODE_CURSOR) 
			{
				count_enc2mode_reset(ENC_MODE2_SEC); //Сбросить счетчик таймера 2 в исходное- не переходить в режим VOLUME_ENC_MODE_VOLUME
				S83_cursor_UP();
			}
		counter_dis = 0;		
		}
		
	if (enc_state_1 == ENC_RIGHT) 
		{
		if (flag_mode_vol_encoder == VOLUME_ENC_MODE_VOLUME) S83_volume_DOWN();
		if (flag_mode_vol_encoder == VOLUME_ENC_MODE_CURSOR) 
				{
				count_enc2mode_reset(ENC_MODE2_SEC); //Сбросить счетчик таймера 2 в исходное	
				S83_cursor_DOWN();
				}
		counter_dis = 0;		
		}
	
	#ifdef CONFIG_UPDOWN_ENCODER
						int encoder_2_state;
						encoder_2_state = get_encoder(&encoder_updown);
											
						if (encoder_2_state == ENC_LEFT)	
								{
								S83_cursor_UP();
								counter_dis = 0;		
								}
												
						if (encoder_2_state == ENC_RIGHT) 
								{
								S83_cursor_DOWN();
								counter_dis = 0;	
								}
	#endif
							
	counter_dis++;
	if (counter_dis == 3000) 		//Если энкодер опросили 1000 раз напрасно
			{
			Disable_TIMER(&htim1);	//oстанавливаем этот таймер после 1000 опросов без изменения
			counter_dis = 0;				//Обнуляем счетчик напрасных опросов энкодера	
			}
			
	//Enable_EXT_IRQ_buttons(); //Включаем прерывание на кнопках

	/* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
}


//Таймер 2 (обработчик) многофункциональный. 
void TIM2_IRQHandler(void)
{
	//if (t2_mode & T2_MODE_DISABLE) //Пора отключить таймер  
	//Disable_TIMER(&htim2);
				
	#ifdef CONFIG_VOL_ENCODER_MODE_2	
				if (t2_mode & T2_MODE_ENCVOLM)
					{
					//if (tim2_mode_1_counter == 0)
					if (0 == count_down(&flag_count_enc2mode) )		
						{
						count_enc2mode_reset(7);							
						flag_mode_vol_encoder = VOLUME_ENC_MODE_VOLUME; //Переводим энкодер в режим управления громкостью
						//_mode_1_counter = TIM2_MODE_1_CNT_VALUE;
						t2_mode &= ~T2_MODE_ENCVOLM;	//oстанавливаем этот режим
						}
					
					}
	#endif
		
	if (t2_mode & T2_MODE_W_RESET)
		{
			if (0 == count_down(&flag_count_sec_w))
				{
				count_w_reset(5);							//сброс счетчика W
				PIN_WORK_RESET;								//выключаем сигнал W (Work)
				t2_mode &= ~T2_MODE_W_RESET;	//oстанавливаем этот режим	
				}
		}
		
	if (t2_mode & T2_MODE_DISPMSG)
		{
			if (0 == count_down(&flag_count_sec_toast))
				{
				count_toast_reset(u_TMSG_SEC);								//сброс счетчика toast
				set_print_screen_mode(PRINT_SCREEN_MODE_GUI);	//Переходим в обычный режим отображения
				flag_ready_gui_frame = true; 									//прорисовать немедленно	если сервер не шлет данные этот флаг не всзведется 
				t2_mode &= ~T2_MODE_DISPMSG;									//oстанавливаем этот режим	
				}
		}
		
	if (t2_mode & T2_MODE_USBDATA)
		{
			if (0 == count_down(&flag_count_sec_nodata))
				{
				count_nodata_reset();	
				if (flag_ready_usbhid_data) //Данные приходят
					flag_ready_usbhid_data = false; //Сбрасываем флаг что приходят
				else //Неприходят
					{
					memcpy(p_TMSG_STR,(const void*)"Нет данных от AC83 !!!",22);
					u_TMSG_LEN = 22;
					u16_TMSG_COLOR = 0xFFFF;
					u_TMSG_SEC = 3;
					flag_ready_msg_toast = true; 						
					}					
				}
		
		}
		
  HAL_TIM_IRQHandler(&htim2);
}





int flag_propusk_seek_time = 0;
int seek_ok(void) //Регулировка частоты повторения
	{
	if( flag_propusk_seek_time )	
		{
		flag_propusk_seek_time--;
		return false;
		}
	return true;
	}
	
	
//Обработчик прерывания таймера опроса клавиатуры при удержании
void TIM3_IRQHandler(void)
	{
	uint32_t buttons_out;

	if (flag_propusk_tim3) 
		{
		flag_propusk_tim3--;	
		goto finish_tim3; //Не отправляем
		}
	buttons_out = S83_buttons_read();
	
	if(0xFFFFFFFF == buttons_out) //Если кнопки отпущены - уже отпустили
		{

		if (flag_btn_next_pressed) S83_buttons_send(BUTTON_NEXT);
		if (flag_btn_prev_pressed) S83_buttons_send(BUTTON_PRE);   
		if (flag_btn_play_pressed) S83_buttons_send(BUTTON_PLAY);   
		if (flag_btn_stop_pressed) S83_buttons_send(BUTTON_STOP);   
			
		flag_btn_next_pressed = 0;	
		flag_btn_prev_pressed = 0;	
		flag_btn_play_pressed = 0;
		flag_btn_stop_pressed = 0;
			
		Disable_TIMER(&htim3);						//oстанавливаем этот таймер
		flag_propusk_tim3 = PROPUSK_NUM;	//Задержку ему изначально	
		Enable_EXT_IRQ_buttons();					//Включаем прерывание на кнопках
		}	
	else //Кнопка какае то удерживается в данный момент
		{	

		switch (buttons_out)
			{	
			case BUTTON_STOP: if (flag_propusk_tim3_stop)	//Пропуски - задержка для этой кнопки
														{
														flag_propusk_tim3_stop--;
														goto finish_tim3;
														}	
												if (flag_btn_stop_pressed) 
														{
														S83_buttons_send(BUTTON_STOP_LONG);
														flag_btn_stop_pressed = 0;
														}
												break;
														
			case BUTTON_PLAY: if (flag_propusk_tim3_play)	//Пропуски - задержка для этой кнопки
														{
														flag_propusk_tim3_play--;
														goto finish_tim3;
														}	
														
												if (flag_btn_play_pressed) 
														{
														S83_buttons_send(BUTTON_PLAY_LONG);
														flag_btn_play_pressed = 0;
														}
												break;
						
														
			case BUTTON_PRE:  if (flag_propusk_tim3_seek)	
														{
														flag_propusk_tim3_seek--;
														goto finish_tim3;
														}	
					
												flag_btn_prev_pressed = 0;	
												if (seek_ok()) 
														{
														S83_buttons_send(BUTTON_PREV_LONG);
														flag_propusk_seek_time = 2;
														}
												break;
			case BUTTON_NEXT: if (flag_propusk_tim3_seek)	
														{
														flag_propusk_tim3_seek--;
														goto finish_tim3;
														}
												flag_btn_next_pressed = 0;		
												if (seek_ok()) 
														{
														S83_buttons_send(BUTTON_NEXT_LONG);
														flag_propusk_seek_time = 2;
														}
												break;
														
			default:	S83_buttons_send(buttons_out); 	//Отправляем 
			}
			
		
		count_enc2mode_reset(ENC_MODE2_SEC);	//Сбросить счетчик таймера 2 в исходное- не переходить в режим VOLUME_ENC_MODE_VOLUME	
		}
	
	finish_tim3:

	HAL_TIM_IRQHandler(&htim3);
	}



/**
* @brief This function handles EXTI line[15:10] interrupts.
*/
void EXTI15_10_IRQHandler(void)
	{
	//PRE DOWN POFF
	Disable_EXT_IRQ_buttons();						//отключаем прерывания на кнопках
	
	uint32_t btn_state = S83_buttons_read();//Читаем состояние кнопок коммандеру
	if (btn_state == BUTTON_NEXT || btn_state == BUTTON_PRE) //если следующий или предыдущий  
			{
			flag_propusk_tim3 = 1;
			flag_propusk_tim3_seek = PROPUSK_NUM_SEEK;	
			if (btn_state == BUTTON_NEXT) flag_btn_next_pressed = 1;	
			if (btn_state == BUTTON_PRE)  flag_btn_prev_pressed = 1;		
			}
	else			
			S83_buttons_send(btn_state);	//Отправляем состояние кнопок коммандеру
		
	Enable_TIMER(&htim3);									//вКлючаем таймер клавиатуры для проверки удержания кнопки
  
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
	}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
	{
	//if(GPIO_Pin == GPIO_PIN_15) 	S83_buttons_send(S83_buttons_read());
	}
