/***************************************************************************
* Fecha:14/11/2025                                                         *
* Autores: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas           *
* Docente: J.Corredor PhD                                                  *
* Programa:                                                                *
*      Multiplicacion de Matrices algoritmo clasico                        *
* Version:                                                                 *
*      Paralelismo con Procesos Fork                                       *
* Descripcion:                                                             *
*        Este programa realiza la multiplicacion de matrices cuadradas     *
*        utilizando procesos fork para evaluar el rendimiento en funcion   *
*        del tamaño de la matriz y el numero de procesos.                  *
****************************************************************************/

//se declaran las bibliotecas que se van a utilizar en el programa.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include "moduloMMClasicaFork.h" //se incluye el archivo de cabecera que contiene las funciones que se van a utilizar en el programa.

int main(int argc, char *argv[]) {// se declara la funcion principal la cual va a ejecutar el programa.
  if (argc < 3) { //se verifica que se hayan ingresados los argumentos necesarios para ejecutar el programa, en este caso el programa necesita el tamaño de la matriz y el numero de procesos. 
    printf("\n \t\tUse: $./nom_ejecutable Size Hilos \n");//$./nom_ejecutable Size hilos representa el comando que se debe ingresar en la terminal para ejecutar el programa.
    exit(0);//se sale del programa si no se ingresaron los argumentos necesarios.
  }
    //se convierten los argumentos de texto a enteros usando la funcion atoi.
  int N      = (int) atoi(argv[1]);//se convierte el primer argumento a entero y se guarda en la variable N, N representa el tamaño de la matriz cuadrada (NXN).
  int num_P  = (int) atoi(argv[2]);//se convierte el segundo argumento a entero y se guarda en la variable num_p que representa el numero de procesos que se van a crear.
  double *matA = (double *) calloc(N*N, sizeof(double)); //se reserva memoria dinamica para la matriz A y se inicializa en 0.
  double *matB = (double *) calloc(N*N, sizeof(double));//se reserva memoria dinamica para la matriz B y se inicializa en 0.
  double *matC = (double *) calloc(N*N, sizeof(double));//se reserva memoria dinamica para la matriz C y se inicializa en 0.

    srand(time(0)); //se inicializa el generador de numeros aleatorios para llenar las matrices son valores distintos.

    iniMatrix(matA, matB, N);//Se inicializan las matrices A y B con valores aleatorios.
    impMatrix(matA, N);//se imprime la matriz A.
    impMatrix(matB, N);//se imprime la matriz B.

    int rows_per_process = N/num_P;//se calcula el numero de filas que se van a calcular por cada proceso, para ello se divide el tamaño de la matriz entre el numero de procesos.

  InicioMuestra();//se inicia el temporizador con el proposito de medir el tiempo de ejecucion del programa.

    for (int i = 0; i < num_P; i++) {//se crea un ciclo for que va a generar los procesos fork encargados de realizar la multiplicacion de matrices.
        pid_t pid = fork();//se genera un nuevo proceso usando la funcion fork. si pid es 0, el proceso es el hijo, si pid es mayor a 0 el proceso es el padre.

        if (pid == 0) { //si el proceso es el hijo, se ejecuta lo siguiente:
            int start_row = i * rows_per_process;//se define la fila inicial que va a calcular el proceso hijo.
            int end_row = (i == num_P - 1) ? N : start_row + rows_per_process;//se define la fila final que va a calcular el proceso hijo, si el proceso es el ultimo entonces la fila final equivale al tamaño de la matriz. (practicamente se esta definiendo el rango de filas de la matriz C que va a calcular el proceso hijo)

      multiMatrix(matA, matB, matC, N, start_row, end_row); //se llama a la funcion multiMatriz con el proposito de calcular las filas asignadas en el rango de start_row a end_row.

      if(N<9){// si el tamaño de la matriz es menor a 9, entonces se imprime los resultados calculados por el proceso hijo. lo que equivale a las entradas de la matriz C (C=A*B)
              printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), start_row, end_row-1);//se imprime el pid del proceso hijo y el rango de filas que calculo
              for (int r = start_row; r < end_row; r++) {//se crea un ciclo for que va a imprimir las filas calculadas por el proceso hijo.
                  for (int c = 0; c < N; c++) {//se crea un ciclo for que va a imprimir las columnas calculadas por el proceso hijo
                      printf(" %.2f ", matC[N*r+c]);//se imprime el valor de la matriz C en la entrada (fila,columna)
                  }
                  printf("\n");//se imprime un salto de linea para que el resultado sea mas legible a la hora de mostrar la matriz C.
              }
      }
            exit(0); //se sale del proceso hijo termina y le devuelve el control al proceso padre.
        } else if (pid < 0) {//si el proceso no se creo correctamente se ejecuta lo siguiente:
            perror("fork failed");//se imprime un mensaje de error.
      free(matA);//se libera la memoria dinamica de la matriz A.
      free(matB);//se libera la memoria dinamica de la matriz B.
      free(matC);//se libera la memoria dinamica de la matriz C.
            exit(1);//se retorna 1 para indicar que hubo un error en la creacion del proceso.
        }
    }

    for (int i = 0; i < num_P; i++) {//se crea un ciclo for que va a esperar a que todos los procesos hijos terminen de ejecutarse antes de continuar.
        wait(NULL);//se espera a que el proceso hijo termine de ejecutarse.
    }

  FinMuestra(); //se detiene el temporizador de tiempo de ejecucion.

  free(matA);//se libera la memoria dinamica de la matriz A.
  free(matB);//se libera la memoria dinamica de la matriz B.
  free(matC);//se libera la memoria dinamica de la matriz C.

    return 0;//se retorna 0 para indicar que el programa se ejecuto correctamente.
}