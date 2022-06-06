Tareas: 

1) Funcionalidades y opciones del compilador para limitar el inicio y fin de las fases de traduccion

A partir del comando "gcc --help" en la terminal,vemos que algunas de las funcionalidades son:
-> Preprocesar unicamente, sin compilar o ensamblar o vincular -> -E
-> Compilar sin ensamblar o vincular -> -S
-> Compilar y ensamblar, sin vincular -> -c
Esto es muy util para poder comprender que se realiza en cada etapa de traduccion sobre el programa que se quiere compilar
desde que se comienza hasta que finaliza dicho proceso. 


2) 7.3.1 Secuencia de pasos:

------------------------------------------------------------------------------------------------------------------------------------------------------------------
1. Preprocesador

->Preprocesar sin compilar
Comandos utilizados: gcc helloX.c -E -o helloX.i
Resultado: helloX.i

    a) Se escribe hello2.c y se obtiene hello2.i

    b) Se puede concluir a partir de esto que luego de preprocesar se obtienen los prototipos de stdio.h funciones y estructuras.
       Ademas, saca los comentarios y los reemplaza por espacios. Al sacar el archivo preprocesado por un archivo en lugar de a traves de la 
       terminal agregando el ("-o"), se agiliza el proceso. A pesar de que prontf no es una funcion, no se detecta ningun error ya que el preprocesador
       no conoce de C. Solo tiene en cuenta comentarios e includes y defines.   

    c) Se escribe hello3.c

    d) La semantica en la primera linea: es una declaracion de una funcion que devuelve un int, espera por lo menos 1 argumento. Al tener un puntero con const,
       quiere decir que no puede modificarse a lo que esta apuntando. Es un puntero de "solo lectura". Al incluir el restrict, quiere decir
       que solo este puntero apunta a "x", ninguno mas (sirve para optimizar).
       
    e) Se obtiene hello3.i : Al no tener el include de stdio.h, no se incluyen los prototipos de funciones y estructuras en hello3.i
       
       Diferencias entre hello2.i y hello3.i: son casi iguales, no hay mucho para que haga el preprocesador en este caso.
                                              Principalmente, en el caso de hello2.i al tener el include de stdio.h trae los prototipos de funciones 
                                              y estructuras, en el caso de hello3.i no ocurre esto. 
       
       Diferencias entre hello3.c y hello3.i: En hello3.i se encuentra el mismo texto que en hello3.c pero ademas hay...............
                                              Si agregamos al final del comando (-p), las primeras lineas con numerales no se imprimen,
                                              y hello3.i seria identico a hello3.c
------------------------------------------------------------------------------------------------------------------------------------------------------------------
2.  Compilacion

->Compilacion sin ensamblado
Comandos utilizados: gcc helloX.i -S -o helloX.s
Resultado: helloX.s

    a) Se obtiene hello3.s. Ademas la compilacion devuelve un error y un warning:

warning: implicit declaration of function 'prontf'; did you mean 'printf'? [-Wimplicit-function-declaration]
    4 |  prontf("La respuesta es %d\n");
      |  ^~~~~~
      |  printf

hello3.c:4:2: error: expected declaration or statement at end of input

      Warning: Se debe a que la funcion prontf no esta declarada, y que probablemente se deba a un error de tipeo 
               al querer tipar printf que esta declarada en stdio.h
      Error: Se debe a que la funcion main no tiene la llave de cerrado de la funcion ("}")


    b) Se corrigen los errores, no los warnings de hello3.c y se obtiene hello4.c, luego se obtiene hello4.s Ahora, solamente hay warnings:

hello4.c:5:2: warning: implicit declaration of function 'prontf'; did you mean 'printf'? [-Wimplicit-function-declaration]
    5 |  prontf("La respuesta es %d\n"); //Sentencia
      |  ^~~~~~
      |  printf

    c) El codigo de hello4.s esta escrito en assembler. Se transforma el codigo C en lenguaje assemblera que sea propio de nuestro procesador.
       El lenguaje assembler o ensamblador es un lenguaje de bajo nivel que representa las instrucciones basicas que debe ejectutar la computadora
       para ejecutar el programa original. 

->Compilacion con ensamblado pero sin vinculacion 
Comandos utilizados: gcc helloX.s -c -o helloX.o
Resultado: helloX.o

    d) Se obtiene hello4.o, sin ningun error ni warnings. Esto es asi, ya que en este paso no estamos ni preprocesando ni compilando, solo estamos
       ensamblando, es decir, se esta traduciendo el codigo desde lenguaje assembler a codigo de maquina. Por lo tanto, la etapa en la que el compilador o el preprocesador detectan errores y warnings ya se paso. Se traduce el archivo.s y se pasa a codigo objeto que esta escrito en lenguaje de maquina.
------------------------------------------------------------------------------------------------------------------------------------------------------------------
3. Vinculacion 

Comandos utilizados: gcc helloX.o -o helloX
Resultados: helloX

    a) Para vincular hello4.o con la biblioteca standar, se hace automaticamente por parte de la computadora. Sin embargo, hay un error en hello4.o:

Undefined symbols for architecture arm64:
  "_prontf", referenced from:
      _main in hello4.o
ld: symbol(s) not found for architecture arm64
collect2: error: ld returned 1 exit status

    Se debe a que prontf no se encuentra declarada ni definida en la biblioteca standar. 

    b) Se corrige hello4.c (cambiando el prontf por un printf) y se obtiene hello5.c y se vincula con la biblioteca standar para obtener hello5

Ejecutar
Comandos utilizados: ./helloX
    c) Se ejecuta hello5
       Se obtiene: "La respuesta es 1868281184"
       No se obtiene el valor esprado, ya que en el printf no se hace referencia al valor que se desea imprimir (aquel guardado en la variable i). Se imprime
       un valor "basura" que estaba en memoria.

------------------------------------------------------------------------------------------------------------------------------------------------------------------
4. Correccion de Bug

    a) Se escribe hello6.c y se verifica que funcione

    Resultado: "La respuesta es 42"
------------------------------------------------------------------------------------------------------------------------------------------------------------------
5. Remocion de Prototipo

    a) Se escribe hello7.c 
       Resultado: "La respuesta es 42"

    b) A pesar de poseer warnings como en casos anteriores (por no incluir a stdio.h, esto no afecta la ejecucion ya que estas se ecuentran pre incluidas en la computadora)
hello7.c: In function 'main':
hello7.c:3:5: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
    3 |     printf("La respuesta es %d\n", i);
      |     ^~~~~~
hello7.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
  +++ |+#include <stdio.h>
    1 | int main(void){
hello7.c:3:5: warning: incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
    3 |     printf("La respuesta es %d\n", i);
      |     ^~~~~~
hello7.c:3:5: note: include '<stdio.h>' or provide a declaration of 'printf'

       Ademas, funciona porque cumple con todas las correcciones que se realizaron sobre las variantes del codigo anteriores. La funcion main esta encerrada por ambas llaves, 
       se usa printf y no prontf y se incluye la variabel i (con el valor que se desea imprimir) en printf.
------------------------------------------------------------------------------------------------------------------------------------------------------------------
6. Compilacion Separada: Contratos y Modulos
