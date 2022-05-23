#include <stdio.h>
#include "Conversion.h"

void printTablas (const int,const int,const int);
void printTablaCelsius (const int,const int,const int);
void printTablaFahrenheit (const int,const int,const int);
void printFilasCelsius(const int,const int,const int);
void printFilasFahrenheit(const int,const int,const int);
void printFilaCelsius (int);
void printFilaFahrenheit (int);

int main (void){
    const int LOWER = 0;
    const int UPPER = 300;
    const int STEP = 20;    

    printTablas (LOWER,UPPER,STEP);
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