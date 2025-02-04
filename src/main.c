#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main() {
    Paciente* novo_paciente = criar_paciente(1, "123.456.789-09", "César", 24, "2025-02-03");
    Paciente* novo_paciente3 = criar_paciente(1, "606.184.184-15", "César Augusto", 24, "2025-02-03");
    Lista* nova_lista = criar_lista();
    // imprimir_paciente(novo_paciente);
    inserir_paciente(nova_lista, novo_paciente);
    Paciente* novo_paciente2 = criar_paciente(2, "154.701.577-25", "João", 24, "2025-02-03");
    inserir_paciente(nova_lista, novo_paciente2);
    inserir_paciente(nova_lista, novo_paciente3);
    // imprimir_pacientes(nova_lista);
    // liberar_paciente(novo_paciente);
    // buscar_por_nome(nova_lista, "César");
    buscar_por_cpf(nova_lista, "123.456.789-09");
    liberar_lista(nova_lista);

    return 0;
}