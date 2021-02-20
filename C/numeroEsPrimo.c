#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int numero = 0;
    printf("Digite un Numero");
    scanf("%d", &numero);

    
int cant_divisores = 0;
    int div = 1;

    
do{

        int result = numero % div;

        if (result == 0){
        cant_divisores++;
        div++;

        }

    }  while(cant_divisores <= 2 && div <= numero);


            if(cant_divisores == 2){
                printf("el numero es primo\n");

            } else{
                    printf("El numero no es primo\n");

                }

}


