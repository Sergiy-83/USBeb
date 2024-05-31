#include <stdbool.h>

#include "main.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"
#include "S83_lcd.h"
#include "S83_graphics.h"
#include "S83_gui.h"
#include "S83_spi_software.h"
#include "S83_main_data.h"
#include "S83_themes.h"

	struct sspi_desc sspi_1 =
		{
		.port 		= GPIOB,
		.pin_clk 	= GPIO_PIN_7,
		.pin_cs 	= GPIO_PIN_10,
		.pin_miso = 0,
		.pin_mosi = GPIO_PIN_8 	
		};
	struct sspi_desc sspi_2 = 
		{
		.port			= GPIOB,
		.pin_clk 	= GPIO_PIN_7,
		.pin_cs 	= GPIO_PIN_9,
		.pin_miso = 0,
		.pin_mosi = GPIO_PIN_8 	
		};
		
void SystemClock_Config(void);

void main_pring_gui(void)
	{
	TEST_LED_SET;
	GUI_print_interface();	
	TEST_LED_RESET;
	}

int main(void)
	{
	

	
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  MX_TIM1_Init();
	MX_TIM2_Init();
  MX_TIM3_Init();

		
		
	lcd_backlight_off(); //�������� LCD ���� 595-� �� ����� �� Z ���������

	//�������� ���� � ��������� � ��������� ���������
	uint8_t buff_zero[] = {0,0,0,0,0,0,0,0,0,0};
	sspi_transfer(&sspi_1, buff_zero, 10);
	sspi_transfer(&sspi_2, buff_zero, 10);

	set_lcd_brightness(100); //������� �������
	LCD_Init();
	lcd_backlight_on();
	GUI_init();

	GUI_loading();
	
	GUI_print_static_text();
	
	Enable_TIMER(&htim2);
  
	/* Infinite loop */
  while (1)
  {
	//���������� ������	
	if (flag_ready_gui_frame) 
		{
		flag_ready_gui_frame = false;

		//////////////////// �������� � ������� ////////////////////////////////////
		if (Flags_data & F_POWEROFF)	
			set_print_screen_mode(PRINT_SCREEN_MODE_POFF);
		else
			{	
			if (flag_screen_mode == PRINT_SCREEN_MODE_POFF )  
				{
				set_print_screen_mode(PRINT_SCREEN_MODE_GUI);
				}					
							
			}
		////////////// ������������ ����� //////////////////////////////////////////////	
		if (flag_screen_mode == PRINT_SCREEN_MODE_POFF) 
				{
				GUI_print_poff_screen();	
				T2_add_mode(T2_MODE_W_RESET,u8_W_SEC); //������ ������� ������ W (Work)
				}
		/////////////////////////////////////////////////////////////////////////////////		
		if (flag_screen_mode == PRINT_SCREEN_MODE_GUI)
			{
			if (flag_screen_mode_pre == PRINT_SCREEN_MODE_POFF)
				{
				set_print_screen_mode(PRINT_SCREEN_MODE_GUI);	
				G_clear_screen(COLOR_BLACK); //�� ������ ���
				GUI_print_static_text();	
				PIN_WORK_SET;
				#ifdef CONFIG_VOL_ENCODER_MODE_2	
							flag_mode_vol_encoder = VOLUME_ENC_MODE_VOLUME; //������� � ����� 
				#endif
				}
		
			if (flag_screen_mode_pre == PRINT_SCREEN_MODE_TOAST)
				{
				GUI_clear_toast();
				set_print_screen_mode(PRINT_SCREEN_MODE_GUI); //��� �� �������� flag_screen_mode_pre
				}
				
			main_pring_gui(); //���������� ����� � ����������
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////			
		//if (flag_screen_mode == PRINT_SCREEN_MODE_TOAST)
			//	{
			//	
			//	}
						

		}
		
	//������ ��� SPI
	if (flag_ready_spi_data)
		{
		//flag_ready_spi_data = false;
		
		//if (SSPI_PORT_1 == SPI_PORT) 			
		//		sspi_transfer(&sspi_1, pSPI_DATA, SPI_LEN);
		//if (SSPI_PORT_2 == SPI_PORT) 			
		//		sspi_transfer(&sspi_2, pSPI_DATA, SPI_LEN);
		//if (SSPI_PORT_3 == SPI_PORT) 			
			//	;//sspi_transfer(&sspi_3, pSPI_DATA, SPI_LEN);
		}	

	//������� �������	
	if(flag_ready_lcd_brig)
		{
		//flag_ready_lcd_brig = false;	
		//set_lcd_brightness(LCD_BRIG);
		}
		
	//������ ������	
	if (flag_ready_get_version)
		{
		flag_ready_get_version = false;
			
		TX_Buffer[0] = TYPE_VERSION_BOARD;	
		VERSION_BOARD = 24; //2.4	* 10
		STRING_LEN = GUI_get_string_len();	
			__DATE__;
		//VERSION_DAY = 1;		
		//VERSION_MONTH = 10;		
		//VERSION_YEAR = 22; //���� ��������� ���������
		strcpy(pDATA_BUILD_STR,__DATE__);
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,TX_Buffer,65);		//���������� �� USB
		PIN_WORK_SET;	
		}	
	
	//������ ������	
	if (flag_ready_gui_colors)
		{
		flag_ready_gui_colors = false;
		curr_theme.color_txt_par 						= *pCOLOR_par_name;					//���� ����� ���������
		curr_theme.color_txt_par_value 			= *pCOLOR_par_value;				//���� �������� ���������
		curr_theme.color_txt_par_value_wrng = *pCOLOR_par_value_wrng;		//���� ���������� �������� ���������	
		curr_theme.color_progress_bar 			= *pCOLOR_par_progress_bar;	//���� ������������	
		GUI_print_static_text();	
		PIN_WORK_SET;			
		}
		
	//��������� ������ ���������	
	if (flag_ready_msg_toast)
		{
		flag_ready_msg_toast 	= false; 
		count_toast_reset(u_TMSG_SEC);
			
  	if ( (flag_screen_mode == PRINT_SCREEN_MODE_GUI) || (flag_screen_mode == PRINT_SCREEN_MODE_TOAST) ) 		//C������� ���������� ������ � ������� ������
			{
			if (flag_screen_mode == PRINT_SCREEN_MODE_TOAST) 
					{
					GUI_clear_toast();  //���� ��� � ������ ��������� �� ������ ����������
					if (flag_len_toast > u_TMSG_LEN) main_pring_gui();		//���������� ����� � ���������� ��� ��� ��������� �������� ����� ���� ��� ��� ����������
					}
			set_print_screen_mode(PRINT_SCREEN_MODE_TOAST); 
			GUI_print_toast(p_TMSG_STR,u_TMSG_LEN,u16_TMSG_COLOR);		//�������� ���������
			T2_add_mode(T2_MODE_DISPMSG,u_TMSG_SEC); 									//��������� ������ ������������� ���������	
			}
		}

  }

}

//������������ ������������
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef 				RCC_OscInitStruct;
  RCC_ClkInitTypeDef 				RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef 	PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType 	= RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState 				= RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue 	= RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState 				= RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState 		= RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource 	= RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL 			= RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType 			= RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource 		= RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider 	= RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider 	= RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider 	= RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
//������������ ����� �������� ���� ����������� ����������, ����� �������� � ��������� �������� ������ HAL  
 
while(1)
		{
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);	
		delay(60);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);	
		delay(60);
		}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


