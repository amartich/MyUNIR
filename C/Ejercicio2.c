#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
/*
	Escribe un programa en C bajo Linux que busque dentro de un directorio 
	cuya ruta es proporcionada en la línea de comandos todos los ficheros cuyo 
	tamaño esté comprendido entre dos valores que se pasen también como argumentos 
	del programa.
*/

int main(int argc, char *argv[]) 
{
	if ( argc != 4 ) {
		printf("Uso: Ejercicio2 PATH tam_min tam_max.\n");
	} else {
		char * path = argv[1];
		int tam_min = atoi(argv[2]);
		int tam_max = atoi(argv[3]);

		struct stat estru;
		struct dirent *directorio;			
		DIR *dire;		

		// Abrimos el directorio a analizar
		dire = opendir(path);
		printf("Los archivos existentes en la ruta %s con tamaño comprendido entre %d y %d son:\n", path, tam_min, tam_max);
		// Recorremos cada uno de los archivos que contiene el directorio		
		while ((directorio = readdir(dire)) != NULL ) {
			// Obtenemos las estadísticas del archivo y las guardamos en 'estru'
			stat( directorio->d_name, &estru);
			if ( estru.st_size > tam_min && estru.st_size < tam_max ) {
				printf("%-20s (tam: %ld)\n", directorio->d_name, estru.st_size);
			}
		}
		// Cerramos el directorio
		closedir(dire);
	}
	return 0;
}
