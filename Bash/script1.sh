#!/bin/bash
createFileDirectory() {
    case $2 in
        1)
            mkdir $1
            echo "Directorio $1 creado"
        ;;
        2)
            touch $1
            echo "Archivo $1 creado"
        ;;
        *)
            echo "No es ni un archivo ni un directorio"
        ;;
    esac
}

read -p "Nombre del archivo o directorio: " name
read -p "¿ Desea crear un directorio (1) o un fichero (2) ? " type

createFileDirectory $name $type

