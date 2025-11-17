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
#include "calc.h"

static uint8_t letztePhase = PHASE_A;
static int32_t phasenZähler = 0;
static int32_t letzter_zähler = 0;
static uint32_t last_ts = 0;
uint32_t current_ts = 0;

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

	initTimer();					// Initialisierung des LCD Boards
	input_init();
	output_init();
	
	
	uint8_t mach_update;
	
	uint8_t current_phase;

	uint32_t zuordnung;

	double current_winkel;
	letztePhase = zuordnung_Signal();
	last_ts = getTimeStamp();
	double last_winkel = drehwinkelrechner(phasenZähler);
	// Test in Endlosschleife
	while(1) {

		
		current_phase = zuordnung_Signal();
		current_ts = getTimeStamp();
		current_winkel = drehwinkelrechner(phasenZähler);
		uint32_t zuordnung = zuordnung_Phasenwechsel(letztePhase, current_phase);
		
		//switch um phasenwechsel zuzuordnen
		switch(zuordnung){
			case VORWÄRTSLAUF:
				led_vorwaerts();
				phasenZähler++;
				break;

			case RÜCKWÄRTSLAUF:
				led_rueckwaerts();
				phasenZähler--;
				break;

			case NOCHANGE:
				break;
			
			case FEHLER:
				led_fehler();
				break;

		}
		//Erkennung ob s6 gedrückt wurde, wenn ja, wird led_fehler() zurückgesetzt
		s6_leser();

		//update display
		
		if (current_ts - last_ts >= 250){
			last_ts = current_ts;
			mach_update = 1;
		} else {
			mach_update = 0;
		}

		

	}


}






// EOF
