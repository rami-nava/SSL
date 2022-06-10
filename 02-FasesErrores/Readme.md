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

    b) Se puede concluir a partir de esto que luego de preprocesar se obtienen los prototipos de stdio.h funciones (declaraciones) y estructuras.
       Ademas, saca los comentarios y los reemplaza por espacios. Al sacar el archivo preprocesado por un archivo en lugar de a traves de la 
       terminal agregando el ("-o"), se agiliza el proceso. A pesar de que prontf no es una funcion, no se detecta ningun error ya que el preprocesador
       no conoce de C. Solo tiene en cuenta comentarios e includes y defines.   

    c) Se escribe hello3.c (se agrega la declaracion de la funcion printf y se borra el comentario)

    d) La semantica en la primera linea: es una declaracion de una funcion que devuelve un int, espera por   lo menos 1 argumento ("..." = cantidad variable de argumentos). Al tener un puntero con const,
       quiere decir que no puede modificarse a lo que esta apuntando. Es un puntero de "solo lectura". Al incluir el restrict, quiere decir
       que solo este puntero apunta a ese objeto, ninguno mas (sirve para optimizar, no va a haber solapamiento, el compilador puede secuenciarlo en el orden que quiera).  
       
       No es parte de la semantica pero: "s" es una cadena formada por caracteres comunes y especificadores (como por ejemplo "%d"). String no existe en C. 

    e) Se obtiene hello3.i : Al no tener el include de stdio.h, no se incluyen los prototipos de funciones y estructuras en hello3.i
       
       Diferencias entre hello2.i y hello3.i: son casi iguales, no hay mucho para que haga el preprocesador en este caso.
                                              Principalmente, en el caso de hello2.i al tener el include de stdio.h trae los prototipos de funciones 
                                              y estructuras, en el caso de hello3.i no ocurre esto. 

       Diferencias entre hello3.c y hello3.i: En hello3.i se encuentra el mismo texto que en hello3.c pero ademas hay    unas lineas extras que contienen informacion para el compilador. Para que despues genere mejores diagnosticos.
                                              Si agregamos al final del comando (-p), estas primeras lineas con numerales no se imprimen,
                                              y hello3.i seria identico a hello3.c
------------------------------------------------------------------------------------------------------------------------------------------------------------------
2.  Compilacion

->Compilacion sin ensamblado
Comandos utilizados: gcc helloX.i -S -o helloX.s
Resultado: helloX.s

    a) Se quiere obtener hello3.s. Sin embargo, la compilacion devuelve un error y un warning y no puede crearse hello3.s:

warning: implicit declaration of function 'prontf'; did you mean 'printf'? [-Wimplicit-function-declaration]
    4 |  prontf("La respuesta es %d\n");
      |  ^~~~~~
      |  printf

hello3.c:4:2: error: expected declaration or statement at end of input

      Warning: Se debe a que la funcion prontf no esta declarada, y que probablemente se deba a un error de tipeo 
               al querer tipar printf que esta declarada en la primer linea. El compilador no lo detecta como un error.
      Error: Se debe a que la funcion main no tiene la llave de cerrado de la funcion ("}"). Es un error del tipo sintactico. 


    b) Se corrigen los errores, no los warnings de hello3.c y se obtiene hello4.c, luego se obtiene hello4.s Ahora, solamente hay warnings:

hello4.c:5:2: warning: implicit declaration of function 'prontf'; did you mean 'printf'? [-Wimplicit-function-declaration]
    5 |  prontf("La respuesta es %d\n"); //Sentencia
      |  ^~~~~~
      |  printf

    c) El codigo de hello4.s esta escrito en assembler. Se transforma el codigo C en lenguaje assembler que sea propio de nuestro procesador.
       El lenguaje assembler o ensamblador es un lenguaje de bajo nivel que representa las instrucciones basicas que debe ejectutar la computadora
       para ejecutar el programa original. 

       Principal: Hay declaraciones de nivel assembler al principio. Luego arranca main en la linea X, dura Y lineas. 
                  Se incluye informacion para el ensamblador al final. 
       Linea principal en assembler: Antes de esto prepara la pila. Luego mueve el valor 42 a un registro.  Llama a prontf. y se mueve el puntero de funciones a 0??? 
      Son instrucciones para el microprocesador en caracteres ASCII?


No se puede compilar si aun hay errores presentes en el codigo. Si hay warnings puede que si se pueda compilar como en este caso.

->Compilacion con ensamblado pero sin vinculacion 
Comandos utilizados: gcc helloX.s -c -o helloX.o
Resultado: helloX.o

    d) Se obtiene hello4.o, sin ningun error ni warnings. Esto es asi, ya que en este paso no estamos ni preprocesando ni compilando, solo estamos
       ensamblando, es decir, se esta traduciendo el codigo desde lenguaje assembler a codigo de maquina. Por lo tanto, la etapa en la que el compilador o el preprocesador detectan errores y warnings ya se paso. Se traduce el archivo.s y se pasa a codigo objeto que esta escrito en lenguaje de maquina.

       No tienen representacion con sentido en caracteres ASCII. Hay maneras de visualizarlos, que permiten ver los bytes y las direcciones. 
       Cada byte es una instruccion para el microprocesador. 
       Instrucciones como numeros en lugar de palabras (como assembler)

------------------------------------------------------------------------------------------------------------------------------------------------------------------
3. Vinculacion 

Comandos utilizados: gcc helloX.o -o helloX
Resultados: helloX

    a) Al vincular hello4.o con la biblioteca standar, hay un problema que no permite obtener el archivo ejecutable:

Undefined symbols for architecture arm64:
  "_prontf", referenced from:
      _main in hello4.o
ld: symbol(s) not found for architecture arm64
collect2: error: ld returned 1 exit status

    No se puede vincular hello4.o. Esto se debe a que prontf no se encuentra declarada ni definida en la biblioteca standar ni en el codigo fuente. Por lo tanto,
    no se puede obtener el archivo ejecutable de hello4.c 

    b) Se corrige hello4.c (cambiando el prontf por un printf) y se obtiene hello5.c y se vincula con la biblioteca standar para obtener hello5 (ejecutable)

       hello5.o o hello5.c vincula => gcc hello5.c -o hello5 // gcc hello5.o -c -o hello5

Ejecutar
Comandos utilizados: ./helloX
    c) Se ejecuta hello5
       Se obtiene: "La respuesta es 1868281184"
       Este es un error pragmatico, ya que el codigo es ejecutable y no se recibe ningun tipo de error por parte del compilador. Esto se debe a que el error pragmatico, 
       no es un error en cuanto a la escritura del codigo, sino que se debe a su funcionamiento. hello5.c deberia devolver el string: "La respuesta es 42", sin embargo 
       esto no ocurre pero para el compilador esto no representa ningun tipo de error ya que este no sabe que espera printf osea no sabe que uso tiene q darle a esta 
       funcion. Printf no es parte del lenguaje es parte de la biblioteca standar.

       La causa del error, radica en el printf, donde no se hace referencia al valor que se desea imprimir (aquel guardado en la variable i). Al no respetarse el contrato
       de la funcion printf, se imprime un valor cualquiera, por lo tanto, no se obtiene el valor esperado => Falla la funcion principal del programa.

       En conclusion: Al no respetarse el contrato de printf, printf hace lo que quiere. 

------------------------------------------------------------------------------------------------------------------------------------------------------------------
4. Correccion de Bug

    BUG: cuando ocurre un comportamiento distinto del esperado (justo como ocurrio en hello5)

    a) Se escribe hello6.c y se verifica que funcione

    Resultado: "La respuesta es 42"

    En este caso, la respuesta del programa es esperada, porque estamos diciendole que imprima el valor que previamente guardamos en la variable i, el cual es 42.
------------------------------------------------------------------------------------------------------------------------------------------------------------------
5. Remocion de Prototipo

    a) Se escribe hello7.c 
       Resultado: "La respuesta es 42"

    b) Deberia compilar => ya que la definicion de printf esta en la biblioteca, al no haber declaracion habra un warning pero compilara.
       Al ejecutar los comandos, se reciben warnings como en casos anteriores pero compila y ejecuta:

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


       Uno de los warnings (el segundo), hace referencia a que deberia incluirse la libreria stdio.h o una declaracion de esta funcion en el codigo, para utilizarla, sin embargo, printf es un caso especial, ya que al ser tan utilizada, viene incorporada al compilador (propio de gcc y otros compiladores), por lo tanto, es un warning y no un error. 

       Ademas, el primer warning esta avisando que hay una declaracion implicita de printf => ante no haber una declaracion, el compilador asume su declaracion en base al primer uso de dicha funcion (entonces en este caso, asume que printf devuelve una cadena y un int). => CARACTERISTICA PROPIA DE C

       Por ultimo, el tercer warning, comenta que a parte de ser una declaracion implicita, es incompatible con la declaracion que ya se encuentra en el compilador.

       Ademas, funciona porque cumple con todas las correcciones que se realizaron sobre las variantes del codigo anteriores. La funcion main esta encerrada por ambas llaves, 
       se usa printf y no prontf y se incluye la variabel i (con el valor que se desea imprimir) en printf.

       En conclusion, el programa funciona, a pesar de utilizar declaraciones implicitas, sin embargo, aunque no haga falta declararlas previamente para utilizarlas en C, es una buena practica para evitar potenciales errores al utilizarlas.
------------------------------------------------------------------------------------------------------------------------------------------------------------------
6. Compilacion Separada: Contratos y Modulos




REMOCION DEL PROTOTIPO

ES BUENO? es muy general pero sirve para no tener tantos problemas 

EN CUANTO AL LENGUAJE C: hace falta declaracion antes de llamar a una funcion? => no hace falta pero es buena practica => 
