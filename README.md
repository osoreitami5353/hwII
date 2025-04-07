# Homework II
Estos códigos corresponden a las consignas del homework 2 de la materia Paradigmas de la Programación. El archivo de las consignas es `I102_Homework2.pdf`.

Cada ejercicio contiene un archivo `.hpp`, `.cpp` y uno `.cpp` que contiene el main(), siguiendo las especificaciones indicadas en el enunciado. Se incluyen instrucciones de compilación para cada uno.

* Aclaración importante *
  Me tomé el atrevimiento de agregar algunas cosas de más a algunos ejercicios sólo para probar más funcionalidades y, cuando era posible, probar a acercarme ligeramente a lo que podría verse (con muchas ganas de intentar verlo) como una base de datos, ya que en esas actividades se realizan registros que se mantienen durante la ejecución. Espero no sea problema, y en caso de que lo sea pido disculpas por ello.

## Ejercicio I — Clase `Time`

En esta actividad se implementa una clase llamada `Time`, diseñada para representar y manipular horarios utilizando el formato de 12 horas con notación A.M./P.M.

### Características principales:

- La clase permite:
  - Inicializar tiempos con diferentes cantidades de parámetros (solo hora, hora y minutos, etc.).
  - Obtener la hora, los minutos, los segundos y el estado A.M./P.M. por separado.
  - Mostrar la hora completa en formato tradicional y en formato 24hs.
  - Modificar el tiempo ingresado a través del menú interactivo.
  - Registrar nuevo tiempo.

### Validaciones implementadas:
  - Verifica que las horas estén entre 0 y 12 (formato AM/PM).
  - Asegura que minutos y segundos no sean negativos.
  - Convierte automáticamente minutos/segundos excedentes a horas/minutos.
  - Valida el formato de entrada del AM/PM (`am`, `AM`, `pm`, `PM`).

### Cómo probarlo:

1. Compilar y ejecutar con:
   - g++ EjercicioImain.cpp EjercicioI.cpp -Wall -g -std=c++20 -o ejerI (en el ejercicio I no es necesario compilar evitando los warnings por la versión, ya que no se utiliza "auto", pero como en los otros ejercicios suele utilizarse, es cómodo compilar con la misma línea con ligeras variaciones.
   - ./ejerI
2. Al ejecutar el programa, se solicita ingresar una hora con el siguiente formato: h m s am/pm
3. Luego se despliega un menú interactivo con opciones para:
    - Modificar la hora.
    - Mostrar hora, minutos, segundos o AM/PM individualmente.
    - Mostrar la hora completa o en formato 24hs.

4. El programa se mantiene activo hasta seleccionar la opción **8. Salir**.

### Archivos involucrados:
- `EjercicioI.hpp`: Declaración de la clase Time, funciones auxiliares y validaciones.
- `EjercicioI.cpp`: Contiene la implementación de la clase `Time`.
- `EjercicioImain.cpp`: Punto de entrada del programa, con el menú y la interacción con el usuario.

## Ejercicio II – Sistema de Gestión de Cursos y Alumnos

Este ejercicio implementa un sistema orientado a objetos para gestionar cursos y estudiantes. El objetivo es permitir la creación de cursos y alumnos, así como su asociación mediante inscripciones y desinscripciones. Se destacan principios de encapsulamiento, uso de std::vector, manejo de punteros inteligentes (std::shared_ptr), y funciones organizadas por casos de uso.

Respuesta a punto c): La relación entre los objetos Curso y Estudiante es una asociación bidireccional de muchos a muchos. Esto significa que un objeto Curso puede tener asociados varios objetos Estudiante, y a su vez, un Estudiante puede estar inscrito en varios Cursos. En el diseño orientado a objetos, esta relación se implementa generalmente mediante contenedores (por ejemplo, vectores) en ambas clases, o utilizando una clase intermedia si se requiere manejar información adicional sobre la inscripción (como fecha, notas, etc.).

### Características principales:
  - Creación de cursos con capacidad máxima e identificación única.
  - Registro de estudiantes, almacenando su nombre e ID.
  - Inscripción de alumnos a cursos existentes (si no están llenos).
  - Desinscripción de alumnos de cursos.
  - Consulta de disponibilidad (si el curso está lleno o no).
  - Búsqueda de estudiantes dentro de un curso.
  - Visualización de todos los cursos y estudiantes.
  - Información detallada de un curso o un estudiante específico.
  - Creación de un curso nuevo a partir de la copia de otro.
  - Interfaz en consola clara y organizada, con menú numérico y separación visual.

### Validaciones implementadas:
  - Evita inscribir estudiantes en cursos llenos.
  - Impide inscribir al mismo estudiante dos veces en un mismo curso.
  - Valida que el curso o alumno exista antes de operar sobre ellos.
  - Muestra mensajes informativos y claros ante errores o acciones inválidas.

### Cómo probarlo:
1. Compilar y ejecutar con:
   - g++ EjercicioIImain.cpp EjercicioII.cpp -Wall -g -std=c++20 -o ejerII
   - ./ejerII
2. Seguir las instrucciones del menú interactivo para:
    - Crear cursos (opción 1) y estudiantes (opción 2).
    - Inscribir/desinscribir estudiantes (opciones 4 y 5).
    - Verificar estados, buscar alumnos, y mostrar información (opciones 3, 6–10).
    - Probar la copia de un curso con la opción 11.
3. Ingresar valores desde teclado según se solicite.
4. Finalizar el programa seleccionando la opción 12.

### Archivos involucrados:
- `EjercicioII.hpp`: Contiene las clases Course y Student, además de las funciones auxiliares para cada opción del menú.
- `EjercicioII.cpp`: Implementaciones de las funciones declaradas en el .hpp.
- `EjercicioIImain.cpp`: Contiene la función principal main() con el menú interactivo.

### Ejercicio III: Operaciones entre Enteros, Reales y Complejos usando Polimorfismo en C++

En este ejercicio, se implementó una jerarquía de clases para representar números de diferentes tipos (Integer, Real, Complex) y se permitió realizar operaciones aritméticas entre ellos utilizando polimorfismo y dynamic_cast. La clase base abstracta Number define una interfaz común, y cada clase derivada implementa las operaciones respetando su lógica matemática.

### Características principales:
  - Se implementa una jerarquía de clases que representa números enteros (Integer), reales (Real) y complejos (Complex), todos derivados de una clase abstracta Number.
  - Cada clase define cómo operar con otros tipos mediante métodos polimórficos: add, subtract, multiply y divide.
  - Las operaciones entre tipos distintos (por ejemplo, un entero y un número complejo) están soportadas mediante conversiones usando dynamic_cast.
  - El programa gestiona internamente la creación del tipo de resultado adecuado para cada operación.
  - Se implementa un sistema de menús para que el usuario pueda ingresar dos números de tipos variados y realizar operaciones entre ellos.
  - Se utilizan flujos (ostringstream) para mostrar los resultados en formato legible, especialmente para los complejos, como "a+bi" o "a-bi".

### Validaciones implementadas:
  - Validación de selección de tipo de número a ingresar (entero, real o complejo).
  - Control de división por cero en números reales y enteros.
  - En la división de números complejos, se evita la división por módulo cero.
  - Validación del tipo del operando mediante dynamic_cast para operar correctamente según el tipo real del objeto.
  - Al dividir dos enteros, el resultado se convierte automáticamente en un número real si es necesario (por ejemplo, 5 / 2 = 2.5).

### Cómo probarlo:
1. Compilar y ejecutar con:
   - g++ EjercicioIIImain.cpp EjercicioIII.cpp -Wall -g -std=c++20 -o ejerIII
   - ./ejerIII
2. Ingresar el primer número, eligiendo su tipo:
    - Entero: se ingresa un valor como 5
    - Real: se ingresa un valor como 3.14
    - Complejo: se ingresan parte real e imaginaria como 2 y 4 para 2+4i
3. Repetir el proceso para el segundo número.
4. Seleccionar la operación deseada (suma, resta, multiplicación o división).
5. El programa mostrará el resultado correctamente tipado (por ejemplo, un Real si fue la suma entre un Integer y un Real, o un Complex si alguno de los operandos lo era).
6. Se puede repetir el proceso con diferentes combinaciones de tipos.
   
### Archivos involucrados:
- `EjercicioIII.hpp`: Contiene la clase abstracta Number y las clases derivadas Integer, Real y Complex, junto con las declaraciones de funciones auxiliares para el menú.
- `EjercicioIII.cpp`: Implementaciones de los métodos de cada clase y de las funciones auxiliares del ejercicio.
- `EjercicioIIImain.cpp`: Contiene la función main() con el menú interactivo para realizar operaciones entre distintos tipos de números.

### Ejercicio IV: Sistema Bancario con Cuentas Vinculadas usando Herencia y Polimorfismo en C++

En este ejercicio, se desarrolló un sistema bancario que permite gestionar cajas de ahorro y cuentas corrientes utilizando herencia y polimorfismo. La clase base abstracta BankAccount define una interfaz común para ambas cuentas, mientras que SavingsBank y CheckingAccount extienden su funcionalidad. La cuenta corriente puede acceder a fondos de su caja de ahorro vinculada si es necesario, y se implementa una penalización por mostrar repetidamente la información de la caja de ahorro. El sistema interactúa con el usuario mediante un menú de opciones.

### Características principales:
  - Se definen dos tipos de cuentas bancarias: SavingsBank (caja de ahorro) y CheckingAccount (cuenta corriente), ambas derivadas de la clase abstracta BankAccount.
  - La cuenta corriente puede retirar fondos también desde su caja de ahorro asociada si no tiene saldo suficiente.
  - Se cobra una comisión al mostrar la información de la caja de ahorro más de dos veces.
  - Se implementa un menú interactivo con opciones para crear cuentas, depositar, retirar y mostrar información.

### Validaciones implementadas:
  - No se permite crear más de una cuenta para el mismo titular.
  - Se valida si hay suficientes fondos antes de realizar un retiro.
  - Se impide seleccionar opciones inválidas del menú o ingresar tipos de cuenta no reconocidos.
  - Al retirar desde cuenta corriente, si no alcanza el saldo propio pero sí sumando con la caja de ahorro, se realiza el retiro combinado.

### Cómo probarlo:

1. Compilar y ejecutar con:
   - g++ EjercicioIVmain.cpp EjercicioIV.cpp -Wall -g -std=c++20 -o ejerIV
   - ./ejerIV
2. Crear una nueva cuenta bancaria ingresando el nombre del titular (opción 1).
3. Depositar un monto tanto en la caja de ahorro como en la cuenta corriente (opción 2).
4. Retirar dinero desde una u otra cuenta para comprobar las validaciones de saldo (opción 3).
5. Mostrar la información de las cuentas varias veces para verificar la penalización de la caja de ahorro (opción 4).
6. Intentar crear una cuenta con un nombre ya registrado y observar el mensaje de advertencia.

### Archivos involucrados:
- `EjercicioIV.hpp`: Define las clases BankAccount, SavingsBank y CheckingAccount, así como las funciones auxiliares del menú.
- `EjercicioIV.cpp`: Contiene la implementación de los métodos de las clases y las funciones del menú interactivo.
- `EjercicioIVmain.cpp`: Incluye la función main() con la lógica del menú y el ciclo principal del programa.
