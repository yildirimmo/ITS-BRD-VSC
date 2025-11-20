#include "calc.h"

#define TICKS_PER_SECOND 90000000.0 // Timer läuft mit 90 MHz (90 Ticks pro us)
#define COUNTS_MAX 1200.0       
#define DEGREE_MAX 360

double drehwinkelrechner(int32_t val){
    /*
    Beispiel: val = 600
    600/1200 = 0,5
    0,5 * 360 = 180
    */
    return ((double)val / COUNTS_MAX) * DEGREE_MAX;
}

double geschwindigkeitsrechner(double winkel_neu, double winkel_alt, double zeit_in_sek){
    double winkel_diff = winkel_neu - winkel_alt;

    // Division durch null 
    if(zeit_in_sek == 0.0) {
        return 0.0;
    }

    // Berechnung: Grad pro Sekunde
    return winkel_diff / zeit_in_sek;
}