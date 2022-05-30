#include <assert.h>
#include "Conversion.h"
#include <stdio.h>
#include <stdlib.h>

int errorAceptable (double, double, float);

int main (void) {
assert (errorAceptable (Celsius (20),-6.6667,0.1));
assert (errorAceptable (Celsius (115),46.1111,0.1));
assert (errorAceptable (Celsius (190),87.7778,0.1));
assert (errorAceptable (Celsius (220),104.444,0.1));
printf ("No hay errores en: Fahrenheit a Celsius\n");
assert (errorAceptable (Fahrenheit (37),98.6,0.1));
assert (errorAceptable (Fahrenheit (134),273.2,0.1));
assert (errorAceptable (Fahrenheit (200),392.0,0.1));
assert (errorAceptable (Fahrenheit (290),554.0,0.1));
printf ("No hay errores en: Celsius a Fahrenheit\n");

}

int errorAceptable (double temp, double valor, float epsilon){
    if ( abs (temp - valor) < epsilon) // se toma como valido un valor obtenido cuyo error con respecto al valor real sea menor al |0.1|
    return 1;    
    else 
    return 0;
}