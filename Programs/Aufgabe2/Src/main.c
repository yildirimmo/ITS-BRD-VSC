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


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

	initTimer();					// Initialisierung des LCD Boards
	input_init();
	output_init();

	
	int32_t phasenZähler = 0;
	
	uint32_t current_ts = 0;
	
	uint8_t current_phase = 0;

	uint32_t zuordnung = 0;

	double current_winkel = 0.0f;

	uint8_t letztePhase = zuordnung_Signal() & 0x03;

	uint32_t last_ts = getTimeStamp();

	double last_winkel = drehwinkelrechner(phasenZähler);

	uint32_t time = 0; //um zu sehen, wie viel millisekunden vorbei sind, um alle 250 ms display upzudaten

	double geschwindigkeit = 0;


	// Test in Endlosschleife
	while(1) {

		
		current_phase = zuordnung_Signal() & 0x03;

		current_ts = getTimeStamp();

		current_winkel = drehwinkelrechner(phasenZähler);
		
		zuordnung = zuordnung_Phasenwechsel(letztePhase, current_phase);

		geschwindigkeit = geschwindigkeitsrechner(current_winkel, last_winkel, current_ts, last_ts);
		
		letztePhase = current_phase;

		last_winkel = current_winkel;

		time += ( last_ts - current_ts ) * (1/90);
		last_ts = current_ts;

		
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
		} else {
		}

		

	}


}






// EOF
