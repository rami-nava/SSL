#TP 1: Interaces y Makefile

#Integrantes: 
    • Ramiro Navarro

#Objetivos: 
    • Aplicar el uso de interfaces y módulos.
    • Construir un programa formado por más de una unidad de traducción.
    • Comprender el proceso de traducción o Build cuando intervienen varios archivos fuente.
    • Aplicar el uso de Makefile.

#Aclaraciones: 
    • TablasDeConversion.c esta hecho con funciones del estilo printTablas, printFilas, entre otras. Se utilizaron distintas funciones para la tabla de celsius a fahrenheit y para la de fahrenheit a celsius debido a inconvenientes con pasar funciones como argumentos a otras funciones.
    • TablasDeConversion2.c es el archivo original, el cual no llama a funciones del estilo printFilas o printTablas. 
    • Las funciones del estilo de printFilas y  printTablas estan definidas en Conversion.c.
    • El makefile esta escrito para ejecutar el archivo TablasDeConversion.c.