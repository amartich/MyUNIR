#!/bin/bash
# Crear un archivo o directorio pasado como parámetro.

me=`basename "$0"`

function crearDirectorio {
    mkdir $1
}

function crearArchivo {
    touch $1
}

function printUse {
    echo "Parámetros incorrectos."
    echo "USO: ./$me -d|-f NOMBRE"
    echo "Ejemplo: ./$me -f archivo-texto.txt"
    echo "Ejemplo: ./$me -d directorio1"
}

if [[ $1 == "-d" && $2 ]] ; then
    crearDirectorio $2
else
    if [[ $1 == "-f" && $2 ]] ; then
        crearArchivo $2
    else
        printUse
    fi
fi