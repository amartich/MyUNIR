#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
void main(){

        int a;
        int b;
        char s1[16]; // buffers para lecturas
        char s2[16]; // buffers para lecturas
        scanf("%d %d",&a,&b);

        FILE *f1;
        f1=fopen("fichero.dat","w"); //escritura

        int pid=fork();
        if (pid == 0){
                printf("Sumo dos numeros %d + %d es igual a %d \n",a,b,a+b);
                fprintf(f1,"%d\n",a+b);
        }
        else {
                wait(NULL); // espero a que acabe primer hijo
                pid=fork();
                if (pid == 0){
                        printf("Multiplico dos numeros %d * %d es igual a %d \n",a,b,a*b);
                        fprintf(f1,"%d\n",a*b);
                }
                else{

                        wait(NULL); // espero a que acabe segundo hijo
                        pid=fork();
                        if (pid == 0){
                                fclose(f1);
                                f1 = fopen("fichero.dat", "r"); // lectura
                                fgets(s1, 16, f1);
                                fgets(s2, 16, f1);
                                printf("EL contenido del fichero es:\n");
                                printf("%s%s\n", s1, s2);
                                fclose(f1);

                        }
                        wait(NULL); // espero a que acabe tercer hijo

                }
        }
}
