/**********************************************************************************************
* Fecha:14/11/2025                                                                            *
* Autores: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas.                             *
*                                                                                             *
* Programa:                                                                                   *
*      Multiplicacion de Matrices algoritmo matriz Transpuesta (Filas x Filas)                *
* Version:                                                                                    *
*      Paralelismo con OpenMP                                                                 *
* Descripcion:En este programa se implementa la multiplicacion de matrices NXN usando la      *
*             transpuesta de la segund matriz(filasxfilas), con el proposito de aprovechar    *
*             la localidad de memoria con openMP. incluye funciones para inicializar matrices,*
*             imprimir matrices y medir el tiempo de ejecucion.                               *
***********************************************************************************************/

//se declaran las bibliotecas que se van a utilizar en el programa.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include "moduloMMFilasOpenMP.h"//se incluye el archivo de cabecera que contiene las funciones que se van a utilizar en el programa.

/* Definiciones que corresponden a los 'extern' del .h */
struct timeval inicio, fin;//se declaran las variables de tiempo que se van a utilizar para medir el tiempo de ejecucion del programa.

void InicioMuestra(){ //Se declara la funcion Inicio Muestra() que va a iniciar el temporizador de tiempo de ejecucion.
    gettimeofday(&inicio, (void *)0);//gettimeofday() es una funcion que devuelve el tiempo inicial en microsegundos.
}

void FinMuestra(){//se declara la funcion FinMuestra() que va a detener el temporizador de tiempo de ejecucion.
    gettimeofday(&fin, (void *)0);// se obtiene el tiempo final en microsegundos.
    fin.tv_usec -= inicio.tv_usec;//se calcula la diferencia de tiempos en microsegundos.
    fin.tv_sec  -= inicio.tv_sec;//se calcula la diferencia de tiempos en segundos.
    double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);//la variable tiempo representa el tiempo total de ejecucion en microsegundos.
    printf("%9.0f \n", tiempo);//se imprime el tiempo de ejecucion en microsegundos.
}

void impMatrix(double *matrix, int D, int t){
    int aux = 0;//se declara la variable aux que representa el numero de columnas de la matriz.
    if (D < 6)//se verifica que el tamaño de la matriz sea menor a 6, si es asi esntonces se ejecuta lo siguiente:
        switch (t){//se crea un switch que va a determinar el tipo de impresion de la matriz
            case 0: /* por filas */
                for (int i = 0; i < D*D; i++){//se genera un ciclo for para recorrer los elementos de la matriz.
                    if (i % D == 0) printf("\n");//se imprime un salto de lines si el indice del elemento es divisible entre el tamaño de la matriz
                    printf("%.2f ", matrix[i]);//se imprime el elemento de la matriz
                }
                printf("\n  - \n");//se imprime un salto de linea para que el resultado sea mas legible a la hora de mostrar la matriz.
                break;
            case 1: /* por columnas (transpuesta visual) */
                while (aux < D){//se crea un ciclo while que va a recorrer las columnas de la matriz.
                    for (int i = aux; i < D*D; i += D)//se crea im ciclo for que va a recorrer las fila de la matriz
                        printf("%.2f ", matrix[i]);//se imprime el elemento de la matriz.
                    aux++;//se incrementa el valor aux en 1 para que wl ciclo while pueda terminar.
                    printf("\n");//se imprime un salto de linea para que el resultado de la matriz sea mas legible
                }
                printf("\n  - \n");////se imprime otro salto de linea para que el resultado de la matriz sea mas legible
                break;//se cierra el switch usando un break.
            default://se crea un default si no se cumple ninguna de las condiciones anteriores.
                printf("Sin tipo de impresion\n");//se imprime este mensaje si no se cumple ninguna de las condiciones anteriores.
        }
}

void iniMatrix(double *m1, double *m2, int D){//se declara la funcion iniMatrix() con el proposito de inicializar las matrices A y B.
    for (int i = 0; i < D*D; i++, m1++, m2++){//se crea un ciclo for para recorrer los elementos de las matrices.
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0);//se inicializa el elemento de la primera matriz con un valor ente 1 y 5.
        *m2 = (double)rand()/RAND_MAX*(9.0-5.0);//se inicializa el elemento de la segunda matriz con un valor entre 5 y 9.
    }
}

void multiMatrixTrans(double *mA, double *mB, double *mC, int D){//se declara la funcion multiMatrixTrans() con el proposito de realizar la multiplicacion de matrices.
    double Suma, *pA, *pB;//se declaran las variables suma, PA y PB. donde suma almacena el resultado de la multiplicacion de los elementos de las matrices A y B, PA es un puntero que apunta a las filas de A y PB es un puntero que a puntra a las filas de B.
    //se crea una region con openMP para distribuir el trabajo entre los hilos.
    #pragma omp parallel 
    {
         //#programa omp for se utiliza para distribuir el trabajo entre lops hilos.
        #pragma omp for
        for (int i = 0; i < D; i++){// se crea un ciclo for para recorrer las filas de la matriz A.
            for (int j = 0; j < D; j++){//se crea un ciclo for para recorrer las filas de la matriz B.
                pA = mA + i*D;   /* fila i de A */
                pB = mB + j*D;   /* fila j de B (equivale a col j de B^T) */
                Suma = 0.0; //se inicializa la variable suma en 0.
                for (int k = 0; k < D; k++, pA++, pB++){ //se crea un ciclo for para recorrer los elementos de la fila i de la matriz A y la fila j de la matriz B.
                    Suma += *pA * *pB; //se realiza la multiplicacion de los elementos de la fila i de la matriz A y la fila j de la matriz B y se almacena en la variable suma.
                }
                mC[i*D + j] = Suma;//se almacena el resultado de la suma en la matriz C.
            }
        }
    }
}