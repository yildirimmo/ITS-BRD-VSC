#include "stm32f429xx.h"
#include <stdlib.h>
#include <stdio.h>

static char PHASE_A;
static char PHASE_B; 
static char PHASE_C;
static char PHASE_D;
static uint8_t MASK_A = 0x00; //Kanal A = 0, Kanal B = 0
static uint8_t MASK_B = 0x01; //Kanal A = 1, Kanal B = 0
static uint8_t MASK_C = 0x03; //Kanal A = 1, Kanal B = 1
static uint8_t MASK_D = 0x02; //Kanal A = 0, Kanal B = 1




/**
 * @brief Hier wird das Signal aus den Kanälen (aus dem 
 * Pi Pico) gelesen und den einzelnen Phasen zugeordnet
 * 
 * Lesen aus GPIOF->IDR
 */
uint32_t zuordnung_Signal(){
    uint8_t current = (uint8_t)GPIOF->IDR;
    uint8_t state = (current & 0x03); //um pf0 und pf1 anzugucken im idr register, der rest ist egal

    //Masken für die Phasen implementieren und vergleichen
    //Rückgabe ist einfach welche Phase gerade ist
    PHASE_A = (MASK_A == (state & MASK_A));
    PHASE_B = (MASK_B == (state & MASK_B));
    PHASE_C = (MASK_C == (state & MASK_C));
    PHASE_D = (MASK_D == (state & MASK_D));

    if(PHASE_A){
        return 1; //Returne etwas, was dem Aufrufer sagt, welche Phase gerade ist.
    }
    if(PHASE_B){
        return 1; //Returne etwas, was dem Aufrufer sagt, welche Phase gerade ist.
    }
    if(PHASE_C){
        return 1; //Returne etwas, was dem Aufrufer sagt, welche Phase gerade ist.
    }
    if(PHASE_D){
        return 1; //Returne etwas, was dem Aufrufer sagt, welche Phase gerade ist.
    }
    
    return 1;
}

/**
 * @brief Hier wird die Phase zugeordnet 
 */
uint32_t zuordnung_Phasenwechsel(){
    return 1;
}

/**
 * @brief 
 */
uint32_t drehgrad_messer(){
    return 1;
}

uint32_t s6_leser(){
    //hier soll gelesen werden, ob s6 gedrückt wurde
    return 1;
}

