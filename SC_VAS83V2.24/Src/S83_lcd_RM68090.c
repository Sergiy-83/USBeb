#include "S83_lcd_RM68090.h"





void LCD_Init_RM68090(void)
	{
	LCD_Init_pins(); 	delay(10);
	RST_RESET; 				delay(100);
	RST_SET;					delay(100);
	
	//************* Reset LCD Driver ****************//
	LCD_write_register(0x0001, 0x0100); // set SS and SM bit               100
	LCD_write_register(0x0002, 0x0700); // set 1 line inversion
	
	#ifdef 	portrait
	LCD_write_register(0x0003, 0x1030); // set GRAM write direction and BGR=1 def1030
	#endif
	#ifdef 	landscape
	LCD_write_register(0x0003, 0x1028); // set GRAM write direction and BGR=1 def1030
	#endif
		
	LCD_write_register(0x0004, 0x0000); // Resize register
	LCD_write_register(0x0008, 0x0202); // set the back porch and front porch
	LCD_write_register(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
	LCD_write_register(0x000A, 0x0000); // FMARK function disable
	LCD_write_register(0x000C, 0x0000); // RGB interface setting
	LCD_write_register(0x000D, 0x0000); // Frame marker Position
	LCD_write_register (0x000F, 0x0000); // RGB interface polarity
	delay(20); // Delay 10 ms
	//*************Power On sequence ****************//
	LCD_write_register(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_write_register (0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	LCD_write_register (0x0012, 0x0000); // VREG1OUT voltage
	LCD_write_register (0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
	LCD_write_register (0x0007, 0x0001);
	LCD_write_register (0x0007, 0x0020);
	delay(200); // Dis-charge capacitor power voltage
	LCD_write_register(0x0010, 0x1490); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_write_register(0x0011, 0x0117); // Set DC1[2:0], DC0[2:0], VC[2:0]
	delay(80); // Delay 50ms
	LCD_write_register(0x0012, 0x008E); // Internal reference voltage
	delay(20); // Delay 10ms
	LCD_write_register(0x0013, 0x1B00); // VDV[4:0] for VCOM amplitude

	LCD_write_register(0x0029, 0x001D); // VCM[5:0] for VCOMH
	LCD_write_register(0x002B, 0x000C); // Set Frame Rate
	delay(80); // Delay 50ms
	LCD_write_register(0x0020, 0x0000); // GRAM horizontal Address
	LCD_write_register(0x0021, 0x0000); // GRAM Vertical Address
	// ----------- Adjust the Gamma Curve ----------//
	LCD_write_register(0x0030, 0x0000);
	LCD_write_register(0x0031, 0x0307);
	LCD_write_register(0x0032, 0x0202);
	LCD_write_register(0x0035, 0x0007);
	LCD_write_register(0x0036, 0x1000);
	LCD_write_register(0x0037, 0x0505);
	LCD_write_register(0x0038, 0x0004);
	LCD_write_register(0x0039, 0x0707);
	LCD_write_register(0x003C, 0x0700);
	LCD_write_register(0x003D, 0x0010);
	//------------------ Set GRAM area Область заливки---------------//
	LCD_write_register(0x0050, 0x0000); // Horizontal GRAM Start Address
	LCD_write_register(0x0051, 0x00EF); // Horizontal GRAM End Address
	LCD_write_register(0x0052, 0x0000); // Vertical GRAM Start Address
	LCD_write_register(0x0053, 0x013F); // Vertical GRAM Start Address
	LCD_write_register(0x0060, 0xA700); // Gate Scan Line
	LCD_write_register(0x0061, 0x0001); // NDL,VLE, REV
	LCD_write_register(0x006A, 0x0000); // set scrolling line
	//-------------- Panel Control -------------------//
	LCD_write_register(0x0090, 0x0010);
	LCD_write_register(0x0092, 0x0000);
	delay(20); // Delay 10ms
	LCD_write_register(0x0007, 0x0133); // 262K color and display ON
	}
	
void LCD_EnterSleep_RM68090(void)
	{
	LCD_write_register(0x0007, 0x0131); // Set D1=0, D0=1
	delay(20); // Delay 10ms
	LCD_write_register(0x0007, 0x0130); // Set D1=0, D0=0

	delay(20); // Delay 10ms
	LCD_write_register(0x0007, 0x0000); // display OFF
	//************* Power OFF sequence **************//
	LCD_write_register(0x0010, 0x0080); // SAP, BT[3:0], APE, AP, DSTB, SLP
	LCD_write_register(0x0011, 0x0000); // DC1[2:0], DC0[2:0], VC[2:0]
	LCD_write_register(0x0012, 0x0000); // VREG1OUT voltage
	LCD_write_register(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
	delay(80); // Dis-charge capacitor power voltage
	LCD_write_register(0x0010, 0x0082); // SAP, BT[3:0], APE, AP, DSTB, SLP
	}
	
void LCD_ExitSleep_RM68090(void)
	{
	//*************Power On sequence ******************//
	LCD_write_register(0x0010, 0x0080); // SAP, BT[3:0], AP, DSTB, SLP
	delay(80); // Dis-charge capacitor power voltage
	LCD_write_register(0x0010, 0x1490); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_write_register(0x0011, 0x0117); // DC1[2:0], DC0[2:0], VC[2:0]
	delay(100); // Delay 80ms
	LCD_write_register(0x0012, 0x008E); // External reference voltage =Vci;
	delay(20); // Delay 10ms
	LCD_write_register(0x0013, 0x1900); // VDV[4:0] for VCOM amplitude
	LCD_write_register(0x0029, 0x0023); // VCM[5:0] for VCOMH
	delay(80); // Delay 50ms
	LCD_write_register(0x0007, 0x0133); // 262K color and display ON
	}
	
//Запись комманды - регистра
void LCD_write_command(uint16_t arg_cmd)
	{
	RS_RESET;
	//LCD_DATA_PORT = arg_cmd >> 8;
	//PULSE_WR;

	//LCD_DATA_PORT = arg_cmd;
	//PULSE_WR;
	WRITE_DATA_FAST_2B(arg_cmd);
	RS_SET;	
	}
//Запись данных
void LCD_write_data (uint16_t arg_data)
	{
	WRITE_DATA_FAST_2B(arg_data);
	}
	
// Запись в регистр arg_reg данных arg_data
void LCD_write_register (uint16_t arg_reg, uint16_t arg_data)
	{
	LCD_write_command ( arg_reg);
	LCD_write_data (arg_data);
	}
	
void LCD_Init_pins(void)
	{
	RST_SET;
	WR_RESET;
	RD_SET;
	RS_RESET;
	CS_RESET;
	}	
	
	// Установка области, к которую будут заноситься данные
void LCD_set_window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
	{
	#ifdef portrait 
	LCD_write_register(0x20,x1);
	LCD_write_register(0x21,y1);
	LCD_write_register(0x50,x1);
	LCD_write_register(0x52,y1);
	LCD_write_register(0x51,x2);
	LCD_write_register(0x53,y2);
	LCD_write_command(0x22); 
	#endif
		
	#ifdef landscape 	
	uint16_t _x1=239-y2;

	//LCD_write_register(0x20,_x1);
	LCD_write_register(0x20,239-y1);
	LCD_write_register(0x21,x1);
		
	LCD_write_register(0x50,_x1);
	LCD_write_register(0x52,x1);
	LCD_write_register(0x51,239-y1);
	LCD_write_register(0x53,x2);
	LCD_write_command(0x22);



	#endif	
	}
