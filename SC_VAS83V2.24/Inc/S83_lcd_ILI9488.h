#ifndef _S83_LCD_ILI9488_H_
#define _S83_LCD_ILI9488_H_

#include "S83_configuration.h"

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
