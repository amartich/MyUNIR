#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
/*
	Escribe un programa en C bajo Linux que cree un fichero de texto plano que liste el 
	nombre, el tamaño y la fecha de la última modificación 
	de todos los ficheros que haya en un directorio cuya ruta es proporcionada en la línea 
	de comandos. No debe entrar en los subdirectorios.
*/
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("El programa debe ejecutarse pasando como parámetro la ruta.\n");
	}
	else
	{
		// Guardamos el path que viene en el parámetro en una variable
		char *path = argv[1];

		// Creamos el fichero donde se van a escribir las estadisticas
		int descriptor = creat("estadisticas.txt", 600);

		struct stat estru;
		struct dirent *directorio;
		DIR *dire;
		char fUltimaModificacion[12];
		char *line;
		size_t sz;

		// Abrimos el directorio a analizar
		dire = opendir(path);

		// Recorremos cada uno de los archivos que contiene el directorio
		while ((directorio = readdir(dire)) != NULL)
		{
			// Obtenemos las estadísticas del archivo y las guardamos en 'estru'
			stat(directorio->d_name, &estru);
			// Guardamos la fecha de última modificación en la variable 'fUltimaModificacion'
			strftime(fUltimaModificacion, 12, "%Y-%m-%d", localtime(&estru.st_mtime));
			// Obtenemos el tamaño del texto que vamos a querer escribir en el fichero de estadísticas.
			sz = snprintf(NULL, 0, "%-20s %ld %s\n", directorio->d_name, estru.st_size, fUltimaModificacion);
			line = (char *)malloc(sz + 1);
			// Guardamos en la variable 'line' la linea que queremos escribir
			snprintf(line, sz + 1, "%-20s %ld %s\n", directorio->d_name, estru.st_size, fUltimaModificacion);
			// Escribimos la linea en el fichero de estadísticas.
			write(descriptor, line, sz);
		}
		// Cerramos el directorio
		closedir(dire);

		// Cerramos el fichero
		close(descriptor);
	}
	return 0;
}