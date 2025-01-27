#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

Paciente* criar_paciente(int id, const char* cpf, const char* nome, int idade,
const char* data_cadastro) {
    Paciente* paciente = (Paciente*)malloc(sizeof(Paciente));
    if (paciente == NULL) {
        return NULL;
    }
    
    paciente->id = id;
    strcpy(paciente->cpf, cpf, sizeof(paciente->cpf) - 1);
    paciente->cpf[sizeof(paciente->cpf) - 1] = '\0';

    strcpy(paciente->nome, nome, sizeof(paciente->nome) - 1);
    paciente->nome[sizeof(paciente->nome) - 1] = '\0';

    paciente->idade = idade;

    strcpy(paciente->data_cadastro, data_cadastro, sizeof(paciente->data_cadastro) - 1);
    paciente->data_cadastro[sizeof(paciente->data_cadastro) - 1] = '\0';

    return paciente;

}

void imprimir_paciente(const Paciente* paciente) {
    if (paciente != NULL) {
        printf("%-3d %-14s %-30s %-6d %s\n",
        paciente->id,
        paciente->cpf,
        paciente->nome,
        paciente->idade,
        paciente->data_cadastro);
    }
}

void liberar_paciente(Paciente* paciente) {
    free(paciente);
}
