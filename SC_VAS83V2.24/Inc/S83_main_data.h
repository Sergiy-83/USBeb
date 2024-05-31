#ifndef _S83_INPUT_DATA_H_
#define _S83_INPUT_DATA_H_

#include <stdbool.h>
#include <stdint.h>
//���� �������� ���������
enum types
		{
		TYPE_STRING_1=0,
		TYPE_STRING_2,
		TYPE_STRING_3,
		TYPE_STRING_4,
		TYPE_STRING_5,
		TYPE_STRING_6,
		TYPE_STRING_7,
		TYPE_STRING_8,
		TYPE_STRING_9,
		TYPE_STRING_10,
		TYPE_LCD_OTHER_DATA,	//����� ����� � ������
		TYPE_LCD_BRIG,				//������� �������
		TYPE_LCD_COLORS,			//����� ��� ��������� ��������� GUI
		TYPE_LCD_MSG,					//��������� ���������
		TYPE_CMD_GET_VERSION, //������ ������
		TYPE_SPI_DATA,				//������ ��� SPI ��������
		TYPE_NUM_LAST					//��������� ����
		};
		
//���� ��������� ���������
enum message_types_in
    {
    TYPE_KEYBOARD_DATA = 0,
    TYPE_VERSION_BOARD
    };	

#define VERSION_BOARD	TX_Buffer[1]	//������ ����� * 10  (21 = 2,1 * 10)
#define STRING_LEN		TX_Buffer[2]	//����� ������ ����� � ��������		
#define pDATA_BUILD_STR	(char*)&TX_Buffer[3]	

//��������� ������	
enum data_other
    {
    PERCENT_POS_CURSOR = 1,	//�������, ��������� ������� � ������
    PERCENT_WINDOW,					//������� ���� � 10 ����� �� ������ ���. ��������� � ������
    PERCENT_TIME,						//������� ����������� �������
    STRING_TIME = 4,        //17 �������� ������������� ������� 00:00:00/00:00:00  
    
    DAC_FREQ = 21,          //������� �������������
    DAC_BIT = 22,           //���������� ���
    
    VOLUME_DB = 23,         //5 ����. ��������� (�����)
    
    FILE_CODEC = 28,        //��� - ������ �����
    FILE_FREQ = 29,         //��� - ������� �����
		FILE_BIT = 30,					//���������� ���
    FILE_BITRATE = 31,      //������� ������ 7 ���� 
    
		FLAGS = 38							//�����
        
    };
		
#define u8_W_SEC 5
		
enum flags_data
    {
    F_POWEROFF = 0x1, //
    F_REPEATE  = 0x2,
    F_RANDOM   = 0x4,
    F_EQ       = 0x8
    };		
		
enum sr_code
{   SR_NULL,
    SR_32000,
    SR_44100,
    SR_48000,
    SR_88200,
    SR_96000,
    SR_176400,
    SR_192000,
	  SR_352800,
		SR_384000,
		SR_705600
};	

enum aformat_code
		{
		AF_NULL,
		AF_FLAC,
		AF_M4A,
		AF_WAV,	
		AF_OGG,
		AF_AAC,
		AF_AC3,
		AF_MP3,
		AF_WV,
		AF_WMA,
		AF_APE,
		AF_MPC,
		AF_DSD,
		AF_DTS	
		};

//������ ��������� ������ 
enum string_format
    {
    IDX_TYPE_MESSAGE = 0,	//��� ��������� - ������� ����
    IDX_STRING = 1,			//������ ���� ������ - ������ ����
		
		IDX_ICON = 61,	
		IDX_BITS = 62,	
		IDX_COLOR = 63
    };		
		
//������ ���������� �������� TOAST
enum USBEB_TMSG
    {
    IDX_TMSG_STR    = 1,   //������ ���� ������ ���������
    IDX_TMSG_STRF   = 51,  //��������� ���� ������ ���������
    //������
    IDX_TMSG_LEN    = 59,  //����� - 1b
    IDX_TMSG_SEC    = 60,  //����� ����������� 1b
    IDX_TMSG_COLOR  = 61,  //���� 3b � ������� ������� 2b
    IDX_TMSG_LAST   = 64   //��������� ���� �������
    };
		
#define u_TMSG_LEN					RX_Buffer[TYPE_LCD_MSG][IDX_TMSG_LEN]
#define p_TMSG_STR  (char*)&RX_Buffer[TYPE_LCD_MSG][IDX_TMSG_STR]
#define u_TMSG_SEC  				RX_Buffer[TYPE_LCD_MSG][IDX_TMSG_SEC]
#define u16_TMSG_COLOR  			*(uint16_t*)&RX_Buffer[TYPE_LCD_MSG][IDX_TMSG_COLOR]

//���� ������
enum icons
		{
		ICON_BACK=0,
		ICON_FOLDER,
		ICON_FILE,
		ICON_PLAYING,
		ICON_PAUSE,	
		ICON_POFF
		}; 
		
		
#define flag_icon_back      0b00000
#define flag_icon_folder    0b00001
#define flag_icon_file      0b00010
#define flag_icon_playing   0b00011
#define flag_icon_pause     0b00100
#define flag_icon_poff     0b00101
		
//�����
enum bits
		{
		BIT_CURSOR = 0x8,
		BIT_ZEROSTRING = 0x10		
		};
		
#define pDATA(x)				(char*)			&(RX_Buffer[x][IDX_STRING])		

#define ICON(x)					RX_Buffer[x][IDX_ICON]	
#define CURSOR(x)				 BIT_CURSOR 		& RX_Buffer[x][IDX_BITS]
#define ZEROSTRING(x)		 BIT_ZEROSTRING & RX_Buffer[x][IDX_BITS]
#define pCOLOR(x)				((uint16_t*)	&(RX_Buffer[x][IDX_COLOR]))	

#define percent_pos_cursor      RX_Buffer[TYPE_LCD_OTHER_DATA][PERCENT_POS_CURSOR]
#define percent_window          RX_Buffer[TYPE_LCD_OTHER_DATA][PERCENT_WINDOW]
#define percent_time            RX_Buffer[TYPE_LCD_OTHER_DATA][PERCENT_TIME]
#define pString_time            &RX_Buffer[TYPE_LCD_OTHER_DATA][STRING_TIME] //������ �������
#define pVolume_db							&RX_Buffer[TYPE_LCD_OTHER_DATA][VOLUME_DB]
#define pFileBitrate						&RX_Buffer[TYPE_LCD_OTHER_DATA][FILE_BITRATE]


#define Dac_Freq                RX_Buffer[TYPE_LCD_OTHER_DATA][DAC_FREQ]
#define Dac_Bit	                RX_Buffer[TYPE_LCD_OTHER_DATA][DAC_BIT]
#define File_Bit	              RX_Buffer[TYPE_LCD_OTHER_DATA][FILE_BIT]
#define File_Frec	              RX_Buffer[TYPE_LCD_OTHER_DATA][FILE_FREQ]
#define File_Codec              RX_Buffer[TYPE_LCD_OTHER_DATA][FILE_CODEC]
#define Flags_data              RX_Buffer[TYPE_LCD_OTHER_DATA][FLAGS]

#define pSPI_DATA		((uint8_t*)	&RX_Buffer[TYPE_SPI_DATA][1])		
#define SPI_LEN			RX_Buffer[TYPE_SPI_DATA][61]		
#define SPI_PART		RX_Buffer[TYPE_SPI_DATA][62]		
#define SPI_OPT			RX_Buffer[TYPE_SPI_DATA][63]		
#define SPI_PORT		RX_Buffer[TYPE_SPI_DATA][64]
#define LCD_BRIG		RX_Buffer[TYPE_LCD_BRIG][1]	

#define pCOLOR_par_name						((uint16_t*)	&(RX_Buffer[TYPE_LCD_COLORS][1]))	//���� ����� ���������
#define pCOLOR_par_value					((uint16_t*)	&(RX_Buffer[TYPE_LCD_COLORS][3]))	//���� �������� ���������
#define pCOLOR_par_value_wrng			((uint16_t*)	&(RX_Buffer[TYPE_LCD_COLORS][5]))	//���� ���������� �������� ���������	
#define pCOLOR_par_progress_bar		((uint16_t*)	&(RX_Buffer[TYPE_LCD_COLORS][7]))	//���� ������������

extern volatile bool flag_ready_usbhid_data;//������ ������ �� USB
extern volatile bool flag_ready_gui_frame;	//������ ������
extern volatile bool flag_ready_spi_data;		//������ ������ ��� �������� �� SPI
extern volatile bool flag_ready_lcd_brig;		//������ ������� �������
extern volatile bool flag_ready_get_version;//������ ������ ������
extern volatile bool flag_ready_gui_colors;	//������ ��������� ������
extern volatile bool flag_ready_msg_toast;	//��������� ������

int count_down(volatile int* arg_counter);

//toast
extern volatile uint8_t  flag_len_toast;
extern volatile int  flag_count_sec_toast; //�������� �������� ��� toast ���������
void 	count_toast_reset(int arg_sec);

//w
extern volatile int  flag_count_sec_w;		 //�������� �������� ��� ������� W
void count_w_reset(int arg_sec);		

//nodata
extern volatile int  flag_count_sec_nodata;		 //�������� �������� ��� "���������� ������"
void count_nodata_reset(void);	

//enc2mode 
#define ENC_MODE2_SEC 7
extern volatile int  flag_count_enc2mode;  //�������� �������� ��� �������� �������� � ������ �����
void count_enc2mode_reset(int arg_sec);
	
//
extern volatile int  flag_screen_mode;
extern volatile int  flag_screen_mode_pre;
void 	set_print_screen_mode	(int arg_new_mode);



extern volatile bool flag_mode_vol_encoder; //����� ������������ ����������� �������� (� ������ ����� ���� �������)


extern struct sspi_desc sspi_1; //SSPI ���������� 1  (pga2310)
extern struct sspi_desc sspi_2;	//SSPI ���������� 2  (��������� ���������)

extern uint8_t TX_Buffer[65]; //����� ��������� �� USB HID ������ 65 ���� �� ����������
extern uint8_t RX_Buffer[TYPE_NUM_LAST][65];


enum num_spi_port
	{
	SSPI_PORT_1 = 0,
	SSPI_PORT_2,
	SSPI_PORT_3
	};
	
#define PRINT_SCREEN_MODE_GUI 			0 //���������� ������� �����
#define PRINT_SCREEN_MODE_POFF			1 //���������� ��������� ������
#define PRINT_SCREEN_MODE_TOAST			2 //���������� ���������
	

#define VOLUME_ENC_MODE_VOLUME 1
#define VOLUME_ENC_MODE_CURSOR 0

#define	TEST_LED_SET 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET)	
#define	TEST_LED_RESET 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET)
#define PIN_WORK_SET 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)
#define PIN_WORK_RESET 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET)

//������ ������ 2-�� �������
extern volatile int t2_mode; 												//����� ������� 2 (����� �����)
void T2_add_mode(uint32_t arg_mode, int arg_time); 	//�������� ����� �������	
#define T2_MODE_DISABLE  0
#define T2_MODE_ENCVOLM  1				//� ���� ������ ������ �������� ����� �������� � ���������� ����������
#define T2_MODE_W_RESET (1 << 1)  //� ���� ������ ������ ������ ������ W  ��� ����������� ������
#define T2_MODE_DISPMSG (1 << 2)  //� ���� ������ ������ ������ ���� ����������� toast ���������	
#define T2_MODE_USBDATA (1 << 3)  //� ���� ������ ������ ��������� ��������� ��� ���������� ������	
#endif
