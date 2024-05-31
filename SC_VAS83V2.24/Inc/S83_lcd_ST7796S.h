#ifndef __S83_LCD_ST7796S_H
#define __S83_LCD_ST7796S_H

#include "S83_configuration.h"



//Выбор ориентации
#define landscape 1

#define X_MAX 479
#define Y_MAX 319


	#ifdef 	CONFIG_ORIENTATION_PORTRAIT_01
		#define X_MAX 319
		#define Y_MAX 479
	#endif

	#ifdef 	CONFIG_ORIENTATION_PORTRAIT_02
		#define X_MAX 319
		#define Y_MAX 479
	#endif

	#ifdef 	CONFIG_ORIENTATION_LANDSCAPE_01
		#define X_MAX 479
		#define Y_MAX 319
	#endif

	#ifdef 	CONFIG_ORIENTATION_LANDSCAPE_02
		#define X_MAX 479
		#define Y_MAX 319
	#endif


#endif
