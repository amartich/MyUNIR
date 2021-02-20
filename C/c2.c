#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
/**
	Un proceso padre lee una cadena de caracteres del terminal del usuario.
	Después pasa esa cadena a un proceso hijo quien la usa para crear un fichero
	e informa al proceso padre cuando lo haya creado.

	El proceso padre abre el fichero y escribe otra cadena de caracteres recibida
	por el terminal del usuario.

	Cierra el fichero y lo lee nuevamente mostrando por pantalla su contenido.
*/
char * leerCadena();
void leerFichero();

int descriptor;

void main() {
	// Pedimos la cadena en el proceso padre
	char * line = leerCadena2();	
	pid_t pid = fork();

	if ( pid == 0 ) {
		// Proceso hijo
		printf("Abrimos el documento\n");
		descriptor = creat("ejercicio-2.txt", 0666);
		write(descriptor, line, strlen(line));
		close(descriptor);
		// Finalizamos la  ejecución del proceso hijo
		_exit(0);
	}
	// Exitiendo el _exit(0) en el proceso hijo, aquí sólo llegará el proceso padre
	int status = 0;
	// Esperamos por el proceso hijo
	waitpid(pid, &status, 0);
	// En este momento el proceso hijo ya habrá acabado de ejecutarse

	// Pedimos y escribimos la segunda cadena
	line = leerCadena();
	descriptor = open("ejercicio-2.txt", O_RDWR | O_APPEND);
	write(descriptor, line, strlen(line));

	// Cerramos el archivo	
	close(descriptor);

	// Leemos el contenido del archivo
	leerFichero();
}

void leerFichero() {
	printf("Vamos a leer el archivo ejercicio-2.txt\n");	
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("ejercicio-2.txt", "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }
    fclose(fp);
    if (line)
		free(line);	
}
char * leerCadena() {
	char * line;
	char cadena[256];
	printf("Introduce la cadena: ");
	scanf("%[^\n]s", cadena);
	size_t size = snprintf(NULL, 0, "%s\n", cadena);
	line = (char*) malloc(size+1);
	snprintf(line, size+1, "%s\n", cadena);	
	return line;
}