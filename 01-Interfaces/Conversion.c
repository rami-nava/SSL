#include "Conversion.h"
#include <stdio.h>

double GetCelsFromFahr (double f){
    return (5.0/9.0)*(f-32);
}

double GetFahrFromCels (double c){
    return (c*9.0/5.0) + 32;
}

void printTablas (const int LOWER,const int UPPER,const int STEP){
    printTablaCelsius (LOWER,UPPER,STEP);
    printTablaFahrenheit (LOWER,UPPER,STEP);
}

void printTablaCelsius (const int LOWER,const int UPPER,const int STEP){
    printf ("Tabla 1: Celsius a Fahrenheit\n");
    printFilasCelsius(LOWER,UPPER,STEP);
}

void printTablaFahrenheit (const int LOWER,const int UPPER,const int STEP){
    printf ("Tabla 2: Fahrenheit a Celsius\n");
    printFilasFahrenheit(LOWER,UPPER,STEP);
}

void printFilasCelsius(const int LOWER,const int UPPER,const int STEP){
    for (int temp = LOWER; temp <= UPPER; temp += STEP)
    printFilaCelsius(temp);
}

void printFilasFahrenheit(const int LOWER,const int UPPER,const int STEP){
    for (int temp = LOWER; temp <= UPPER; temp += STEP)
    printFilaFahrenheit (temp);
}

void printFilaCelsius(int temp){
    printf ("%14d °C = %5.1f °F\n",temp,GetFahrFromCels (temp));
}

void printFilaFahrenheit(int temp){
    printf ("%14d °F = %5.1f °C \n",temp,GetCelsFromFahr (temp));
}

int casiIgual (double temp, double valor){
    if ((temp - valor) < 0.1 && (temp - valor) > -0.1 ) // se toma como valido un valor obtenido cuyo error con respecto al valor real sea menor al |0.1|
    return 1;    
    else 
    return 0;
    
}