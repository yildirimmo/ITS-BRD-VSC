#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
static int32_t maxDegree = 360;
static int32_t maxCount = 1200;

double drehwinkelrechner(int32_t val){
    double temp = ((double)maxDegree / (double)maxCount) * val ;
    double result = 0;
    result = (maxCount * temp)/360;
    return result;
}

double geschwindigkeitsrechner(double winkel2, double winkel1, uint32_t t2, uint32_t t1){
    double zähler = winkel2 - winkel1;
    double nenner = (double)t2 - (double)t1; 
    double result = zähler/nenner;
    return result;
}