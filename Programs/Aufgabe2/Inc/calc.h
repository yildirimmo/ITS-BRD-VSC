#ifndef CALC_H
#define CALC_H
#include <stdint.h>

double drehwinkelrechner(int32_t val);

double geschwindigkeitsrechner(double winkel2, double winkel1, uint32_t t2, uint32_t t1);
#endif