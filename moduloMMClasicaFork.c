/*******************************************************************************
*  Autores: Santiago Hernndez Morales y Jose Jesus Cepeda Vargas               *
*  Fecha:14/11/2025                                                            *
*  Docente: J.Corredor PhD                                                     *
*  Descripcion: Este modulo implementa las funciones auxiliares                *
*  utilizadas por la version del programa de multiplicacion de matrices        *
*  clasica basada en procesos fork(). Este modulo incluye inicializacion       *
*  de matrices,impresion de matrices,medicion de tiempo de ejecucion y         *
*  calculo de multiplicacion de matrices.                                      *
********************************************************************************/


#include "moduloMMClasicaFork.h" //se incluye el archivo de cabecera que contiene las funciones que se van a utilizar en el programa.
//se declaran las bibliotecas que se van a utilizar en el progrma.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Estado interno de temporizacion (encapsulado en este modulo) */
static struct timeval inicio, fin;//se declaran las variables de tiempo que se van a utilizar para medir el tiempo de ejecucion del programa, 

void InicioMuestra(void){//se declara la funcion InicioMuesta() que va a iniciar el temporizador de tiempo de ejecucion.
    gettimeofday(&inicio, (void *)0);//gettimeofday() es una funcion que devuelve el tiempo inicial en microsegundos.
}

void FinMuestra(void){//se declara la funcion FinMuestra() que va a detener el temporizador de tiempo de ejecucion.
    gettimeofday(&fin, (void *)0);//se obtiene el tiempo final en microsegundos.
    fin.tv_usec -= inicio.tv_usec;//se calcula la diferencia de tiempos en microsegundos.
    fin.tv_sec  -= inicio.tv_sec;//se calcula la diferencia de tiempos en segundos.
    double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec);//la variable tiempo reprsenta el tiempo total de ejecucion en microsegundos
    /* Tiempo en microsegundos */
    printf("%9.0f \n", tiempo);//se imprime el tiempo de ejecucion en microsegundos.
}

void multiMatrix(const double *mA, const double *mB, double *mC,
                 int D, int filaI, int filaF) //se declara la funcion multiMatrix() que va a realizar la multiplicacion de matrices.
{
    double Suma; //se declara la variable suma que sirve como una variable acumuladora para almacenar el resultado de la suma de la  multiplicacion de los elementos de las matrices A y B (producto escalar).
    const double *pA;//Es un puntero que apunta a las filas de la matriz A.
    const double *pB;//Es un puntero que apunta a las columnas de la matriz B.

    for (int i = filaI; i < filaF; i++) {//se crea un ciclo for que va a recorrer las filas de la matriz A.
        for (int j = 0; j < D; j++) {//se crea un ciclo for que va a recorrer las columnas de la matriz B.
            Suma = 0.0;//se inicializa la variable suma en 0.
            pA = mA + i * D;  /* inicio de la fila i de A */
            pB = mB + j;      /* inicio de la columna j de B (salto D) */
            for (int k = 0; k < D; k++, pA++, pB += D) {//se crea un ciclo for que va a recorrer los elementos de la fila i de la matriz A y la columna j de la matriz B.
                Suma += (*pA) * (*pB);//Se realiza la multiplicacion de los elementos de la fila i de la matriz A y la columna j de la matriz B y se almacena en la variable suma.
            }
            mC[i * D + j] = Suma;//se almacena el resultado de la suma en la matriz C.
        }
    }
}

void impMatrix(const double *matrix, int D){//se declara la funcion impMatrix() que va a imprimir la matriz.
    if (D < 9) { //si el tamaño de la matriz es menor a 9, entonces se imprime la matriz.
        printf("\nImpresion...\n");//se imprime un mensaje que indica que se va a imprimir la matriz.
        for (int i = 0; i < D * D; i++, matrix++) {//se crea un ciclo for que va a recorrer los elementos de la matriz.
            if (i % D == 0) printf("\n");//se imprime un salto de linea cada vez que se recorre una fila de la matriz.
            printf(" %.2f ", *matrix);//se imprime el elemento de la matriz.
        }
        printf("\n");//se imprime un salto de linea para que el resultado sea mas legible a la hora de mostrar la matriz.
    }
}

void iniMatrix(double *mA, double *mB, int D){//se declara la funcion iniMatrix() que va a inicializar las matrices A y B con valores aleatorios.
    for (int i = 0; i < D * D; i++, mA++, mB++){//se crea un ciclo for que va a recorrer los elementos de las matrices A y B.
        *mA = (double)rand() / RAND_MAX * (5.0 - 1.0);//se inicializa el elemento de la matriz A con un valor aleatorio entre 1 y 5
        *mB = (double)rand() / RAND_MAX * (9.0 - 5.0);//se inicializa el elemento de la matriz B con un valor aleatorio entre 5 y 9
    }
}