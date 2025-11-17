#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "lcd.h"
#include "timer.h"
#include "input.h"
#include "output.h"

#define MODER_MASK_PE7 (0x33 << (8*2))




/**
 * @brief Der Drehwinkel wird auf dem Display ausgegeben
 */
void drehwinkel_ausgeben(double val){
    lcdGotoXY(25, 25);
    printf("Winkel\t:%f\tGrad", val);
}


/**
 * @brief die Geschwindigkeit wird auf dem Display ausgegeben
 */
void winkelgeschwindigkeit_ausgeben(double val){
    lcdGotoXY(25, 50);
    //lcdPrintS("Geschwindigkeit\t:%u\tGrad/s");
    printf("Winkel\t:%f\tGrad/s", val);
}

void led_einschalten(){
    //hier sollen die leds d8 - d15 ausgegeben werden je nach dem, welche phase gerade ist
}

void led_vorwaerts(){
    //d23 anschalten
    GPIOE->BSRR = (0x01 << 8);
}

void led_rueckwaerts(){
    //d22 anschalten
    GPIOE->BSRR = (0x01 << 7);
}

void led_fehler(){
    //d21 anschalten
    GPIOE->BSRR = (0x01 << 6);
}

void fehler_zurücksetzen(){
    GPIOE->BSRR = (0x01 << (6 + 16));
}

void output_init(){
    GPIOE->MODER &= ~MODER_MASK_PE7;
}

