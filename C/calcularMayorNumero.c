#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    float valores[4];
    int i;
    float size = sizeof(valores)/sizeof(float);
        for(i=0 ; i <size; i++){
            printf("Ingrese Numero %d\n", (i+1));
            scanf("%f", &valores[i]);


        }

        float aux = valores[0];
        for(i=1 ; i < size ; i++){
            if(valores[i]>aux){

                aux=valores[i];


            }

        }

        printf("\nEl mayor es: %f\n", aux);


}