
$numero = Read-Host "Digite un numero"
$numero = [math]::Pow($numero , $numero)

$division = $numero % 2

if($division -eq 0 ){
    write "El numero es par"

}else{
    write "El numero es impar"
}
