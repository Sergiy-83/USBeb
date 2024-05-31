#ifndef __S83_CONFIGURATION_H
#define __S83_CONFIGURATION_H

//Выбрать перед компиляцией
//Закоментировать ненужные



//Выбор графического интерфейса плеера для разных разрешений экрана
//#define CONFIG_GUI_320x240 
#define CONFIG_GUI_480x320 

//Выбор контроллера дисплея
//#define CONFIG_LCD_ILI9481 	//480x320 Работает предположительно на ILI9481
//#define CONFIG_LCD_R61581		//480x320
#define CONFIG_LCD_ILI9486 	//480x320 
//#define CONFIG_LCD_ILI9488 	//480x320 Не проверялся. Вероятность работоспособности 90% 
//#define CONFIG_LCD_ST7796S  //480x320
//#define CONFIG_LCD_ILI9325 	//Выбрать 320x240
//#define CONFIG_LCD_RM68090 	//Выбрать 320x240

//Выбор режима входов кнопок UP и DOWN закоментить что то одно
#define CONFIG_UPDOWN_BUTTONS				//Обычные кнопки UP DOWN и энкодер регулятора громкости
//#define CONFIG_UPDOWN_ENCODER			//Дополнительный энкодер на входах для кнопок UP DOWN


#ifndef CONFIG_UPDOWN_ENCODER //Если не включен режим второго энкодера
	//#define CONFIG_VOL_ENCODER_MODE_2		//Включение режима управления только энкодером регулятора громкости, раскоментровать эту строчку если нужен этот режим
#endif


#ifdef CONFIG_VOL_ENCODER_MODE_2
	//#define CONFIG_SWITCH_CURSOR_FN1		//Переключение режима управления энкодера громкости с помощью кнопки FN1 (кастомизация для Набиулина)
#endif



//Выбор ориетации картинки
#define CONFIG_ORIENTATION_LANDSCAPE_01 1
//#define CONFIG_ORIENTATION_LANDSCAPE_02 1
//При разрешении GUI 320x240 возможно отображение на дисплеях 
//с разрешением 480x320 в портретной ориентации
//#define CONFIG_ORIENTATION_PORTRAIT_01
//#define CONFIG_ORIENTATION_PORTRAIT_02


//Здесь ничего не трогаем
#ifdef CONFIG_GUI_480x320
	#define CONFIG_S83_FONT_8x16 1
#endif

#ifdef CONFIG_GUI_320x240
	#define CONFIG_S83_FONT_8x12 1
#endif

#endif
