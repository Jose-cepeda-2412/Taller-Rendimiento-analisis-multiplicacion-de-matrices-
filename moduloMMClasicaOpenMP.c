/********************************************************************
* Fecha:14/11/2025                                                  *
* Autores: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas.   *
* Docente: J.Corredor PhD.                                          *
* Programa:                                                         *
*     Multiplicacion de Matrices algoritmo clasico                  *
* Version:                                                          *
*     Paralelismo con OpenMP (implementaciones de funciones)        *
* Descripcion:                                                      *
*      Este programa implementa las funciones de multiplicacion de  *
*      matrices utilizando paralelismo con openMP, con el proposito *
*      de medir el rendimiento de esta version frente a otras       *
*      versiones de implementacion, este programa incluye funciones *
*      para inicializar matrices, imprimir matrices y medir el      *
*      tiempo de ejecucion.                                         *
*********************************************************************/

//Se declaran las bibliotecas que se van a utilizar en el programa.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include "moduloMMClasicaOpenMP.h" //se incluye el archivo de cabecera que contiene las funciones que se van a utilizar en el programa.


struct timeval inicio, fin; //se declaran las variables de tiempo que se van a utilizar para medir el tiempo de ejecucion del programa.

void InicioMuestra(){//se declara la funcion InicioMuestra() con el proposito de iniciar el temporizador de tiempo de ejecucion.
    gettimeofday(&inicio, (void *)0);//se devuelve el tiempo inicial en microsegundos.
}

void FinMuestra(){ //se declara la funcion FinMuestra() con el proposito de detener el temporizador de tiempo de ejecucion.
    gettimeofday(&fin, (void *)0); //se devuelve el tiempo final en microsegundos.
    fin.tv_usec -= inicio.tv_usec; //se calcula la diferencia de los tiempos en microsegundos.
    fin.tv_sec  -= inicio.tv_sec; //se calcula la diferencia de los tiempos en segundos.
    double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);//se calcula el tiempo total de ejecucion.
    printf("%9.0f \n", tiempo); //se imprime el tiempo total de ejecucion.
}

void impMatrix(double *matrix, int D){ //se declara la funcion impMatrix() con el proposito de imprimir las matrices.
    if(D < 9){//se verifica que el tamaño de la matriz sea menor a 9, si es asi entonces se ejectuta lo siguiente:
        printf("\n");//se imprime un salto de linea para que el resultado sea mas legible.
        for(int i=0; i<D*D; i++){//se crea un ciclo for con el proposito de recorrer los elementos de la matriz.
            if(i%D==0) printf("\n");//se imprime un salto de linea cada vez que se recorre una fila de la matriz.
            printf("%.2f ", matrix[i]);//se imprime el elemento de la matriz.
        }
        printf("\n**-----------------------------**\n");//se imprime un salto de linea para hacer que resultado sea legible.
    }
}

void iniMatrix(double *m1, double *m2, int D){ //se declara la funcion iniMatrix() con el proposito de inicializar las matrices.
    for(int i=0; i<D*D; i++, m1++, m2++){//se crea un ciclo for con el proposito de recorrer los elementos de las matrices.
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0);//se inicializa el elemento de la primera matriz con un valor entre 1 y 5
        *m2 = (double)rand()/RAND_MAX*(9.0-2.0); //se inicializa el elemento de la segunda matriz con un valor entre 2 y 9.
    }
}

void multiMatrix(double *mA, double *mB, double *mC, int D){//se declara la funcion multiMatrix() con el proposito de realizar la multiplicacion de matrices.
    double Suma, *pA, *pB;//se declaran las variables que se van a utilizar para realizar la multiplicacion de matrices.
    //se usa pragma omp parallel para crear una region paralela donde se distribuye el trabajo entre los hilos.
    #pragma omp parallel
    {
         //se utiliza pragma omp for para distribuir el trabajo entre los hilos.
        #pragma omp for
        for(int i=0; i<D; i++){ //se crea un ciclo for con el proposito de recorrer las filas de la matriz A.
            for(int j=0; j<D; j++){//se crea un ciclo for con el proposito de recorrer las columnas de la matriz B.
                pA = mA+i*D;//se inicializa el puntero pA el cual apunta a la primera entrada de la fila i de la matriz A.
                pB = mB+j; //se inicializa el puntero pB el cual apunta a la primera entrada de la columna j de la matriz B.
                Suma = 0.0; //se inicializa la variable suma en 0.
                for(int k=0; k<D; k++, pA++, pB+=D){//se crea un ciclo for con el proposito de recorrer los elementos de la fila i de A y la columna j de B.
                    Suma += *pA * *pB; //se realiza la multiplicacion de los elementos de la fila i de A y la columna j de B y se almacena en la variable suma.
                }
                mC[i*D+j] = Suma; //se almacena el resultado de la suma en la matriz C la cual es la matriz resultante de multiplicar A*B.
            }
        }
    }
}