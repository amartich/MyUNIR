#!/bin/bash

##
#Script de un menu en BASH, actividad 2 SOA, UNIR : 
#Anyel Martich
##
nombre_host=$(hostname)


function espacio_disco(){
#obtener el espacio libre del disco
	echo ""
	echo -e "\e[32m El espacio disponible en disco en:  ${nombre_host} es: "
	echo ""
	df -h /dev/sda* --output=source,fstype,size,used,avail,pcent
	echo""

}

function tamano_directorio(){
#obtener el tamano ocupado por un directorio determinado y sus ficheros 
#y subdirectorios
	echo ""
	read -p "Introdusca el directorio: ej: /etc, /var etc... o, presione <ENTER> para mostrar el Dir actual:" dir
	if [ -z "$dir" ];
		then
		var=$(pwd)
		echo -e "\e[32m El tamano del directeorio $var es"
		du -h
	else
	echo -e "\e[32m El tamano del directorio $dir y todos sus sub-directorios es: "
	sudo du -shc $dir/*
	fi
	echo""
}

function uso_procesador(){
#obtener el uso del procesador
	
	echo ""
	echo -e "\e[32m El uso actual del procesador en ${nombre_host} es: "
	#comando para verificar uso del procesador
	top -n 2
	sleep 2s
	echo ""
	echo -e "\e[32m===Mas informacion sobre el CPU==="
	echo ""
	cat /proc/stat
	echo " "
	echo -e "\e[32m==un poco mas de informacion=="
	echo " "
	ps 
	echo""
}

function usuarios_conectados(){
#obtener el numero de usuarios connectados
	#echo "El el numero de usuarios conectados actualmente en  es: "
	echo ""
	#comando para verificar el numero de usuarios connectados
	uconn=$(ps -eaho user | sort -u | wc -l)
	echo -e "\e[32m Hay: $uconn :usuarios conectados en ${nombre_host}"
	echo""
	users=$(ps -eaho user | sort -u)
	echo -e "\e[32m Los usuaruos son:" $users
	 
	 DIR=/home/scripts
	 if [ ! -d "$DIR" ] ; then
		echo ""
		echo -e "\033[0;31m $DIR no existe"
		sleep 2
		echo -e "\e[32m Creando directorio $DIR..."
		sudo mkdir -p /home/scripts ;
		sudo chmod 777 /home/scripts ;
	fi;
	
	 ps -eaho user | sort -u | wc -l  > /home/scripts/lastusers.txt
	 date +%D  >> /home/scripts/lastusers.txt
	
}
function ultimos_usuarios(){
#obtener el numero de usuarios connectados desde la ultima vez que se pregunto
	echo ""
	#echo "El numero de usuarios conectados la ultima vez en ${nombre_host} es: "
	#cat /home/amartich/Documents/lastusers.txt
	echo -e "\e[32m Usuarios conectados a ${nombre_host} la ultima vez son:"
	echo ""
	INPUT="/home/scripts/lastusers.txt"
	
	if [[ ! -f "$INPUT" ]]; then
		echo ""
		echo "El archivo $INPUT  no existe, favor ejecutar la opcion #4"
		echo ""
	fi
	
	while IFS= read -r f1
		do
		echo -e "\e[32m Total Usuarios y Fecha de la ejecucion:" $f1
		#printf 'Usuario: %s\n Fecha: %s,\n' "$f1"
		#echo $f1
		done < "$INPUT"
	echo""

}

function todos(){
espacio_disco
tamano_directorio
uso_procesador
usuarios_conectados
ultimos_usuarios
}

#
#variable colores
#
verde='\e[32m'
azul='\e[34m'
rojo='\033[0;31m'
limpiar='\e[0m'
#

colorVerde(){
	echo -ne $verde$1$limpiar
}

colorAzul(){
	echo -ne $azul$1$limpiar
}

colorRojo(){
	echo -ne $rojo$1$limpiar
}



menu(){

echo ""
echo "==================================="
echo -ne $(colorAzul 'B A S H _M e n u - S O A')
echo""
echo -ne $(colorRojo 'U N I R')
echo""
echo -ne $(colorVerde 'Anyel Martich')
echo""
echo "==================================="
echo ""
echo -ne "
$(colorVerde '1') Comprobar espacio en disco
$(colorVerde '2') Obtener tamano directorio y subdirectorios
$(colorVerde '3') Obtener uso del procesador
$(colorVerde '4') Numero de usuarios conectados
$(colorVerde '5') Numero de usuarios conectados desde la ultima vez que se pregunto
$(colorVerde '6') Verificar todos
$(colorVerde '0') Salir
$(colorAzul 'Elegir Opcion:')
" 
read a
	
	case $a in
	1) espacio_disco ; menu ;;
	2) tamano_directorio; menu ;;
	3) uso_procesador; menu ;;
	4) usuarios_conectados; menu ;;
	5) ultimos_usuarios; menu ;;
	6) todos; menu;;
0) exit 0 ;;
*) echo -ne $(colorRojo "La Opcion no es Valida.") $limpiar; comandoNovalido ;;
	
	esac
	
}
#llamar funcion menu
menu
