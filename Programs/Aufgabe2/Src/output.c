#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "lcd.h"
#include "timer.h"
#include "input.h"
#include "output.h"




static char buffer[50];
/**
 * @brief Der Drehwinkel wird auf dem Display ausgegeben
 */
void drehwinkel_ausgeben(double val){
    
    sprintf(buffer, "Winkel: %.2f deg    ", val); //50 magic number und benutze snprintf
    lcdGotoXY(2, 3);
    lcdPrintS(buffer);
    
}


/**
 * @brief die Geschwindigkeit wird auf dem Display ausgegeben
 */
void winkelgeschwindigkeit_ausgeben(double val){
    sprintf(buffer, "Speed:  %.2f deg/s   ", val);
    lcdGotoXY(2, 5);
    lcdPrintS(buffer);

}

void led_einschalten(uint32_t val){
    
    uint32_t set_bits = val & 0xFF;

    uint32_t reset_bits = (~val) & 0xFF;

    GPIOD->BSRR = set_bits | (reset_bits << 16);
}

void led_vorwaerts(){
    // d23 an (Pin 8 Port E), d22 aus
    GPIOE->BSRR = (1 << 7) | (1 << (6 + 16));
}

void led_rueckwaerts(){
    // d22 an (Pin 7 Port E), d23 aus
    GPIOE->BSRR = (1 << 6) | (1 << (7 + 16));
}

void led_fehler(){
    // d21 an

    GPIOE->BSRR = (1 << 5) | (1 << (7 + 15)) | (1 << (7 + 16));
}

void led_nochange(){
    GPIOE->BSRR = (1 << (7 + 15)) | (1 << (7 + 16));
}

void fehler_zurücksetzen(){
    // d21 aus (Reset Pin 6)
    GPIOE->BSRR = (1 << (5+16));
}

void output_init(){

    // Status LEDs an PE6, PE7, PE8
    GPIOE->MODER &= ~(0x3F << 12); // Löschen
    GPIOE->MODER |= (0x15 << 12);  // Output (01)

    // LEDs D8-D15 an Port D 
    GPIOD->MODER &= ~(0xFFFF);     // Löschen
    GPIOD->MODER |= 0x5555;        // Output (01) für alle 8 Pins
}