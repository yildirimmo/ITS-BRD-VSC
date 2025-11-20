#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdint.h>
#define MODER_MASK_PE7 (0x33 << (8*2))

void drehwinkel_ausgeben(double val);

void winkelgeschwindigkeit_ausgeben(double val);

void led_einschalten(uint32_t val);

void led_vorwaerts();

void led_rueckwaerts();

void led_fehler();

void led_nochange();

void fehler_zurücksetzen();

void output_init();

#endif
