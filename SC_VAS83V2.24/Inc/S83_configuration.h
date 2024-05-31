#ifndef __S83_CONFIGURATION_H
#define __S83_CONFIGURATION_H

//������� ����� �����������
//��������������� ��������



//����� ������������ ���������� ������ ��� ������ ���������� ������
//#define CONFIG_GUI_320x240 
#define CONFIG_GUI_480x320 

//����� ����������� �������
//#define CONFIG_LCD_ILI9481 	//480x320 �������� ���������������� �� ILI9481
//#define CONFIG_LCD_R61581		//480x320
#define CONFIG_LCD_ILI9486 	//480x320 
//#define CONFIG_LCD_ILI9488 	//480x320 �� ����������. ����������� ����������������� 90% 
//#define CONFIG_LCD_ST7796S  //480x320
//#define CONFIG_LCD_ILI9325 	//������� 320x240
//#define CONFIG_LCD_RM68090 	//������� 320x240

//����� ������ ������ ������ UP � DOWN ����������� ��� �� ����
#define CONFIG_UPDOWN_BUTTONS				//������� ������ UP DOWN � ������� ���������� ���������
//#define CONFIG_UPDOWN_ENCODER			//�������������� ������� �� ������ ��� ������ UP DOWN


#ifndef CONFIG_UPDOWN_ENCODER //���� �� ������� ����� ������� ��������
	//#define CONFIG_VOL_ENCODER_MODE_2		//��������� ������ ���������� ������ ��������� ���������� ���������, ��������������� ��� ������� ���� ����� ���� �����
#endif


#ifdef CONFIG_VOL_ENCODER_MODE_2
	//#define CONFIG_SWITCH_CURSOR_FN1		//������������ ������ ���������� �������� ��������� � ������� ������ FN1 (������������ ��� ���������)
#endif



//����� ��������� ��������
#define CONFIG_ORIENTATION_LANDSCAPE_01 1
//#define CONFIG_ORIENTATION_LANDSCAPE_02 1
//��� ���������� GUI 320x240 �������� ����������� �� �������� 
//� ����������� 480x320 � ���������� ����������
//#define CONFIG_ORIENTATION_PORTRAIT_01
//#define CONFIG_ORIENTATION_PORTRAIT_02


//����� ������ �� �������
#ifdef CONFIG_GUI_480x320
	#define CONFIG_S83_FONT_8x16 1
#endif

#ifdef CONFIG_GUI_320x240
	#define CONFIG_S83_FONT_8x12 1
#endif

#endif
