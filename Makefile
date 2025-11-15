#####################################################################################################
#		Pontificia Universidad Javeriana															 #
#     Autor: Santiago Hernandez Morales y Jose Jesus Cepeda Vargas.									 #
#	  Docente: J.Corredor PhD																		 #
#     Fecha: 11/11/2025																				 #
#     Materia: Sistemas Operativos																	 #
#     Tema: Taller de Evaluacion de Rendimiento														 #
#     Descripcion: El Makefile automatiza la compilacion de los programas							 #
#	  del taller de evaluacion de rendimiento (POSIX,FORK,openMp(por filas),openMP(por columnas))	 #
######################################################################################################



# se define el compilador que se va a usar (gcc)
GCC = gcc
# se define los modulos que se va a usar (para cada programa)
MOD1 = moduloMMClasicaFork
MOD2 = moduloMMClasicaPosix
MOD3 = moduloMMClasicaOpenMP
MOD4 = moduloMMFilasOpenMP
# se define las banderas que se va a usar
CFLAGS = -lm
FOPENMP = -fopenmp -O3
POSIX = -lpthread
# se define los programa posibles a compilar
PROGRAMAS = mmClasicaFork mmClasicaPosix mmClasicaOpenMP mmFilasOpenMP lanzador

# compila el programa 
mmClasicaFork:
	$(GCC) $@.c $(MOD1).c -o $@

mmClasicaPosix:
	$(GCC) $@.c $(MOD2).c -o $@ $(POSIX)

mmClasicaOpenMP:
	$(GCC) $(CFLAGS) $@.c $(MOD3).c -o $@ $(FOPENMP)

mmFilasOpenMP:
	$(GCC) $(CFLAGS) $@.c $(MOD4).c -o $@ $(FOPENMP)

lanzador:
	chmod +x lanzador.pl
#limpieza de los programas
clean:
	$(RM) $(PROGRAMAS)