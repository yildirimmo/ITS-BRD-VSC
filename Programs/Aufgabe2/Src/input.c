#include "stm32f429xx.h"
#include <stdlib.h>
#include <stdio.h>

static int PHASE_A; //maske für phase a aus dem gpiof idr register
static int PHASE_B; 
static int PHASE_C;
static int PHASE_D;




/**
 * @brief Hier wird das Signal aus den Kanälen (aus dem 
 * Pi Pico) gelesen und den einzelnen Phasen zugeordnet
 * 
 * Lesen aus GPIOF->IDR
 */
int zuordnung_Signal(){
    uint32_t current = GPIOF->IDR;
    //Masken für die Phasen implementieren und vergleichen
    //Rückgabe ist einfach welche Phase gerade ist
    char phase_a_pressed;
    return 1;
}

/**
 * @brief Hier wird die Phase zugeordnet 
 */
int zuordnung_Phasenwechsel(){
    return 1;
}

/**
 * @brief 
 */
int drehgrad_messer(){
    return 1;
}

int s6_leser(){
    //hier soll gelesen werden, ob s6 gedrückt wurde
    return 1;
}

