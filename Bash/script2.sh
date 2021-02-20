#!/bin/bash
removeFileDirectory() {
    if [[ -d $1 ]]; then
        rmdir $1; echo "Eliminado directorio $1."
    elif [[ -f $1 ]]; then
        rm $1; echo "Eliminado archivo $1."
    else
        echo "No existe."
    fi
}

read -p "Nombre del archivo o directorio a eliminar: " name

while [[ $sure -ne "Y" ]] || [[ $sure -ne "N" ]]
do
    read -p "¿ Está seguro de eliminar $name (Y/N)? " sure
done

if [[ $sure -eq "Y" ]]; then
    removeFileDirectory $name
fi

