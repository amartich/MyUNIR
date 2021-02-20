<#
Dado un número del 1 al 5 solicitado al usuario lo convierta en palabras. Por ejemplo, si el usuario digita 1 por pantalla sale UNO.
#>

function preguntar-numero {
    [double]$numero = Read-Host "Dime un número del 1 al 5"
    if ( ($numero -ge 1) -and ($numero -le 5) ) {
        traducir-resultado($numero)
    } else {
        Write-Host "El número debe estar entre 1 y 5"
        preguntar-numero
    }
}
function traducir-resultado($numero) {
    switch($numero) {
        {$_ -eq 1 } { Write-host "UNO" }
        {$_ -eq 2 } { Write-host "DOS" }
        {$_ -eq 3 } { Write-host "TRES" }
        {$_ -eq 4 } { Write-host "CUATRO" }
        {$_ -eq 5 } { Write-host "CINCO" }
        
    }
}

preguntar-numero