Tareas: 

1) Funcionalidades y opciones del compilador para limitar el inicio y fin de las fases de traduccion

A partir del comando "gcc --help" en la terminal,vemos que algunas de las funcionalidades son:

-> Preprocesar unicamente, sin compilar o ensamblar o vincular -> -E

-> Compilar sin ensamblar o vincular -> -S

-> Compilar y ensamblar, sin vincular -> -c

Esto es muy util para poder comprender que se realiza en cada etapa de traduccion sobre el programa que se quiere compilar
desde que se comienza hasta que finaliza dicho proceso. 


2) 7.3.1 Secuencia de pasos:

------------------------------------------------------------------------------------------------------------------------------
1. Preprocesador

->Preprocesar sin compilar

Comandos utilizados: gcc helloX.c -E -o helloX.i

Resultado: helloX.i

  a) Se escribe hello2.c y se obtiene hello2.i

  b) Se puede concluir a partir de esto que luego de preprocesar se obtienen los prototipos de stdio.h 
     funciones (declaraciones) y estructuras. Ademas, saca los comentarios y los reemplaza por espacios. 
     Al sacar el archivo preprocesado por un archivo en lugar de a traves de la terminal agregando el ("-o"), 
     se agiliza el proceso. A pesar de que prontf no es una funcion que se encuentre declarada o definida, 
     no se detecta ningun error ya que el preprocesador no conoce de C. Solo tiene en cuenta comentarios e 
     includes y defines.   

  c) Se escribe hello3.c (se agrega la declaracion de la funcion printf y se borra el comentario)

  d) La semantica en la primera linea: es una declaracion de una funcion que devuelve un int, espera por lo menos 1 
     argumento ("..." = cantidad variable de argumentos). Al tener un puntero con const, quiere decir que no puede 
     modificarse a lo que esta apuntando. Es un puntero de "solo lectura". Al incluir el restrict, quiere decir que 
     solo este puntero apunta a ese objeto, ninguno mas (sirve para optimizar, no va a haber solapamiento, el compilador 
     puede secuenciarlo en el orden que quiera).  
       
No es parte de la semantica pero: "s" es una cadena formada por caracteres comunes y especificadores 
(como por ejemplo "%d"). String no existe en C. 

  e) Se obtiene hello3.i : Al no tener el include de stdio.h, no se incluyen los prototipos de funciones y 
     estructuras en hello3.i

    Diferencias entre hello2.i y hello3.i: son casi iguales, no hay mucho para que haga el preprocesador en este caso.
                                           Principalmente, en el caso de hello2.i al tener el include de stdio.h trae los 
                                           prototipos de funciones y estructuras, en el caso de hello3.i no ocurre esto. 

    Diferencias entre hello3.c y hello3.i: En hello3.i se encuentra el mismo texto que en hello3.c pero ademas hay unas 
                                           lineas extras que contienen informacion para el compilado para que despues 
                                           genere mejores diagnosticos. Si agregamos al final del comando (-p), estas 
                                           primeras lineas con numerales no se imprimen, y hello3.i seria identico a hello3.c
                                           
------------------------------------------------------------------------------------------------------------------------------
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
             al querer tipar printf que esta declarada en la primer linea. El compilador no lo detecta como un error ya que
             es posible el uso de declaraciones implictas en C.
             
   Error: Se debe a que la funcion main no tiene la llave de cerrado de la funcion ("}"). Es un error del tipo sintactico. 


  b) Se corrigen los errores, no los warnings de hello3.c y se obtiene hello4.c, luego se obtiene hello4.s 
     Ahora, solamente hay warnings:

    hello4.c:5:2: warning: implicit declaration of function 'prontf'; did you mean 'printf'? [-Wimplicit-function-declaration]
        5 |  prontf("La respuesta es %d\n"); //Sentencia
          |  ^~~~~~      
          |  printf

  c) El codigo de hello4.s esta escrito en assembler. Se transforma el codigo C en lenguaje assembler que sea propio
     de nuestro procesador. El lenguaje assembler o ensamblador es un lenguaje de bajo nivel que representa las 
     instrucciones basicas que debe ejectutar la computadora para ejecutar el programa original. 

En este codigo, hay declaraciones de nivel assembler al principio. Luego arranca main en la linea 10 y se detallan los pasos
para preparar y ejecutar dicha funcion. Luego, al final, se incluye informacion para el ensamblador.

En conclusion, este archivo contiene instrucciones para "nuestro" procesador en caracteres ASCII, como por ejemplo,
mover el valor 42 a un determinado registro, preparar la pila, llamar a prontf y mover el puntero de funciones.
No se puede compilar si aun hay errores presentes en el codigo. Si hay warnings puede que si se pueda compilar como en 
este caso.

->Compilacion con ensamblado pero sin vinculacion 

Comandos utilizados: gcc helloX.s -c -o helloX.o

Resultado: helloX.o

  d) Se obtiene hello4.o, sin ningun error ni warnings. Esto es asi, ya que en este paso no estamos ni preprocesando ni 
     compilando, solo estamos ensamblando, es decir, se esta traduciendo el codigo desde lenguaje assembler a codigo de 
     maquina. Por lo tanto, la etapa en la que el compilador o el preprocesador detectan errores y warnings ya se paso. 
  
No tienen representacion con sentido en caracteres ASCII. Hay maneras de visualizarlos, que permiten ver los bytes y 
las direcciones. 

Cada byte es una instruccion para el microprocesador. 

Instrucciones se encuentran como numeros (opcodes) en lugar de palabras (como seria assembler)

------------------------------------------------------------------------------------------------------------------------------
3. Vinculacion 

->Vincular

Comandos utilizados: gcc helloX.o -o helloX

Resultados: helloX

  a) Al vincular hello4.o con la biblioteca standar, hay un problema que no permite obtener el archivo ejecutable:

    Undefined symbols for architecture arm64:
      "_prontf", referenced from:
          _main in hello4.o
    ld: symbol(s) not found for architecture arm64
    collect2: error: ld returned 1 exit status

No se puede vincular hello4.o. Esto se debe a que prontf no se encuentra declarada ni definida en la biblioteca 
standar ni en el codigo fuente. Por lo tanto, no se puede obtener el archivo ejecutable de hello4.c 

En conclusion: el uso de funciones declaradas implicitamente no es una buena practica. Ya que es posible preprocesar,
compilar y ensamblar el codigo, pero si al vincular el archivo, no se posee una declaracion para dicha funcion, no es posible 
crear el ejecutable. Esto podria evitarse vinculandolo con otro archivo en el cual se posea una declaracion para dicha funcion. 

  b) Se corrige hello4.c (cambiando el prontf por un printf) y se obtiene hello5.c y se vincula con la biblioteca standar 
     para obtener hello5 (ejecutable)

hello5.o o hello5.c vincula => gcc hello5.c -o hello5 // gcc hello5.o -c -o hello5

->Ejecutar

Comandos utilizados: ./helloX

  c) Se ejecuta hello5
     Se obtiene: "La respuesta es 1868281184"
     
  Este es un error pragmatico, ya que el codigo es ejecutable y no se recibe ningun tipo de error por parte del compilador. 
  Esto se debe a que el error pragmatico, no es un error en cuanto a la escritura del codigo, sino que se debe a su 
  funcionamiento. hello5.c deberia devolver el string: "La respuesta es 42", sin embargo esto no ocurre pero para el 
  compilador esto no representa ningun tipo de error ya que este no sabe que espera printf osea no sabe que uso tiene 
  que darle a esta funcion. Printf no es parte del lenguaje es parte de la biblioteca standar.

La causa del error, radica en el printf, donde no se hace referencia al valor que se desea imprimir (aquel guardado 
en la variable i). Al no respetarse el contratode la funcion printf, se imprime un valor cualquiera, por lo tanto, 
no se obtiene el valor esperado => Falla la funcion principal del programa.

En conclusion: Al no respetarse el contrato de printf, printf hace lo que quiere. 

------------------------------------------------------------------------------------------------------------------------------
4. Correccion de Bug

  BUG: cuando ocurre un comportamiento distinto del esperado (justo como ocurrio en hello5)

  a) Se escribe hello6.c y se verifica que funcione

     Resultado: "La respuesta es 42"

  En este caso, la respuesta del programa es esperada, porque estamos diciendole que imprima el valor que previamente 
  guardamos en la variable i, el cual es 42.
  
------------------------------------------------------------------------------------------------------------------------------
5. Remocion de Prototipo

  a) Se escribe hello7.c 
  
     Resultado: "La respuesta es 42"

  b) Deberia compilar => ya que la definicion de printf esta en la biblioteca, al no haber declaracion habra un 
     warning pero compilara. 
     
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


Uno de los warnings (el segundo), hace referencia a que deberia incluirse la libreria stdio.h o una declaracion de esta
funcion en el codigo, para utilizarla, sin embargo, printf es un caso especial, ya que al ser tan utilizada, viene 
incorporada al compilador (propio de gcc y otros compiladores), por lo tanto, es un warning y no un error. 

Ademas, el primer warning esta avisando que hay una declaracion implicita de printf => ante no haber una declaracion, 
el compilador asume su declaracion en base al primer uso de dicha funcion (entonces en este caso, asume que printf 
devuelve una cadena y un int). => CARACTERISTICA PROPIA DE C

Por ultimo, el tercer warning, comenta que a parte de ser una declaracion implicita, es incompatible con la declaracion 
que ya se encuentra en el compilador.

Ademas, funciona porque cumple con todas las correcciones que se realizaron sobre las variantes del codigo anteriores. 
La funcion main esta encerrada por ambas llaves, se usa printf y no prontf y se incluye la variable i (con el valor que 
se desea imprimir) en printf.

En conclusion, el programa funciona, a pesar de utilizar declaraciones implicitas, sin embargo, aunque no haga falta para
algunas funciones como printf (que ya vienen incuidas en el compilador), declararlas previamente para utilizarlas en C, 
es una buena practica para evitar potenciales errores al utilizar esta practica para otras funciones.

------------------------------------------------------------------------------------------------------------------------------
6. Compilacion Separada: Contratos y Modulos

funcion wrapper: en este caso existe una declaracion y una definicion de la funcin prontf. Esta es una funcion wrapper,
                 su unica funcion es llamar a la ya existente funcion printf y ejecutarla con los mismos parametros.

  a) Se escriben studio1.c y hello8.c

  b) Se genera el ejecutable a partir de las 2 unidades de traduccion utilizando el siguiente comando:
  
  gcc hello8.c studio1.c -o hello8
     
  Se obtiene como resultado el archivo ejecutable: hello8

  Hay varios warnings al hacer esto:

    hello8.c: In function 'main':

    hello8.c:3:2: warning: implicit declaration of function 'prontf' [-Wimplicit-function-declaration]
       3 |  prontf("La respuesta es %d\n", i);
         |  ^~~~~~

    studio1.c: In function 'prontf':

    studio1.c:2:2: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
       2 |  printf("La respuesta es %d\n", i);
         |  ^~~~~~

    studio1.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
     +++ |+#include <stdio.h>
       1 | void prontf(const char* s, int i){

    studio1.c:2:2: warning: incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
       2 |  printf("La respuesta es %d\n", i);
         |  ^~~~~~

    studio1.c:2:2: note: include '<stdio.h>' or provide a declaration of 'printf'


   Como se puede ver, hay varios warnings, la mayoria en studio.c. Sin embargo, hay un warning con respecto a hello8.c,
   este esta diciendo que como ocurrio en hello7.c, se esta declarando una funcion de manera implicita, en este caso,
   dicha funcion es prontf. 
     
   Ademas, en studio1.c, esto tambien ocurre, ya que no se incluye declaracion para la funcion printf. Por lo tanto, 
   en otro warning, el compilador recomienda incluir la biblioteca estandar mediante "include <stdio.h>" o declararla
   en el mismo codigo. Y al igual que en hello7.c, el compilador esta informando que el uso que se le esta dando a
   printf, no es compatible con el que ya viene incluido en el compilador.

   Sin embargo, a pesar de la presencia de todos estos warnings, no se evita que se logre crear el ejecutable y 
   mismo ejecutarlo. Esto se debe a que los warnings surgen en el proceso de compilacion y ensamblado. A pesar de esto, 
   es posible crear el ejecutable ya que al vincular se utilizan 2 archivos, el archivo objeto de hello8.c y studio1.c. 
   Es en este ultimo donde se encuentra la definicion de la funcion prontf. En el caso de printf, no se obtiene una 
   declaracion ni definicion, pero como se menciono previamente, esta funcion es un caso especial que ya viene incluida 
   en el compilador. Finalmente, se obtiene la respuesta esperada:

     "La respuesta es 42"
     
   A diferencia de como ocurrio con hello4, en este caso al vincular el archivo hello8.o con studio1.o es posible crear el ejecutable. 

  c) Se crea el archivo hello8Parametros.c que invoca a la funcion prontf con menos o mas parametros que con los que se la declaro.
     En este caso, no se le incluye en la invocacion, el parametro i. 

   Al crear el ejecutable: gcc hello8Parametros.c studio1.c -o hello8

   Se obtienen los siguientes warnings:


    hello8Parametros.c: In function 'main':

    hello8Parametros.c:3:2: warning: implicit declaration of function 'prontf' [-Wimplicit-function-declaration]
       3 |  prontf("La respuesta es %d\n");
         |  ^~~~~~

    studio1.c: In function 'prontf':

    studio1.c:2:2: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
       2 |  printf("La respuesta es %d\n", i);
         |  ^~~~~~

    studio1.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
     +++ |+#include <stdio.h>
       1 | void prontf(const char* s, int i){

    studio1.c:2:2: warning: incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
       2 |  printf("La respuesta es %d\n", i);
         |  ^~~~~~

    studio1.c:2:2: note: include '<stdio.h>' or provide a declaration of 'printf'

   Se obtienen los mismos warnings que en el caso anterior. 

   Se logra crear el ejecutable, y al ejecutarlo se obtiene:

     "La respuesta es 1842165120"

   No se esta respetando el contrato con prontf, por lo tanto, tampoco se va a respetar el contrato con printf (ya que 
   prontf no recibio el parametro i, tampoco va a poder pasarselo a printf). Entonces, printf hace lo que quiere y 
   devuelve cualquier cosa. 

   Es mas, si no le incluimos ningun parametro a la invocacion de prontf, aun asi se logra crear el ejecutable y hello8  
   devuelve:

   "La respuesta es 1806235008", esto se debe a que en printf, la cadena de chars en "la respuesta es " no es un parametro. 

   Si agregamos parametros de mas, tampoco genera ningun problema. 

   En conclusion: sin importar que parametros utilizemos en la invocacion, se logra crear el ejecutable, pero la respuesta
   puede no ser la esperada. 

  d)

   i) Se escribe el contrato studio.h
    
   ii) Se escribe hello99.c (Se utiilzo de nombre hello99.c en lugar de hello9.c, ya que hello9.c en visual studio code, 
        me lo tomaba como un archivo de C++ y me daba error al usar printf).

   iii) Se escribe studio2.c

   iv) Mediante el comando: gcc hello99.c studio2.c -o hello99.
 
 Se obtiene el ejecutable hello99 sin ningun warning o error.
  
 Al ejecutarlo se obtiene la respuesta esperada: 
              
         "La respuesta es 42" .

 Se crea el ejecutable de hello99.c y no se recibe ningun warning ni ningun error. Esto se debe a que a diferencia 
 del caso anterior en el que en hello8.c no se incluia una declaracion para prontf, en hello99.c, esto no ocurre. 
 Prontf esta declarada en studio.h, y esta biblioteca se esta incluyendo en hello99.c mediante un include. Ademas,
 en studio2.c a diferencia de en studio1.c, printf no esta declarada implicitamente, sino que se encuentra declarada 
 en la biblioteca standar y esta se encuentra incluida en el codigo. 

 En conclusion: Al incluir contratos en el cliente (hello99.c) y en el proveedor (studio2.c), se evitan los warnings 
 relacionados a falta de declaraciones (osea al uso de declaraciones implicitas), que no "rompian" el codigo, pero 
 que podian llegar a causar problemas. Es decir, a pesar de no haber declarado las funciones en los respectivos codigos, 
 al inlcuir las biblitecas correspiendentesen donde ya si se encuentran declaradas, el compilador sabe que formate debe 
 tener cada funcion y cuantos y de que tipo deben ser los parametros que reciba. 
 
------------------------------------------------------------------------------------------------------------------------------
