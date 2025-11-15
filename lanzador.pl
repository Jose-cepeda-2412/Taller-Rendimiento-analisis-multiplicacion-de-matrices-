#!/usr/bin/perl
#************************************************************************
#         		Pontificia Universidad Javeriana                          *
#     Autores: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas.   *
#     Fecha: 11/11/2025                                                 *
#     Materia: Sistemas Operativos                                      *
#     Docente: J.Corredor PhD                                           *
#     Tema: Taller de Evaluacion de Rendimiento                         *
#     Fichero: Script de automatizacion de ejecucion por lotes          *
#************************************************************************/

$Path = `pwd`;
chomp($Path);

# Nombre del ejecutable 
$Nombre_Ejecutable = "MM_ejecutable";

# Tamaños matriz
@Size_Matriz = ("500","700","900","1200","1500","1700","2000");

# Numero de hilos (hasta 12)
@Num_Hilos = (1,2,4,8,12);

# Numero de repeticiones por prueba 
$Repeticiones = 30;

foreach $size (@Size_Matriz) {
	foreach $hilo (@Num_Hilos) {

		# Archivo de salida .dat para cada combinacion
		$file = "$Path/$Nombre_Ejecutable-${size}x${size}-Hilos-${hilo}.dat";

		print "\n>>> Ejecutando tamaño=$size hilos=$hilo\n";

		# Ejecuta el programa varias veces y guarda el resultado
		for ($i = 0; $i < $Repeticiones; $i++) {
			system("$Path/$Nombre_Ejecutable $size $hilo >> $file");
		}

		print ">> Resultados guardados en: $file\n";
	}
}

print "\n*** TODAS LAS PRUEBAS FINALIZADAS CORRECTAMENTE ***\n";
