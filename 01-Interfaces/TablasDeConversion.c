#include <stdio.h>
#include "Conversion.h"

int main (void){
    const int LOWER = 0;
    const int UPPER = 300;
    const int STEP = 20;    

    printf ("Fahrenheit a Celsius | Celsius a Fahrenheit\n");
    for (int temp = LOWER; temp <= UPPER; temp += STEP)
    printf ("%6d °F = %5.1f °C | %5d °C = %5.1f °F\n",temp,GetCelsFromFahr (temp),temp, GetFahrFromCels (temp));
}
