#ifndef INPUT_H
#define INPUT_H
#include <stdint.h>

#define PHASE_A 0x00 
#define PHASE_B 0x01 
#define PHASE_C 0x03 
#define PHASE_D 0x02 
#define RÜCKWÄRTSLAUF 0x01
#define NOCHANGE 0x02
#define VORWÄRTSLAUF 0x03
#define FEHLER 0x04
#define MODER_MASK_PF0_PF1 0x1
#define MODER_MASK_PF7 (0x1 << (7*2))

uint32_t zuordnung_Signal();

uint32_t zuordnung_Phasenwechsel(uint32_t phase1, uint32_t phase2);

uint32_t drehgrad_messer();

uint32_t s6_leser();

void input_init();
#endif