<#
Dado un número solicitado al usuario genere la tabla de multiplicar del número hasta 20.
#>

function preguntar-numero {
    [double]$numero = Read-Host "Dime el número del cuál quieres que calcule su tabla de multiplicar"
    pintar-tabla-multiplicar($numero)
}

function pintar-tabla-multiplicar($numero) {
    for ( $i = 1 ; $i -le 20 ; $i++ ) {
        Write-Host "$numero x $i = "($numero*$i)
    }
}

preguntar-numero