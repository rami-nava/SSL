#include <assert.h>
#include "Conversion.h"
#include <stdio.h>
#include <stdlib.h>

int casiIgual (double, double);


int main (void) {
assert (casiIgual (GetCelsFromFahr (20),-6.6667));
assert (casiIgual (GetCelsFromFahr (115),46.1111));
assert (casiIgual (GetCelsFromFahr (190),87.7778));
assert (casiIgual (GetCelsFromFahr (220),104.444));
assert (casiIgual (GetFahrFromCels (37),98.6));
assert (casiIgual (GetFahrFromCels (134),273.2));
assert (casiIgual (GetFahrFromCels (200),392.0));
assert (casiIgual (GetFahrFromCels (290),554.0));
printf("NO HAY ERRORES EN LOS TESTS\n");
}

int casiIgual (double temp, double valor){
    if ( abs (temp - valor) < 0.1) // se toma como valido un valor obtenido cuyo error con respecto al valor real sea menor al |0.1|
    return 1;    
    else 
    return 0;
}