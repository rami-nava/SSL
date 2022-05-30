#TP 1: Interaces y Makefile

#Integrantes: Ramiro Navarro (github: rami-nava, Legajo: 1762540)

#Consigna:
    • Desarrollar un programa que imprima dos tablas de conversión, una de Fahrenheit a Celsius y otra de Celsius a Fahrenheit.

#Objetivos: 

    • Aplicar el uso de interfaces y módulos.

    • Construir un programa formado por más de una unidad de traducción.

    • Comprender el proceso de traducción o Build cuando intervienen varios archivos fuente.

    • Aplicar el uso de Makefile.

#Compilador:

    • Version de compilador utilizada: gcc 11.2.0

    • Standar de C utilizado: c18 (aclarado en el makefile)

    • Se compilo mediante makefile:
         • Comandos a ejecutar:
             • make : para crear y correr el ejecutable de TablasDeConversion (para ejecutarTablasDeConversion2 deberia modificarse el makefile o hacerlo desde la terminal)
             • make clean : para borrar los archivos creados para dicha tarea
             • make test : para crear y correr el ejecutable que se encarga de realizar las pruebas (ConversionTest)
             • make cleanTest : para borrar los archuvis creados para dicha tarea

#Aclaraciones: 

    • TablasDeConversion2.c esta hecho con funciones del estilo printTablas, printFilas, entre otras. 
    Se utilizaron distintas funciones de printFilas o printFila para la tabla de celsius a fahrenheit 
    y para la de fahrenheit a celsius debido a inconvenientes con pasar funciones como argumentos a otras funciones.

    • TablasDeConversion.c es el archivo original, el cual no llama a funciones del estilo printFilas o printTablas.  

    • Para los tests, se tomo como error aceptable, aquel menor a 0,1. 



