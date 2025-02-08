#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

int main() {
    Lista* pacientes = carregar_bd();
    if (pacientes == NULL) {
        fprintf(stderr, "Erro ao carregar lista de pacientes.\n");
        return 1;
    }

    menu(pacientes);

    if (pacientes != NULL) {
        liberar_lista(pacientes);
    }

    return 0;
}