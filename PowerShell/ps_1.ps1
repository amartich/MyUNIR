function Get-NumberToString{
    param([string]$number)
    
    $result = switch($number){
        1 { 'Uno' }
        2 { 'Dos' }
        3 { 'Tres' }
        4 { 'Cuatro' }
        5 { 'Cinco' }
        default { 'No es un numero del 1 al 5.'}
    }

    Write-Host $result

}

$number = Read-Host "Introduce un numero del 1 al 5: "

Get-NumberToString $number