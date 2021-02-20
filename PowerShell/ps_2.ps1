function Get-MutiplicationTable{
    param([int]$number)
    #El % es el alias para foreach
    0..20 | % {Write-Host $number ' x ' $_ ' = ' ($number * $_ )}
}

$number = Read-Host "Introduce un numero para mostrar la tabla de multiplicar hasta 20: "

Get-MutiplicationTable $number