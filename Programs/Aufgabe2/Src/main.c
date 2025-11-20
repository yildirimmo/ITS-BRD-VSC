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

    initTimer();                    // Initialisierung des LCD Boards
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

    double time_messung = 0.0f; // gesammelte Zeit in Mikrosekunden

    uint32_t diff_ticks = 0;

    double verstrichene_zeit = 0.0f;


    // Test in Endlosschleife
    while(1) {
        
        // aktuellen ts holen
        current_ts = getTimeStamp();

        // Aktuelle Phase einlesen
        current_phase = zuordnung_Signal() & 0x03;

        // Winkelberechnung
        current_winkel = drehwinkelrechner(phasenZähler);
        
        // Phasenwechsel bestimmen
        zuordnung = zuordnung_Phasenwechsel(letztePhase, current_phase);

        // switch um phasenwechsel zuzuordnen und LEDs zu setzen
        switch(zuordnung){
            case VORWÄRTSLAUF:
                led_vorwaerts();
                phasenZähler++;
                led_einschalten(phasenZähler); // LEDs Binärzähler update noch zu implementieren
                break;

            case RÜCKWÄRTSLAUF:
                led_rueckwaerts();
                phasenZähler--;
                led_einschalten(phasenZähler); // LEDs Binärzähler update noch zu implementieren
                break;

            case NOCHANGE:
                break;
            
            case FEHLER:
                led_fehler();
                break;
        }

        letztePhase = current_phase;
        
        // Erkennung ob s6 gedrückt wurde
        s6_leser();


        // Zeitmessung
        diff_ticks = current_ts - last_ts; 
        last_ts = current_ts; 

        // Ticks in Mikrosekunden umrechnen (Ticks / 90 = mikros)
        // Beispiel: 90 Ticks sind 1 µs.
        verstrichene_zeit = (double)diff_ticks / 90.0;

        // Zur gesammelten Zeit addieren
        time_messung += verstrichene_zeit;

        // Sind 250.000 Mikrosekunden (250ms) vergangen?
        if (time_messung >= 250000.0) {
            
            // Sekundenumrechnung
            double time_in_seconds = time_messung / 1000000.0; 

            // Winkeländerung / Zeit in Sekunden
            double speed = 0.0;
            if (time_in_seconds > 0.0) {
                 speed = (current_winkel - last_winkel) / time_in_seconds; //(w2 - w1) / (t2 - t1)
            }
            
            // Ausgabe
            drehwinkel_ausgeben(current_winkel);
            winkelgeschwindigkeit_ausgeben(speed); // Zeigt Grad/Sekunde an

            // Reset für die nächste Runde
            last_winkel = current_winkel;
            time_messung = 0.0;
        }
    }

}

// EOF