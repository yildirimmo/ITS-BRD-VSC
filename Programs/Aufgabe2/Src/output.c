#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "lcd.h"
#include "timer.h"
#include "input.h"





/**
 * @brief Der Drehwinkel wird auf dem Display ausgegeben
 */
void drehwinkel_ausgeben(uint16_t val){
    //lcdPrintS("Winkel\t:%d\tGrad", val);
    printf("Winkel\t:%d\tGrad", val);
}


/**
 * @brief die Geschwindigkeit wird auf dem Display ausgegeben
 */
void winkelgeschwindigkeit_ausgeben(uint16_t val){
    //lcdPrintS("Geschwindigkeit\t:%u\tGrad/s");
    printf("Winkel\t:%d\tGrad", val);
}

void led_einschalten(){
    //hier sollen die leds d8 - d15 ausgegeben werden je nach dem, welche phase gerade ist
}

void led_vorwaerts(){
    //d23, wenn vorwärtsrichtung erkannt
    uint16_t input_a = zuordnung_Signal();

    uint16_t input_b = zuordnung_Signal();

}

void led_rueckwaerts(){
    //d22 wenn rückwärtsrichtung erkannt
}

void led_fehler(){
    //d21 wenn fehler erkannt
}

