#!/bin/bash
# Eliminar un archivo o directorio pasado como parámetro. Debe preguntar si está seguro de llevar acabo la acción.

me=`basename "$0"`

function borrar {
    rm -r $1
}

function preguntarConsentimiento {
    local choice
    read -p "Está seguro de querer borrar el archivo $1? [s/n]: " choice
    case $choice in
        's') borrar $1 ;;
        'n') exit ;;
        *) preguntarConsentimiento $1;;
    esac
}

function printUse {
    echo "Parámetros incorrectos."
    echo "USO: ./$me NOMBRE"
    echo "Ejemplo: ./$me archivo-texto.txt"
    echo "Ejemplo: ./$me directorio"
}

if [[ $1 ]] ; then
    preguntarConsentimiento  $1    
else
    printUse
fi