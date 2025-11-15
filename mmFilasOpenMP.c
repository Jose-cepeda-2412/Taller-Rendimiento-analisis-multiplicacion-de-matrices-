/***************************************************************************************
*  Fecha:14/11/2025                                                                    *
*  Autores: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas.                     *
*  Docente: J.Corredor PhD                                                             *
*  Programa:                                                                           *
*       Multiplicacion de Matrices algoritmo matriz Transpuesta (Filas x Filas)        *
*  Version:                                                                            *
*       Paralelismo con OpenMP                                                         *
*  Descripcion:El programa realiza la multiplicacion de matrices cuadradas utilizando  *
*   el metodo de transposicion de la segunda matriz (filas X filas) mediante openMP.   *
*   El objetivo es comparar la eficiencia de esta version con respecto a la            *
*   multiplicacion clasica y otras implementaciones.                                   *
***************************************************************************************/

//se declaran las bibliotecas que se van a utilizar en el programa.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

#include "moduloMMFilasOpenMP.h" //se incluye el archivo de cabecera que contiene las funciones que se van a utilizar en el programa.


int main(int argc, char *argv[]){//se declara la funcion principal la cual va a ejecutar el progragrama
  if(argc < 3){//se verifica que se hayan pasado los argumentos necesarios al programa.
    printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");//se muestra el comando para ejecutar el programa.
    exit(0);//se sale del programa si no se han pasado los argumentos necesarios.
  }


  int N = atoi(argv[1]);//se convierte el primer argumento a un entero y se guarda en la variable N, N representa el tamaño de las matrices (NXN).
  int TH = atoi(argv[2]);//se convierte el segundo argumento a un entero y se guarda en la variable TH, TH representa el numero de hilos que se van a utilizar en el programa en la ejecucion paralela.
  double *matrixA  = (double *)calloc(N*N, sizeof(double));//se reserva memoria dinamica para la matriz A y se inicializa en 0.
  double *matrixB  = (double *)calloc(N*N, sizeof(double));//se reserva memoria dinamica para la matriz B y se inicializa en 0.
  double *matrixC  = (double *)calloc(N*N, sizeof(double));//se reserva memoria dinamica para la matriz C y se inicializa en 0.
  srand(time(NULL));//se inicializa el generador de numeros aleatorios para llenar las matrices con valores distintos.

  omp_set_num_threads(TH);//se configura el numero de hilos que openMP va a utilizar en las regiones paralelas.

  iniMatrix(matrixA, matrixB, N);//se inicializan las matrices A y B con valores aleatorios.

  impMatrix(matrixA, N, 0);//se imprime la matriz A de forma normal.
  impMatrix(matrixB, N, 1);//se imprime la matriz B de forma transpuesta.

  InicioMuestra();//se inicializa el temporizador de tiempo de ejecucion.
  multiMatrixTrans(matrixA, matrixB, matrixC, N);//se llama  a la funcion multiMatrixTrans() para realizar la multiplicacion de matrices, al usar este metodo de multiplicacion se mejora la localidad de los datos y se reduce el almacenamiento temporal de datos (cache)
  FinMuestra();//se detiene el temporizador de tiempo de ejecucion.

  impMatrix(matrixC, N, 0);//se imprime la matriz resultante C.

  /*LiberaciOn de Memoria*/
  free(matrixA);//se libera la memoria dinamica de la matriz A.
  free(matrixB);//se libera la memoria dinamica de la matriz B.
  free(matrixC);//se libera la memoria dinamica de la matriz C.

  return 0;//se retorna 0 para indicar que el programa se ejecuto correctamente.
}