<#	
    Crea un script que le pida al usuario que introduzca una nota 
    y muestre un mensaje en base a la siguiente tabla:

    Nota	                    Puntuación
    Muy buena	                Entre 16,00 y 20,00
    Bueno	                    Entre 14,00 y 15,99
    Lo suficientemente bueno	Entre 12,00 y 13,99
    Medio	                    Entre 10,00 y 11,99
    Insuficiente	            Inferior a 10
#>

[double]$nota = Read-Host "¿Qué nota ha sacado? (La nota debe ser un número entre 0 y 20)"
switch ($nota) {
    {$_ -lt 10 }                    { Write-Host "Insuficiente" }
    {($_ -ge 10) -and ($_ -lt 12) } { Write-Host "Medio" }
    {($_ -ge 12) -and ($_ -lt 14) } { Write-Host "Lo suficientemente bueno" }
    {($_ -ge 14) -and ($_ -lt 16) } { Write-Host "Bueno" }
    {($_ -ge 16) -and ($_ -le 20) } { Write-Host "Muy buena" }
    default                         { Write-Host "La nota no está entre 0 y 20" }
}
