#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define WRITE 1
#define READ 0

int main(int argc, char *argv[])
{
    /**
     * 2. Tenemos cinco filósofos sentados a una mesa. Solamente hay un 
     * palillo entre cada dos. Para comer, un filósofo debe tomar los dos 
     * palillos que tiene uno a su izquierda y otro a su derecha cuando estén 
     * libres. Cuando termine de comer debe dejar libres los dos palillos para 
     * sus compañeros. Lo que se busca es que ningún comensal se muera de hambre. 
     */

    /**
     * Resolucion:
     * Cada palillo se representa con una tuberia y cada filosofo con un proceso. 
     * 5 procesos (filosofos) y 5 tuberias (palillos). 
     * 
     * Cada filosofo solo tiene potestad sobre su palillo izquierdo, el cual 
     * bloquea cuando intenta comer, comprueba si esta libre el de su derecha, si 
     * esta libre come, si no esta libre, libera el suyo para que otro pueda comer.
     */

    // crea los 5 palillos
    printf("Odin: Crear palillos.\n");
    int palillo[5][2];
    for (size_t i = 0; i < 5; i++)
        pipe(palillo[i]);

    int identidad; // valor de indice que identifica cada proceso

    int pid_padre = getppid();

    // crear procesos hijos
    printf("Odin: El padre de todos crea los filosofos.\n");
    int pid_hijo[5];
    int pid;
    for (size_t i = 0; i < 5; i++)
        if (pid_padre == getppid()) // solo entra Odin - El padre de todos
        {
            pid = fork();
            if (pid == 0)
                // Lo ejecuta Hijo
                identidad = i;
            else
                // Lo ejecuta Padre
                pid_hijo[i] = pid;
        }

    // tratar de comer 100 veces - solo filosofos
    int libre = -1;
    if (pid == 0)
    {
        int veces = 0;
        int dch;
        int mi_pid = getpid();
        printf("Filosofo %d Esperando para comer...\n", identidad);
        while (veces <= 100)
        {
            // ocupa su palillo
            write(palillo[identidad][WRITE], &identidad, sizeof(int));
            // lee el palillo de su vecino
            read(palillo[(identidad + 1) % 5][READ], &dch, sizeof(int));
            if (dch == libre)
            {
                // si esta libre el de su derecha come una vez
                printf("Filosofo %d COMIENDO. Contador:%d\n", identidad, veces);
                veces++;
            }
            else
            {
                printf("Filosofo %d Esperando a: Filosofo %d\n", identidad, dch);
            }
            // libera su palillo para que pueda comoer otro
            write(palillo[identidad][WRITE], &libre, sizeof(int));
        }
        printf("Filosofo %d SACIADO!!!\n", identidad);
        exit(0);
    }

    // Liberar palillos
    for (size_t i = 0; i < 5; i++)
    {
        printf("Odin: Liberar palillo %ld\n", i);
        write(palillo[i][WRITE], &libre, sizeof(int));
    }
    // Padre espera a que los filosofos terminen de comer
    int estado;
    for (size_t i = 0; i < 5; i++)
        waitpid(pid_hijo[i], &estado, 0);

    printf("\nOdin: No hay hambre en el sistema :D\n");

    return 0;
}
