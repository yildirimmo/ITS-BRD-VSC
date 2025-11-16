#include "stm32f429xx.h"
#include <stdlib.h>
#include <stdio.h>

#define PHASE_A 0x00 //Kanal A = 0, Kanal B = 0
#define PHASE_B 0x01 //Kanal A = 1, Kanal B = 0
#define PHASE_C 0x03 //Kanal A = 1, Kanal B = 1
#define PHASE_D 0x02 //Kanal A = 0, Kanal B = 1

/**
 * @brief Hier wird das Signal aus den Kanälen (aus dem 
 * Pi Pico) gelesen und den einzelnen Phasen zugeordnet
 * 
 * @return state, welches den jetzigen Zustand abbildet
 */
uint32_t zuordnung_Signal(){
    uint8_t current = (uint8_t)GPIOF->IDR;
    uint8_t state = (current & 0x03); //um pf0 und pf1 anzugucken im idr register, der rest ist egal
    if (PHASE_A == state){
        return PHASE_A;
    }else if (PHASE_B == state){
        return PHASE_B;
    }else if (PHASE_C == state){
        return PHASE_C;
    }else {
        return PHASE_D;
    }
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

