/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "timer.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include <stdint.h>
#include "output.h"
#include "input.h"

static uint8_t letztePhase = PHASE_A;
static int32_t phasenZähler = 0;
static int32_t letzter_zähler = 0;
static uint32_t last_ts = 0;

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

	initTimer();					// Initialisierung des LCD Boards
	input_init();
	output_init();
	

	uint32_t last_update = 0;
	
	uint32_t current_ts = 0;
	uint8_t mach_update;


	last_ts = getTimeStamp();
	// Test in Endlosschleife
	while(1) {


		current_ts = getTimeStamp();
		

		//update
		if (current_ts - last_update >= 250){
			last_update = current_ts;
			mach_update = 1;
		} else {
			mach_update = 0;
		}


		if (mach_update){
			drehwinkel_ausgeben(2); //gelesener Wert aus Python
			winkelgeschwindigkeit_ausgeben(2); //gelesener wert aus python bzw gpiof -> idr
		}


	}


}




// EOF
