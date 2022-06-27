Compilador Utilizado:

gcc (Homebrew GCC 11.2.0_3) 11.2.0

Tareas: 

1) Funcionalidades y opciones del compilador para limitar el inicio y fin de las fases de traduccion

A partir del comando "gcc --help" en la terminal,vemos que algunas de las funcionalidades son:

-> Preprocesar unicamente, sin compilar o ensamblar o vincular -> -E

-> Compilar sin ensamblar o vincular -> -S

-> Compilar y ensamblar, sin vincular -> -c

Esto es muy util para poder comprender que se realiza en cada etapa de traduccion sobre el programa que se quiere compilar
desde que se comienza hasta que finaliza dicho proceso. 

------------------------------------------------------------------------------------------------------------------------------

2) 7.3.1 Secuencia de pasos:

1. Preprocesador

->Preprocesar sin compilar

Comandos utilizados: gcc helloX.c -E -o helloX.i

Resultado: helloX.i

  a) Se escribe hello2.c y se obtiene hello2.i

  b) Se puede concluir a partir de esto que luego de preprocesar se obtienen los prototipos de stdio.h de
     funciones (sus declaraciones) y estructuras. Ademas, saca los comentarios y los reemplaza por espacios. 
     Al sacar el archivo preprocesado por un archivo en lugar de a traves de la terminal agregando el ("-o"), 
     se agiliza el proceso. A pesar de que prontf no es una funcion que se encuentre declarada o definida, 
     no se detecta ningun error ya que el preprocesador no conoce de C. Solo tiene en cuenta comentarios,
     includes y defines.   

  c) Se escribe hello3.c (se agrega la declaracion de la funcion printf y se borra el comentario).

  d) En cuanto a la semantica de la primera linea, es una declaracion de una funcion que devuelve un int y espera 
     por lo menos 1 argumento ("..." = cantidad variable de argumentos). Al tener un puntero con const, quiere 
     decir que no puede modificarse a lo que esta apuntando. Es un puntero de "solo lectura". Al incluir el restrict, 
     quiere decir que solo este puntero apunta a ese objeto, ninguno mas (sirve para optimizar, no va a haber solapamiento).  
       
No es parte de la semantica pero: "s" es una cadena formada por caracteres comunes y especificadores 
(como por ejemplo "%d"). String no existe en C. 

  e) Se obtiene hello3.i : Al no tener el include de stdio.h, no se incluyen los prototipos de funciones y 
     estructuras en hello3.i

    Diferencias entre hello2.i y hello3.i: son casi iguales, no hay mucho para que haga el preprocesador en este caso.
                                           Principalmente, en el caso de hello2.i al tener el include de stdio.h trae los 
                                           prototipos de funciones y estructuras, en el caso de hello3.i no ocurre esto. 

    Diferencias entre hello3.c y hello3.i: En hello3.i se encuentra el mismo texto que en hello3.c pero ademas hay unas 
                                           lineas extras que contienen informacion para el compilador para que despues 
                                           genere mejores diagnosticos. Si agregamos al final del comando (-p), estas 
                                           primeras lineas con numerales no se imprimen, y hello3.i seria identico a hello3.c

------------------------------------------------------------------------------------------------------------------------------
2. Compilacion

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
             es posible el uso de declaraciones implictas al compilar con GCC, o obtener las definiciones de las funciones 
             en otros archivos que luego se vinculen.

   Error: Se debe a que la funcion main no tiene la llave de cerrado de la funcion ("}"). Es un error del tipo sintactico que 
          detiene la compilacion.

  b) Se corrigen los errores, no los warnings de hello3.c y se obtiene hello4.c, luego se obtiene hello4.s 

     Ahora, solamente hay warnings:

    hello4.c:5:2: warning: implicit declaration of function 'prontf'; did you mean 'printf'? [-Wimplicit-function-declaration]
        5 |  prontf("La respuesta es %d\n"); //Sentencia
          |  ^~~~~~      
          |  printf

  c) El codigo de hello4.s esta escrito en assembler. Se transforma el codigo C en lenguaje assembler que sea propio
     de nuestro procesador. El lenguaje assembler o ensamblador es un lenguaje de bajo nivel que representa las 
     instrucciones basicas que debe ejecutar la computadora para correr el programa original. 

En este codigo, hay declaraciones de nivel assembler al principio. Luego arranca main en la linea 10 y se detallan los pasos
para preparar y ejecutar dicha funcion. Luego, al final, se incluye informacion para el ensamblador.

En conclusion, este archivo contiene instrucciones para "nuestro" procesador , como por ejemplo,
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

Las instrucciones se encuentran como numeros (opcodes) en lugar de palabras (como seria assembler)

------------------------------------------------------------------------------------------------------------------------------
3. Vinculacion 

->Vincular

Comandos utilizados: gcc helloX.o -o helloX

Resultados: helloX (archivo ejecutable)

  a) Al vincular hello4.o con la biblioteca standar, hay un problema que no permite obtener el archivo ejecutable:

    Undefined symbols for architecture arm64:
      "_prontf", referenced from:
          _main in hello4.o
    ld: symbol(s) not found for architecture arm64
    collect2: error: ld returned 1 exit status

No se puede vincular hello4.o. Esto se debe a que prontf no se encuentra declarada ni definida en la biblioteca 
standar ni en el codigo fuente. Por lo tanto, no se puede obtener el archivo ejecutable de hello4.c ya que cuando el linker
haga un llamado a la funcion prontf, no existe la definicion de la misma. 

En conclusion: el uso de funciones declaradas implicitamente no es una buena practica. Ya que es posible preprocesar,
compilar y ensamblar el codigo, pero si al vincular el archivo, no se posee una definicion para dicha funcion, no es posible 
crear el ejecutable. Esto podria evitarse vinculandolo con otro archivo en el cual se posea una definicion para dicha funcion. 

  b) Se corrige hello4.c (cambiando el prontf por un printf) y se obtiene hello5.c y se vincula con la biblioteca standar 
     para obtener hello5 (ejecutable)

hello5.o o hello5.c puede crearse el ejecutable mediante estos 2 archivos => gcc hello5.c -o hello5 // gcc hello5.o -c -o hello5

Esto es asi ya que la definicion de printf se encuentra en la biblioteca standar.

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
en la variable i). Al no respetarse el contrato de la funcion printf (se incluye un especificador que espera un entero para 
reemplazar, pero no lo recibe) se imprime un valor cualquiera, por lo tanto, no se obtiene el valor esperado => Falla la 
funcion principal del programa.

En conclusion: Al no respetarse el contrato de printf, printf hace lo que quiere. 

------------------------------------------------------------------------------------------------------------------------------
4. Correccion de Bug

  BUG: cuando ocurre un comportamiento distinto del esperado (justo como ocurrio en hello5).

  a) Se escribe hello6.c y se verifica que funcione

     Resultado: "La respuesta es 42"

  En este caso, la respuesta del programa es esperada, porque estamos diciendole que imprima el valor que previamente 
  guardamos en la variable i, el cual es 42.
  
------------------------------------------------------------------------------------------------------------------------------
5. Remocion de Prototipo

  a) Se escribe hello7.c 
  
     Resultado: "La respuesta es 42"

  b) Al ejecutar los comandos, se reciben warnings como en casos anteriores pero compila y ejecuta:

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

En cuanto a los warnings, el segundo hace referencia a que deberia incluirse la libreria stdio.h o una declaracion de esta
funcion en el codigo, para utilizarla, sin embargo, printf es un caso especial, ya que al ser tan utilizada, viene 
incorporada al compilador (propio de gcc y otros compiladores), por lo tanto, se logra vincular. 

Ademas, el primer warning esta avisando que hay una declaracion implicita de printf => ante no haber una declaracion, 
el compilador asume su declaracion en base al primer uso de dicha funcion (entonces en este caso, asume que printf 
devuelve una cadena y un int). => CARACTERISTICA PROPIA DE C

En este caso se logro compilar y la ejecucion fue exitosa, sin embargo, esto dependera del compilador que se utilize. En este
caso, al utilizar gcc, el hecho de usar declaraciones implicitas no rompe el codigo, ya que este decide flexibilizarse en 
lugar de considerarlo como un error. En si, segun el estandar de C, no es correcto utilizar declaraciones de funciones implicitas,
sin embargo, al no haber una norma sobre que hacer cuando no se respeta esta medida, gcc decide flexibilizarse, crear el 
ejecutable (si es posible) y enviar warnings. Si se hubiese compilado utilizando clang, no seria posible crear el ejecutable. 

En conclusion, el programa funciona a pesar de utilizar declaraciones implicitas ya que estamos compilando con gcc.
A pesar de esto, no es una buena practica utilizar declaraciones implicitas para funciones, ya que podria traer 
problemas durante la vinculacion. El caso de printf es especial, ya que esta viene incluida en el compilador, por lo tanto
no necesita que se escriba una declaracion ni definicion. Por lo tanto, es recomendable incluir definiciones y en lo posible 
declaraciones para las funciones. 

------------------------------------------------------------------------------------------------------------------------------
6. Compilacion Separada: Contratos y Modulos

funcion wrapper: en este caso existe una declaracion y una definicion de la funcin prontf. Esta es una funcion wrapper,
                 su unica funcion es llamar a la ya existente funcion printf y ejecutarla.

  a) Se escriben studio1.c y hello8.c

  b) Si se intentase crear el ejecutable utilizando solamente hello8.c y el comando:

  gcc hello8.c -o hello8

  Se podria llegar a compilar el archivo, sin embargo fallaria la vinculacion debido a que hay una referencia indefinida 
  a prontf. Por lo tanto, a pesar de que hello8.c sea correcto semantica y sintacticamente para este compilador, no puede 
  resolverse el call a prontf (presente en el archivo objeto) durante la vinculacion.

  La definicion de prontf se encuentra en la unidad de traduccion de studio1.c. 

  Se puede generar el ejecutable a partir de las 2 unidades de traduccion utilizando el siguiente comando:
  
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

   Se puede ver que hay varios warnings, la mayoria en studio.c. Sin embargo, hay un warning con respecto 
   a hello8.c,este esta diciendo que como ocurrio en hello7.c, se esta declarando una funcion de manera implicita, en 
   este caso,dicha funcion es prontf. 

   Ademas, en studio1.c, esto tambien ocurre, ya que no se incluye declaracion para la funcion printf. Por lo tanto, 
   en otro warning, el compilador recomienda incluir la biblioteca estandar mediante "include <stdio.h>" o declararla
   en el mismo codigo. Y al igual que en hello7.c, el compilador esta informando que el uso que se le esta dando a
   printf, no es compatible con el que ya viene incluido en el compilador.

   A pesar de todos estos warnings, se logra crear el ejecutable debido a que gcc es permisivo, encontro la definicion de 
   prontf en studio1.c y resolvio el llamado que hace el linker. Para ello, primero se compilan ambos codigos y se obtienen
   ambos archivos objetos (de aqui surgen los warnings). Luego el linker es quien se encarga de crear el ejecutable 
   a partir de estos 2 archivos. 

   Finalmente, se obtiene la respuesta esperada:

     "La respuesta es 42"

   A diferencia de como ocurrio con hello4, en este caso al tener una definicion de prontf (aunque sea en otro archivo),
   al vincular el archivo hello8.o con studio1.o es posible crear el ejecutable. 

  c) Se crea el archivo hello8Parametros.c que invoca a la funcion prontf con menos o mas parametros que con los 
     que se la declaro en studio1.c. En este caso, no se le incluye en la invocacion, el parametro i. 

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

   "La respuesta es 1806235008",la cadena de chars "la respuesta es " no es un parametro por lo tanto se imprime sin problemas. 

   Si agregamos parametros de mas, tampoco genera ningun problema. 

   Normalmente no podria llamarse a una funcion con mas o menos parametros en C, sin embargo, en este caso si es posible. 
   Es capaz de compilar ya que no hay ningun prototipo de prontf definido. El compilador no tiene contra que contrastar 
   la cantidad de argumentos que necesita dicha funcion. Al compilar hello8.c no conoce de otros archivos (osea no sabe 
   de studio1.c).Luego al vincularlos, al haber un call a una funcion que esta definida en otro archivo, los enlaza
   (pone la direccion de la funcion) => EL LINKER NO HACE NINGUNA VERIFICACION.

   El linker recibe los 2 archivos objeto. Se va a poder hacer el llamado a prontf, y en algun momento se van a mandar 3 
   argumentos (se van a apilar) pero luego al ejecutar la funcion, se van a tomar 2 (se desapilan 2) que son los necesarios 
   para dicha funcion. Por lo tanto, se genera un desbalance. Estos son temas de implementacion, 
   pero en cuanto al codigo --> funciona

   En tiempo de ejecucion no hay control de cantidad de parametros, esto se analiza en tiempo de compilacion pero en este 
   caso no dan error ya que no hay prototipo de la funcion contra el cual contrastar la cantidad de parametros necesaria. 

   Al hacer esto, entramos en un "area de comportamiento indefinido", no existe prototipo y gcc es demasiado permisivo  
   entonces no sabemos que puede pasar ya que no se estan cumpliendo las reglas y el estandar de C no indica que pasos 
   seguir cuando esto ocurre.
        
   Existe la posibilidad de que si se lo vuelve a llamar falle por como quedo la pila, quiza quedo desbalanceada. Tambien,
   que funcione en mi computadora, no quiere decir que funcionaria en todas las maquinas, es decir no garantiza que sea 
   portable.

   Estos son comportamientos indefinidos, no se puede garantizar nada. 

  d)

   i) Se escribe el contrato studio.h
    
   ii) Se escribe hello9.c.

   iii) Se escribe studio2.c

   iv) Se utiliza el comando: gcc hello9.c studio2.c -o hello9 para obtener el ejecutable de hello9.

 Si no se incluye studio2.c en el comando, no se encontraria la definicion de prontf y daria error. Sin embargo,
 en este caso se obtiene el ejecutable hello9 sin ningun warning o error.
  
 Al ejecutarlo se obtiene la respuesta esperada: 

        "La respuesta es 42" .

 Esto se debe a que a diferencia del caso anterior en el que en hello8.c no se incluia una declaracion para prontf, 
 en hello9.c, esto no ocurre. Prontf esta declarada en studio.h, y esta biblioteca se esta incluyendo en hello9.c 
 mediante un include. Ademas,en studio2.c a diferencia de en studio1.c, printf no esta declarada implicitamente, 
 sino que se encuentra declarada en la biblioteca standar y esta se encuentra incluida en el codigo. 
 
 Al incluir el contrato se incluyen los prototipos -> no se podria aumentar la cantidad de parametros -> daria error
 
 Ventajas de incluir el contrato: nos provee los prototipos de las funciones (evita la invocacion con una cantidad 
 erronea de parametros), permite detectar errores en el cliente (podria usarlo mal, por ejemplo, si se le pasan menos 
 parametros, hay un error) detectandolo en tiempo de compilacion y no de ejecucion. Tambien permite ver que el proveedor 
 este entregando el producto correcto.

------------------------------------------------------------------------------------------------------------------------------
Credito Extra:

Una biblioteca es una coleccion de archivos objeto. Por lo tanto, contienen declaraciones de estructuras y funciones. 
Suelen guardarse como archivos.rar o archivos.zip donde contienen generalmente varios archivos.o (tiene codigo compilado). 
Es decir, contienen codigo ensamblado de funciones. Por lo tanto, el uso de bibliotecas, permite hacer uso de las 
funcionalidades que se encuentran dentro de la misma, sin la necesidad de reescribirlas. Al vincular el archivo que se desea
compilar con la biblioteca, se pueden resolver los llamados a funciones que se encuentren definidas en la misma. 

A la par de las bibliotecas, existen los archivos.h, estos son contratos que al incluirlos, se evita reescribir los prototipos 
de las funciones que se encuentran dentro del contrato. Es decir, contienen la informacion acerca de que tipo de dato devuelve 
cada funcion, y cuantos y de que tipo son los parametros que necesita, si es que necesita. El preprocesador reemplaza el include
por las declaraciones desarrolladas en dicho contrato.

En base a esto, se puede decir que una biblioteca es un "material de referencia que uno puede utilizar".

La biblioteca en si no es portable ya que contiene archivos.o ya compilados, los cuales dependen de cada procesador. Sin embargo, 
el codigo fuente, es decir, los archivos.c si son portables, ya que no habria que reescribirlos, simplemente habria que volver
a compilarlos bajo el nuevo procesador y obtener los archivos.o propios del nuevo procesador. 

Ventajas: Evitar la reescritura de codigo, evitar todo el trabajo y tiempo que podria llevar lograr todas las funcionalidades 
          que brinda, evitar posibles errores. Por lo tanto, tambien reducen el tiempo que lleva desarrollar el programa. 
          Y cualquier otra ventaja relacionada a una mayor rapidez en el desarrollon (por ejemplo, menos costos).

Desventajas: Funcionalidades desaprovechadas, si se implementa una biblioteca con muchisimas funcionales de las cuales solo
             necesitamos unas pocas, esto podria hacer que nuestro codigo pese mas de lo necesario, y a la vez, se estaria 
             desaprovechando codigo.

------------------------------------------------------------------------------------------------------------------------------

