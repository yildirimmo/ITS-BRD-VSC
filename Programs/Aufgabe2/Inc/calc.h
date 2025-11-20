#ifndef CALC_H
#include <stdint.h>
#define CALC_H
#define COUNTS_MAX 1200.0       
#define DEGREE_MAX 360




double drehwinkelrechner(int32_t val);

double geschwindigkeitsrechner(double winkel2, double winkel1, double zeit_in_sek);
#endif