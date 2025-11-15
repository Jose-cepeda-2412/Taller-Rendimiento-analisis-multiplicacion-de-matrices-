/*************************************************************************************
* Fecha:14/11/2025                                                                   *
* Autores: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas.                    *
* Docente: J.Corredor PhD                                                            *   
* Programa:                                                                          *
*      Multiplicacion de Matrices clasica con hilos Posix (PTHREADS)                 *
* Version:                                                                           *
*      Paralelismo con hilos pthreads "POSIX"                                        *
* Descripcion:En este programa se implementan funciones para realizar                *
*             la multiplicacion clasica de matrices mediante el uso de hilos         *
*             POSIX. Este programa contiene                                          *
*             funciones para inicializar las matrices, imprimir las matrices,        *
*             medir el tiempo de ejecucion y realizar la multiplicacion de matrices. *
**************************************************************************************/
//se declaran las bibliotecas que se van a utilizar en el programa.
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "moduloMMClasicaPosix.h" //se incluye el archivo de cabecera que contiene la funciones que se van a utilizar en el programa.


pthread_mutex_t MM_mutex; //se declara un mutex con el proposito de sincronizar los hilos.
double *matrixA, *matrixB, *matrixC;//se declaran las matrices que se va a utilizar en el programa. En este caso C=A*B.
struct timeval inicio, fin;//se declaran las variables de tiempo que se van a utilizar para medir el tiempo de ejecucion del programa.



void InicioMuestra(){//se declara la funcion de InicioMuestra() que va a iniciar el temporizador de tiempo de ejecucion.
    gettimeofday(&inicio, (void *)0);//se devuelve el tiempo inicial en microsegundos.
}

void FinMuestra(){ //se declara la funcion FinMuestra() la cual va a detener el temporizador de tiempo de ejecucion.
    gettimeofday(&fin, (void *)0);//se devuelve el tiempo final en microsegundos
    fin.tv_usec -= inicio.tv_usec;//se calcula la diferencia de los tiempos en microsegundos.
    fin.tv_sec  -= inicio.tv_sec;//se calcula la diferencia de los tiempos en segundos
    double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);//se calcula el tiempo total de ejecucion en segundos.
    printf("%9.0f \n", tiempo);//se imprime el tiempo total.
}

void iniMatrix(double *m1, double *m2, int D){ //se declara la funcion iniMatrix() la cual va a inicializar las matrices.
    for(int i = 0; i < D*D; i++, m1++, m2++){ //se crea un ciclo for con el proposito de recorrer los elementos de las matrices.
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0); //se inicializa el elemento de la primera matriz con un valor entre 1 y 5
        *m2 = (double)rand()/RAND_MAX*(9.0-5.0); //se inicializa el elemento de la segunda matriz con un valor ente 5 y 9.
    }   
}

void impMatrix(double *matriz, int D){//se declara la funcion impMatrix() la cual va a imprimir las matrices.
    if(D < 9){//se verifica que el tamaño de la matriz sea menor a 9, si es asi entonces se ejecuta lo siguiente:
        for(int i = 0; i < D*D; i++){ //se crea un ciclo for con el proposito de recorrer los elementos de la matriz.
            if(i%D==0) printf("\n");//se imprime un salto de linea cada vez que se recorre una fila de la matriz.
            printf(" %.2f ", matriz[i]);//se imprime el elemento de la matriz.
        }   
        printf("\n>-------------------->\n");//se imprime un salto de linea para que el resultado sea legible.
    }
}

void *multiMatrix(void *variables){ //se declara la funcion multiMatrix() la cual va a realizar la multiplicacion de matrices.
    struct parametros *data = (struct parametros *)variables;//se convierte el puntero generico a un puntero de parametros.

    int idH  = data->idH; //representa el ID del hilo actual.
    int nH   = data->nH; //representa el total de hilos creados.
    int D    = data->N; // representa la dimension de la matriz (NXN)
    int filaI= (D/nH)*idH; // representa la fila inicial que va a calcular el hilo actual.
    int filaF= (D/nH)*(idH+1); //representa la fila final que va a calcular el hilo actual.
    double Suma, *pA, *pB; //se declaran las variables que se van a utilizar para realizar la multiplicacion de matrices.

    for (int i = filaI; i < filaF; i++){ //se crea un ciclo for con el proposito de recorrer las filas de A.
        for (int j = 0; j < D; j++){//se crea un ciclo for con el proposito de recorrer las columnas de B
            pA = matrixA + i*D; //se inicializa el puntero pA con la direccion de la primera entrada de la fila i de la matriz A.
            pB = matrixB + j;//se inicializa el puntero pB con la direccion de la primera entrada de la columna j de la matriz B.
            Suma = 0.0; //se inicializa la variable suma en 0.
            for (int k = 0; k < D; k++, pA++, pB+=D){ //se crea un ciclo for con el proposito de recorrer los elementos de la fila i de A y la columna j de B.
                Suma += *pA * *pB;//se realiza la multiplicacion de los elementos de la fila i de A y la columna j de B y se almacena en la variable suma.
            }
            matrixC[i*D+j] = Suma; //se almacena el resultado de la suma en la matriz C la cual es la matriz resultante de multiplicar A*B.
        }
    }

    pthread_mutex_lock (&MM_mutex); //se bloquea el mutex con el proposito de sincronizar los hilos.
    pthread_mutex_unlock (&MM_mutex);//se desbloquea el mutex con el proposito de liberar el acceso a la seccion critica.
    pthread_exit(NULL); //se finaliza la ejecucion del hilo actual.
}