/************************************************************************
* Fecha:14/11/2025                                                      *
* Autores: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas.       *
* Docente: J.Corredor PhD                                               *      
* Programa:                                                             *
*      Multiplicacion de Matrices algoritmo clasico                     *
* Version:                                                              *
*      Paralelismo con Hilos Pthreads "POSIX"                           *
* Descripcion: Este archivo de cabecera contiene las funciones que se   *
* van a utilizar en mmClasicaPosix.c                                    *
*************************************************************************/

#ifndef __MODULO_MM_CLASICA_PTHREADS_H__ //se define una directiva de inclusion condicional para evitar que el archivo de cabecera se incluya mas de una vez en un mismo archivo de codigo.
#define __MODULO_MM_CLASICA_PTHREADS_H__ 
//se define una constante que se utilizara para evitar que el archivo de cabecera se incluya mas de una vez en el mismo encabezado

//se declaran las librerias que se van a utilizar en el programa
#include <pthread.h>
#include <sys/time.h>


extern pthread_mutex_t MM_mutex;//se declara el mutex que se va a utilizar para sincronizar los hilos.
extern double *matrixA, *matrixB, *matrixC;//se declaran las matrices que se van a utilizar en el programa.
extern struct timeval inicio, fin;//se declaran las variables de tiempo que se van a utilizar para medir el tiempo de ejecucion del programa.


struct parametros{//se declara una estructura que va a contener los parametros que se van a pasar a la funcion multiMatrix.
    int nH;//Representa el numero total de hilos
    int idH;//representa el ID de hilos actual
    int N;//representa el tamaño de la matriz (NXN)
};


void InicioMuestra(void);//se declara la funcion que va a iniciar el temporizador de tiempo de ejecucion.
void FinMuestra(void);//se declara la funcion que va a detener el temporizador de tiempo de ejecucion.
void iniMatrix(double *m1, double *m2, int D);//se declara la funcion que va a inicializar las matrices A y B.
void impMatrix(double *matriz, int D);//se declara la funcion que va a imprimir las matrices A y B.
void *multiMatrix(void *variables);//se declara la funcion que va a realizar la multiplicacion de matrices.

#endif//se cierra la directiva de inclusion condicional.