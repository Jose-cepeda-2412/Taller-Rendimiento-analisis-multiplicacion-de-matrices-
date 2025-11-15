/************************************************************************************
*  Autores: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas                   *
*  Fecha: 14/11/2025
*  Docente: J.Corredor PhD                                                          *
*  Programa: Multiplicación de matrices (algoritmo clasico)                         *
*  Version:  Paralelismo con procesos fork (interfaces del modulo)                  *
*  Descripcion: Este archivo de cabecera contiene las funciones que                 *
*  se van a utilizar en mmClasicaFork.c                                             *
*************************************************************************************/

#ifndef __MODULOMMCLASICAFORK_H //se define una directiva de inclusion con el proposito de evitar que el archivo de cabecera se incluya mas de una vez.
#define __MODULOMMCLASICAFORK_H
//se define una constante que tiene como proposito evitar que el archivo de cabecera se incluta mas de una vez.

//se declara las bibliotecas que se van a utilizar en el programa.
#include <sys/time.h>


void InicioMuestra(void);//se declara la funcion que va a iniciar el temporizador de tiempo de ejecucion.
void FinMuestra(void);//se declara la funcion que va a detener el temporizador en tiempo de ejecucion.

void multiMatrix(const double *mA, const double *mB, double *mC,int D, int filaI, int filaF); //se declara la funcion que va a realizar la multiplicacion de matrices.


void impMatrix(const double *matrix, int D); //se declara la funcion que va a imprimir la matriz.
void iniMatrix(double *mA, double *mB, int D);//se declara la funcion que va a inicializar las matrices.


#endif //se cierra la directiva de inclusion.