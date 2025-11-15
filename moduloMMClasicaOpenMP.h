/****************************************************************************************
* Fecha:14/11/2025                                                                      *
* Autor: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas.                         *
* Programa:                                                                             *
*      Multiplicacion de Matrices algoritmo clasico                                     *
* Versión:                                                                              *
*      Paralelismo con OpenMP                                                           *
* Descripcion: Este archivo de cabecera contiene las funciones que se van a             *
*       utilizar en mmClasicaOpenMP.C                                                   *
*****************************************************************************************/


#ifndef MODULO_MM_CLASICA_OPENMP_H//se define una directiva de inclusion condicional para evitar que el archivo de cabecera se incluya mas de una vez en un mismo archivo de codigo.
#define MODULO_MM_CLASICA_OPENMP_H
//se define una constante que se utilizara para evitar que el archivo de cabecera se incluya mas de una vez en el mismo encabezado

//se declara la libreria que se va a utilizar en el programa.
#include <sys/time.h>


extern struct timeval inicio, fin; //Se declaran las variables de tiempo que se van a utilizar para medir el tiempo de ejecucion del programa.


void InicioMuestra(void);//se declara la funcion que va a inicializar el temporizador.
void FinMuestra(void);//se declara la funcion que va a detener el temporizador.

void impMatrix(double *matrix, int D);//se declara la funcion que va a imprimir la matriz.
void iniMatrix(double *m1, double *m2, int D);//se declara la funcion que va a inicializar las matrices.
void multiMatrix(double *mA, double *mB, double *mC, int D);//se declara la funcion que va a realizar la multiplicacion de matrices.

#endif//se cierra la directiva de inclusion condicional.