#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

/*
int main(void){
    if (write(1, "Mensaje para la salida estandar\n", 35) != 36){
        write(2, "ERROR ESCRIBIENDO EB LA SALIDA ESTANDAR \n",44 );

        return -1;

    }
return 0;

}
*/

/*
int main(void){
    int descriptor, index;

    descriptor = creat("prueba", 06000);
        for(index = 0 ; index < 10; index++)
            write(descriptor, index, 0600);
            close(descriptor);
            exit(0);

        

}*/


int main(){
    struct stat estru;
    struct dirent *directorio;

    DIR *dire;
    int bytes =0;
    system ("clear");

    dire=opendir("."); //Abdre el directrio dirent.h
        while ((directorio=readdir(dire))!= NULL){//lee el directorio completo
        stat(directorio->d_name, &estru);
        printf("%-20s %f \n", directorio->d_name ,estru.st_size);
        bytes = bytes+estru.st_size; 

        }

    closedir(dire);
    bytes = bytes/1024;
    printf("\nTotal en KB: %d", bytes);
    exit(0);
        

}

