#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void escribeFichero(int resultado, char* cadena);
int suma(int int1, int int2);
int multiplica(int int1, int int2);
void leeFichero();

int main(int argc, char const *argv[])
{
    int entero1;
    int entero2;
    char cadena[20];
    int pid1;
    int pid2;
    int pid3;
    int resultado;
    //proceso padre pide dos numeros por teclado
    printf("Introduzca un numero \n");
    scanf("%s", cadena);
    entero1 = atoi(cadena);    
    printf("Introduzca otro numero \n");
    scanf("%s", cadena);    
    entero2 = atoi(cadena);

    //Creamos el hijo 1. Encargado de realizar en la suma y escribir en fichero
    pid1 = fork();
    int status1;
    if(pid1 == 0){
        printf("Proceso hijo 1. Suma \n");
        resultado = suma(entero1, entero2);
        char* cadena="suma";
        escribeFichero(resultado, cadena);
        exit(0);
    }
    //El padre esperara a que el hijo 1 termine
    waitpid(pid1, &status1, 0);

    //Creamos el hijo 2. Encargado de realizar en la multiplicacion y escribir en fichero
    pid2 = fork();
    int status2;
    if(pid2 == 0){
        printf("Proceso hijo 2. Multiplica \n");
        resultado = multiplica(entero1, entero2);
        char* cadena="multiplicacion";
        escribeFichero(resultado, cadena);
        exit(0);
    }
    //El padre esperara a que el hijo 2 termine
    waitpid(pid2, &status2, 0);

    //Creamos el hijo 3. Encargado de leer y mostrar el fichero
    pid3 = fork();
    int status3;
    if(pid3 == 0){
        printf("Proceso hijo 3. Lee fichero \n");
        resultado = multiplica(entero1, entero2);
        leeFichero();        
        exit(0);
    }
    //El padre esperara a que el hijo 3 termine
    waitpid(pid3, &status3, 0);
    //Retornamos 0 tras la correcta ejecucion
    return 0;
}

/**
 * Metodo encargado de escribir en el fichero el resultado de cada operacion
 * */
void escribeFichero(int resultado, char* cadena){
    FILE * archivo;   
    archivo = fopen("resultado.dat", "a");
    fprintf(archivo, "Resultado de la %s: %i \n", cadena, resultado);
    fclose(archivo);
}

/**
 * Metodo encargado de leer el fichero y mostrarlo por pantalla
 */
void leeFichero(){
    FILE * archivo;   
    char cadena[500];
    archivo = fopen("resultado.dat", "r");
    fread(cadena, strlen(cadena)+1, 100, archivo);
    printf("%s \n",cadena);    
    fclose(archivo);
}

//Metodo que realiza la suma de dos enteros
int suma(int int1, int int2){
    return int1+int2;
}
//Metodo que realiza la multiplicacion de dos enteros
int multiplica(int int1, int int2){
    return int1*int2;
}
