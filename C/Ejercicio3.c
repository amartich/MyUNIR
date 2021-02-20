#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
	Escribe un programa en C bajo Linux que busque dentro de un directorio cuya 
	ruta es proporcionada en la línea de comandos los ficheros que sean propiedad de 
	un usuario cuyo ID se pase también como un argumento del programa.
*/

int main(int argc, char *argv[]) 
{
	if ( argc != 3 ) {
		printf("Uso: Ejercicio3 PATH USERID.\n");
		printf("Ejemplo: ./Ejercicio3 /home/arturo/ 1000\n");
	} else {
		char * path = argv[1];
		int uid = atoi(argv[2]);

		struct stat estru;
		struct dirent *directorio;			
		DIR *dire;		

		// Abrimos el directorio a analizar
		dire = opendir(path);
		printf("Los archivos existentes en la ruta %s pertenecientes al usuario %d son:\n", path, uid);
		// Recorremos cada uno de los archivos que contiene el directorio		
		while ((directorio = readdir(dire)) != NULL ) {
			// Obtenemos las estadísticas del archivo y las guardamos en 'estru'
			stat( directorio->d_name, &estru);
			if ( estru.st_uid == uid ) {				
				printf("%-20s (UID: %d)\n",directorio->d_name, estru.st_uid);
			}			
		}
		// Cerramos el directorio
		closedir(dire);
	}
	return 0;
}
