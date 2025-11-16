#include "stm32f429xx.h"
#include <stdlib.h>
#include <stdio.h>

// Kanal A = GPIOF IDR PIN 0 
// Kanal B = GPIOF IDR PIN 1
#define PHASE_A 0x00 //Kanal A = 0, Kanal B = 0
#define PHASE_B 0x01 //Kanal A = 1, Kanal B = 0
#define PHASE_C 0x03 //Kanal A = 1, Kanal B = 1
#define PHASE_D 0x02 //Kanal A = 0, Kanal B = 1
#define RÜCKWÄRTSLAUF 0x01
#define NOCHANGE 0x02
#define VORWÄRTSLAUF 0x03
#define FEHLER 0x04

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
 * @brief Hier werden die Phasen zugeordnet 
 * @param phase1 die erste aufgezeichnete Phase
 * @param phase2 die zweite aufgezeichnete Phase
 * @return Gibt den Phasenwechsel zurück
 */
uint32_t zuordnung_Phasenwechsel(uint8_t phase1, uint8_t phase2){
    //uint8_t letztePhase;
    //uint8_t aktuellePhase;

    //Phase 1 bestimmen
    //Phase 1 = A?
    if (phase1 == PHASE_A){
        //letztePhase = PHASE_A;
        //Phase 2 bestimmen
        if (phase2 == PHASE_A){
            //aktuellePhase = PHASE_A;
            return NOCHANGE;
        }
        else if(phase2 == PHASE_B){
            //aktuellePhase = PHASE_B;
            return VORWÄRTSLAUF;
        }
        else if(phase2 == PHASE_C){
            //aktuellePhase = PHASE_C;
            return FEHLER;
        }
        else{
            //aktuellePhase = PHASE_D;
            return RÜCKWÄRTSLAUF;
        }

    } 

    //Phase 1 = B?
    else if(phase1 == PHASE_B){
        //letztePhase = PHASE_B;
        //Phase 2 bestimmen
        if (phase2 == PHASE_A){
            //aktuellePhase = PHASE_A;
            return RÜCKWÄRTSLAUF;
        }
        else if(phase2 == PHASE_B){
            //aktuellePhase = PHASE_B;
            return NOCHANGE;
        }
        else if(phase2 == PHASE_C){
            //aktuellePhase = PHASE_C;
            return VORWÄRTSLAUF;
        }
        else{
            //aktuellePhase = PHASE_D;
            return FEHLER;
        }
        
    }

    //Phase 1 = C?
    else if(phase1 == PHASE_C){
        //letztePhase = PHASE_C;
                //Phase 2 bestimmen
        if (phase2 == PHASE_A){
            //aktuellePhase = PHASE_A;
            return FEHLER;
        }
        else if(phase2 == PHASE_B){
            //aktuellePhase = PHASE_B;
            return RÜCKWÄRTSLAUF;
        }
        else if(phase2 == PHASE_C){
            //aktuellePhase = PHASE_C;
            return NOCHANGE;
        }
        else{
            //aktuellePhase = PHASE_D;
            return VORWÄRTSLAUF;
        }
    }

    //Phase 1 = D?
    else{
        //letztePhase = PHASE_D;
                //Phase 2 bestimmen
        if (phase2 == PHASE_A){
            //aktuellePhase = PHASE_A;
            return VORWÄRTSLAUF;
        }
        else if(phase2 == PHASE_B){
            //aktuellePhase = PHASE_B;
            return FEHLER;
        }
        else if(phase2 == PHASE_C){
            //aktuellePhase = PHASE_C;
            return RÜCKWÄRTSLAUF;
        }
        else{
            //aktuellePhase = PHASE_D;
            return NOCHANGE;
        }
    }
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

