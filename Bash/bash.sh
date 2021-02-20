#!/bin/bash


# Escribir un script para UNIX que muestre un menú con las siguientes tres opciones:
#
# - Guardar un informe del contenido del directorio actual. Especificando si el archivo es un directorio, en caso de no serlo debe indicar si es de lectura o no.
# - Obtener el tamaño ocupado por un determinado directorio y sus ficheros y subdirectorios.
# - Salir
#
# El usuario debe seleccionar una de las opciones. El script debe implementar cada una de las opciones usando funciones.

show_menu(){
    clear
    echo "~~~~~~~~~~~~~~~~~~~~~" 
    echo "  MENU-UNIR" 
    echo "~~~~~~~~~~~~~~~~~~~~~"
    echo "1. Guardar informe del contenido del directorio actual."
    echo "2. Obtener espacio ocupado por un determinado directorio y sus ficheros y subdirectorios."
    echo "0. Salir"
}

read_options(){
    local choice
    read -p "Elija una Opcion [0 - 2]: " choice
    case $choice in
        1) opt1 ;;
        2) opt2 ;;
        0) salir ;;
        *) read_options ;;
    esac
}

opt1(){
    clear
    echo -e "Guardar informe del contenido del directorio actual.\n"
    echo "Informe de contenido del directorio actual" > informe.txt
    ls -laF | tail -n +2 | while read line; do
        filename=$(echo $line | awk 'NF{ print $NF }')
        directoryFlag=$(echo ${line:0:1})
        writeFlagOwner=$(echo ${line:1:1})
        writeFlagGroup=$(echo ${line:4:1})
        writeFlagAll=$(echo ${line:7:1})
        if [[ $directoryFlag == "d" ]]; then
            echo "$filename es un directorio" >> informe.txt
        else
            if [[ $writeFlagOwner == "r" || $writeFlagGroup == "r" || $writeFlagAll == "r" ]]; then
                echo "$filename es un archivo de lectura" >> informe.txt
            else
                echo "$filename no es un archivo de lectura" >> informe.txt
            fi
        fi
    done
    pause
}
opt1-tratarLinea() {
    echo "linea $*\n"
}
opt2(){
    clear
    echo -e "Obtener espacio ocupado por un determinado directorio y sus ficheros y subdirectorios.\n"
    local folderPath
    read -p "Ingrese el Path:" folderPath
    local size
    size=$(du $folterPath -h 2>/dev/null | tail -n 1 | awk '{print($1)}')
    echo -e "Espacio ocupado: $size\n"
    pause
}
salir() {
    exit 0
}
pause(){
  read -p "Pulsa [Enter] para continuar..."
}

while true
    do
        show_menu
        read_options
    done