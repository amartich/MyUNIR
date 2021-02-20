<#
	Crea una secuencia de comandos que ofrezca el siguiente menú:
	Seleccionar:
	1 - Verificar la existencia de un usuario.
	2 - Conocer el UID de un usuario.
    q – Salir.
    El usuario debe introducirse utilizando una función. Su existencia debe ser verificada con otra función.
#>

function Pedir-Usuario {
    $usuario = Read-Host "Introduce el nombre de usuario: "
    return $usuario
}

function Verifica-Usuario {
    Param($usuario)
    try {
        $u = Get-LocalUser $usuario -ErrorAction Stop
    } 
    Catch  [Microsoft.PowerShell.Commands.UserNotFoundException]{
        
    }
    return $u
}

function Conocer-UID {
    Param($usuario)
    $u = Verifica-Usuario $usuario
    if ( $u ) {
        Write-Host El SID de $usuario es $u.SID
    }
    else {
        Write-Host "El usuario $usuario no existe."
    }
}

function Menu-1 {
    $usuario = Pedir-Usuario
    $u = Verifica-Usuario $usuario
    if ( $u ) {
        Write-Host "El usuario $usuario existe."
    }
    else {
        Write-Host "El usuario $usuario no existe."
    }
    pause
}
function Menu-2 {
    $usuario = Pedir-Usuario
    Conocer-UID $usuario
    pause
}

do {
    cls
    Write-Host "Seleccionar:"
    Write-Host "1 - Verificar la existencia de un usuario."
    Write-Host "2 - Conocer el UID de un usuario."
    Write-Host "q - Salir."
    $opcion = Read-Host

    switch ($opcion) {
        "1" { Menu-1 }
        "2" { Menu-2 }
        "q" { exit }
        default { Write-Host "No has seleccionado una opción disponible." }
    }
} while (1)