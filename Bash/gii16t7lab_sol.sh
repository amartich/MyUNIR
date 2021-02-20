#!/bin/bash

#LABORATORIO 1: Programacion de scripts en Linux

#Escribir un script en bash que muestre cada cierto tiempo un menú en el que se puedan obtener al menos las siguientes informaciones sobre el sistema:

		#Obtener el espacio libre del disco
		#Obtener el tamaño ocupado por un determinado directorio y sus ficheros y subdirectorios
		#Obtener el uso del procesador
		#Obtener el número de usuarios conectados
		#Obtener el número de usuarios conectados desde la última vez que se preguntó.

function menu {

        echo "a. Obtener el espacio libre del disco"
        echo "b. Obtener el tamaño ocupado por un determinado directorio y sus ficheros y subdirectorios"
        echo "c. Obtener el uso del procesador"
        echo "d. Obtener el número de usuarios conectados"
        echo "e. Obtener el número de usuarios conectados desde la última vez que se preguntó"
	


        read num_menu
        case $num_menu in 

                
	a)
               	echo "Ha pulsado 1 Obtener el espacio libre en disco"
               	df -h #Esta consulta nos muestra el espacio usado y el libre de nuestras particiones

	             # Ahora vamos a calcular el procentaje de espacio libre que queda del disco.
			
		usado=0
                for i in $(df -k | awk '{print $3}' | grep -v "Used"); do usado=$(( $i + usado )); done

                libre=0
                for i in $(df -k | awk '{print $4}' | grep -v "Avail"); do libre=$(( $i + libre )); done

                total=$(( $usado + $libre  ))
                percFree=$(( $libre * 100 / $total ))
		echo "El disco esta libre en un $percFree %";;
                        
                        
         b)
                echo "Ha pulsado 2 Obtener el tamaño ocupado por un determinado directorio y sus ficheros y subdirectorios"
                echo "Escriba el /directorio a analizar: " # Pedimos al usuario que escriba la ruta del directorio o carpeta
		read directorio #La aplicacion lee el directorio señalado
		echo "su tamaño es:" $(du -h --max-depth=0 $directorio);; #Muestra su tamaño y el nombre del directorio
                        
         c)
                echo "Ha pulsado 3 Obtener el uso del procesador"
                top -n1 | grep "Cpu(s)" | awk '{ print $2 "%" }';; 
			
         d)
                echo "Ha pulsado 4 Obtener el número de usuarios conectados" 
                who -q ;;  #muestra los nombres de cuenta y el numero de usuarios conectados

         e)
                echo "Ha pulsado 5 Obtener el número de usuarios conectados desde la última vez que se preguntó"
		#Calcula la diferencia entre los usuarios que estaban la ultima vez y los que hay ahora.
                if [ $usuarios ]; then echo ok > /dev/null ; else usuarios=0; export usuarios ;fi
                echo $(( $(who | grep -c "") - $usuarios ))
                usuarios=$(who | grep -c "");;
         *) 
                echo "La opción no existe en el menú"
        esac

        sleep 2
        
clear
        
menu

}
menu
~     
