#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/**
	Un proceso padre que recorra un directorio, cuya ruta se pasa como parámetro,
	y que escriba en un fichero de texto los nombres de los ficheros que vaya 
	encontrando	que hayan sido modificados hace cinco horas y además les quite el
	permiso de escritura.

	Cada vez que el proceso se encuentre con un subdirectorio se creará un proceso
	hijo para que se ocupe de hacer lo mismo en el subddirectorio recursivamente. El 
	proceso padre tiene que esperar	a que todos los hijos terminen de ejecutarse.

	No importa que la salida en el fichero donde escriben los procesos padre e hijos 
	no quede ordenada
*/
void procesaDirectorio(const char * path);
int isDirectory(const char *path);

int descriptor;

int main(int argc, char * args[]) {
	// Comprobamos que nos llegue el parámetro con el path, en caso contrario, imprimimos aviso, y cerramos.
	if ( argc != 2 ) {
		printf("Modo de uso: ./c1 PATH\n");
		exit(0);
	}

	

	char * path = args[1];
	// Abrimos el fichero de estadisticas.txt donde escribiremos
	descriptor = creat("estadisticas.txt", 0666);

	// Llamamos a la función recursiva
	procesaDirectorio(path);	

	// En este punto, el programa habrá acabado, tanto él como todos sus hijos.
	printf("El programa ha acabado\n");
	exit(0);
}

void procesaDirectorio(const char * path) {
	printf("Procesando '%s'\n", path);
	// Instanciamos las variables necesarias
	DIR * dire;
	struct dirent *directorio;
	size_t size;
	char * line;

	// Abrimos el path que nos llega como parámetro
	dire = opendir(path);

	// Recorremos los archivos del path
	while ((directorio = readdir(dire)) != NULL ) {
		// Generamos una variable que contiene el path completo del archivo, para poder identificar el archivo
		char fullPath[256];
		strcpy(fullPath, path);
		strcat(fullPath, directorio->d_name);	

		// Si el archivo que estamos revisando es el que hace referencia al directorio actual, o al parent, los saltamos.
		if ( strcmp(directorio->d_name, ".") && strcmp(directorio->d_name, "..") ) {
			// Si el archivo que estamos revisando es un directorio, debemos crear un fork y procesar dicho directorio. En caso contrario, debemos
			// revisar si debemos pintar información del archivo y quitarle permisos de escritura.
			if ( isDirectory(fullPath) != 0 ) {
				// Al ser un directorio, concatenamos un / al final del fullPath para cuando hagamos la llamada a procesar
				strcat(fullPath, "/");
				// Creamos un hilo nuevo
				pid_t pfork = fork();
				if ( pfork == 0 ) {
					// Si es el hilo hijo, procesamos el directorio
					procesaDirectorio(fullPath);
				} else {
					// Si es el hilo padre, esperamos hasta que termine el hilo hijo
					int status = 0;
					waitpid(pfork, &status, 0);
					// Y finalizamos la ejecución del hilo padre.
					_exit(0);
				}
			} else {
				// Al ser un archivo, debemos obtener sus stats para saber si se modificó hace más de 5 horas.
				struct stat estru;
				stat(fullPath, &estru);
				// En min nos guardamos el timestamp actual, y le restamos las 5 horas
				int min = time(NULL);
				min = min - 5 * 60 * 60;
				// Si el tiempo de modificación del archivo, es de hace menos de 5 horas:
				if ( estru.st_mtime > min ) {
					// Debemos setear la cadena que queremos escribir en el archivo estadisticas.txt en una variable primero para poder obtener su tamaño,
					// ya que es necesario en la llamada write
					size = snprintf(NULL, 0, "%s\n", fullPath);
					line = (char*) malloc(size+1);
					snprintf(line, size+1, "%s\n", fullPath);	
					// Escribimos la linea con el fullPath del fichero, y un retorno de carro al final.
					write(descriptor, line, size);
					// Obtenemos los permisos que tiene actualmente el fichero
					mode_t mode = estru.st_mode;
					// Le quitamos el permiso de escritura del usuario
					mode &= ~(S_IWRITE);
					// Le quitamos el permiso de escritura del grupo
					mode &= ~(S_IWGRP);
					// Le quitamos el permiso de escritura de ALL.
					mode &= ~(S_IWOTH);		
					// Le actualizamos los permisos								
					chmod(fullPath, mode);
				}			

			}
		}
		
	}
	printf("FIN Procesando '%s'\n", path);
}

int isDirectory(const char *path) {
	struct stat statbuf;
	if (stat(path, &statbuf) != 0)
		return 0;
	return S_ISDIR(statbuf.st_mode);
}