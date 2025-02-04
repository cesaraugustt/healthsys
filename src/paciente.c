#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

Paciente* criar_paciente(int id, const char* cpf, const char* nome, int idade,
const char* data_cadastro) {
    Paciente* novo_paciente = (Paciente*)malloc(sizeof(Paciente));
    if (novo_paciente == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    novo_paciente->id = id;
    strcpy(novo_paciente->cpf,cpf);
    strcpy(novo_paciente->nome, nome);
    novo_paciente->idade = idade;
    strcpy(novo_paciente->data_cadastro, data_cadastro);
    
    return novo_paciente;
}

void imprimir_paciente(const Paciente* paciente) {
    if (paciente == NULL) {
        printf("Paciente inválido.\n");
        return;
    }
    printf("%-4d %-15s %-30s %-6d %s\n", paciente->id, paciente->cpf,
    paciente->nome, paciente->idade, paciente->data_cadastro);
}

void liberar_paciente(Paciente* paciente) {
    if (paciente != NULL) {
        free(paciente);
    }
}