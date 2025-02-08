#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

int main(void) {
    Lista *lista_de_pacientes = carregar_bd();
    if (lista_de_pacientes == NULL) {
        fprintf(stderr, "Erro ao carregar lista de pacientes.\n");
        return EXIT_FAILURE;
    }

    menu(lista_de_pacientes);

    if (lista_de_pacientes != NULL) {
        liberar_lista(lista_de_pacientes);
    }
    return EXIT_SUCCESS;
}
