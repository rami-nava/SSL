#include <stdio.h>
#include "Conversion.h"

    const int LOWER = 0;
    const int UPPER = 300;
    const int STEP = 20;    

int main (void){
    printf ("Fahrenheit a Celsius | Celsius a Fahrenheit\n");
    for (int temp = LOWER; temp <= UPPER; temp += STEP)
    printf ("%6d °F = %5.1f °C | %5d °C = %5.1f °F\n",temp,Celsius (temp),temp, Fahrenheit (temp));
}
