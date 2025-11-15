/***************************************************************************************
* Fecha:14/11/2025                                                                     *
* Autores: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas.                      *
* Docente: J.Corredor PhD                                                              *
* Programa:                                                                            *
*      Multiplicacion de Matrices algoritmo clasico                                    *
* Version:                                                                             *
*      Paralelismo con Hilos Pthreads "Posix"                                          *
* Descripcion:Este programa multiplica dos matrices de tamaño NXN usando               *
*   hilos en vez de procesos,donde cada hilo se encarga de calcular una                *
*   parte de la matriz resultante para comparar el rendimiento con la version que usa  *
*   fork, lo que permite analizar la escalabilidad y la eficiencia de pthreads.        *
****************************************************************************************/

//se declaran las bibliotecas que se van a utilizar en el programa.
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "moduloMMClasicaPosix.h" //se incluye el archivo de cabecera que contiene las funciones que se van a utilizar en el programa.


int main(int argc, char *argv[]){//se declara la funcion principal la cual va a recibir los argumentos que se le pasan al programa y va a ejecutar el programa.
  if (argc < 3){//se verifica que se hayan pasado los argumentos necesarios al programa.
    printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");//se muestra el comando para ejecutar el programa.
    exit(0);	//se sale del programa si no se han pasado los argumentos necesarios.
  }
    int N = atoi(argv[1]); //se convierte el primer argumento a un entero y se guarda en la variable N, N representa el tamaño de las matrices (NXN).
    int n_threads = atoi(argv[2]); //se convierte el segundo argumento a un entero y se guarda en la variable n_threads, n_threads representa el numero de hilos que se van a utilizar en el programa.

    pthread_t p[n_threads];//se declara un arreglo de identificadores de hilos de tamaño n_threads.
    pthread_attr_t atrMM;//se declara un atributo de hilo para configurar el comportamiento de los hilos.

  matrixA  = (double *)calloc(N*N, sizeof(double));//se reserva memoria dinamica para la matriz A y se inicializa en 0.
  matrixB  = (double *)calloc(N*N, sizeof(double));//se reserva memoria dinamica para la matriz B y se inicializa en 0.
  matrixC  = (double *)calloc(N*N, sizeof(double));//se reserva memoria dinamica para la matriz C y se inicializa en 0.

  iniMatrix(matrixA, matrixB, N);//se inicializan las matrices A y B.
  impMatrix(matrixA, N);//se imprime la matriz A.
  impMatrix(matrixB, N);//se imprime la matriz B.

  InicioMuestra();//se inicia el temporizador de tiempo de ejecucion

  pthread_mutex_init(&MM_mutex, NULL);//se inicializa el mutex para sincronizar los hilos.
  pthread_attr_init(&atrMM);//se inicializa el atributo del hilo.
  pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);//se configura el atributo del hilo para que sea joinable, lo que significa que el hilo principal debe esperar a que el hilo termine antes de continuar.

    for (int j=0; j<n_threads; j++){//se utiliza un ciclo for para crear los hilos segun el numero de hilos que se haya especificado
    struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); //se reserva memoria dinamica para la estructura que almacena los parametros del hilo.
    datos->idH = j;//ID del hilo atual
    datos->nH  = n_threads;//numero total de hilos
    datos->N   = N;//representa el tamaño de la matriz (NXN)

        pthread_create(&p[j],&atrMM,multiMatrix,(void *)datos);//crea el hilo y le pasa la funcion multiMatrix() como argumento,junto con los datos que infican que parte de la matriz se va a calcular.
  }

    for (int j=0; j<n_threads; j++)//se crea un ciclo for para esperar a que todos los hilos terminen de ejecutarse antes de continuar.
        pthread_join(p[j],NULL);//se espera a que el hilo termine de ejecutarse.

  FinMuestra();//se detiene el temporizador de tiempo de ejecucion.

  impMatrix(matrixC, N);//se imprime la matriz resultante C (C=AXB)

  /*Liberacion de memoria*/
  free(matrixA);//se libera la memoria dinamica de la matriz A.
  free(matrixB);//se libera la memoria dinamica de la matriz B.
  free(matrixC);//se libera la memoria dinamica de la matriz C.

  pthread_attr_destroy(&atrMM);//se destruye el atributo del hilo.
  pthread_mutex_destroy(&MM_mutex);//se destruye el mutex.
  pthread_exit (NULL);//se finaliza la ejecucion del hilo principal.

  return 0;//se retorna 0 para indicar que el programa se ejecuto correctamente.
}