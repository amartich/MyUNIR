<#
	Crea una secuencia de comandos para calcular el número de archivos estándar, 
    subdirectorios y ejecutables de un directorio que se pasará como parámetro.
#>

function Contar-Tipo {
    Param($ruta) 
    $items = Get-ChildItem -Path $ruta
    $directorios = 0
    $ejecutables = 0
    $estandar = 0

    foreach ($i in $items) {
        if ( $i.PSIsContainer ) {
            $directorios = $directorios + 1
        } else {
            if ( $i.Name -ilike "*.exe" ) {
                $ejecutables = $ejecutables + 1
            } else {
                $estandar = $estandar + 1
            }
        }
    }
    Write-Host "Directorios: $directorios"
    Write-Host "Ejecutables: $ejecutables"
    Write-Host "Estándar: $estandar"
}
$ruta = Read-Host "¿De qué directorio quieres realizar la cuenta de archivos?"
Contar-Tipo $ruta
#Contar-Tipo "C:\*\"