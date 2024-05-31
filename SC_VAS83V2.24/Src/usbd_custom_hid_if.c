#include <stdbool.h>

#include "usbd_custom_hid_if.h"
#include "S83_main_data.h"
#include "S83_main_data.h"
#include "S83_spi_software.h"

extern	struct sspi_desc sspi_1;
		
/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
  	0x06,0x00,0xff,			//Usage Page (Generic Desktop)
		0x09,0x01,					//Usage (Vendor Usage 1)
		
		0xA1,0x01,					
		0x85,0x02,
		0x75,0x08,
		0x95,64,
		0x09,0x01,
		0x91,0x82,
	
		0x85,0x01,
		0x09,0x04,
		0x75,0x08,
		0x95,64,
		0x81,0x82,
  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};



/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);


USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
	{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
	};



/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
	{
	return (USBD_OK);
	}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
		USBD_CUSTOM_HID_HandleTypeDef *hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData;
		
		if(hhid->Report_buf[0] < TYPE_NUM_LAST) //Если не выходим за пределы массива 0-байт тип сообщения
			{
			flag_ready_usbhid_data = true; //Какие то данные пришли	
			//Читаем данные в буффер (двумерный массив)/////////////////////////////////////////////////////////////
			for (int i=0;i<65;i++) //Побайтно
				{
				RX_Buffer[ hhid->Report_buf[0] ][i] = hhid->Report_buf[i]; 
				}

			//////////////////////////////////////////////////////////////////////////////////////
			//Смотрим что за данные	
			
			if (hhid->Report_buf[0] == TYPE_LCD_OTHER_DATA) 
				{
				flag_ready_gui_frame = true; //Строки и другие данные кадра пришли  - можно рисовать
				}

			if (hhid->Report_buf[0] == TYPE_SPI_DATA) 
				{	
				//Данные для вывода по SPI.
				if (SSPI_PORT_1 == SPI_PORT) 			
					sspi_transfer(&sspi_1, pSPI_DATA, SPI_LEN);
				if (SSPI_PORT_2 == SPI_PORT) 			
					sspi_transfer(&sspi_2, pSPI_DATA, SPI_LEN);
				}	
				
			if (hhid->Report_buf[0] == TYPE_LCD_BRIG) 
				{	
				flag_ready_lcd_brig = true; //Яркость для LCD пришла.		
				set_lcd_brightness(LCD_BRIG);
				}	
				
			if (hhid->Report_buf[0] == TYPE_CMD_GET_VERSION) 
				{	
				flag_ready_get_version = true; 
				}	
				
			if (hhid->Report_buf[0] == TYPE_LCD_COLORS) 
				{	
				flag_ready_gui_colors = true; //Пришли цвета некоторые.
				}	
			
			if (hhid->Report_buf[0] == TYPE_LCD_MSG) 
				{
				flag_ready_msg_toast 	= true; //Пришло текстовое сообщение.
				}	
				
				
			}
	 		
	
		
  return (USBD_OK);
  /* USER CODE END 6 */
}



