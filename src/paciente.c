#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

Paciente* criar_paciente(int id, const char* cpf, const char* nome, int idade,
const char* data_cadastro) {
    Paciente* novo_paciente = (Paciente*)malloc(sizeof(Paciente));
    if (novo_paciente == NULL) {
        printf("Erro ao alocar memória para o paciente.\n");
        exit(EXIT_FAILURE);
    }

    novo_paciente->id = id;
    strncpy(novo_paciente->cpf, cpf, 14); // CPF com pontuação (14 caracteres + '\0')
    novo_paciente->cpf[14] = '\0';        // Garante que o CPF está terminado com '\0'
    strncpy(novo_paciente->nome, nome, 99);
    novo_paciente->nome[99] = '\0';       // Garante que o nome está terminado com '\0'
    novo_paciente->idade = idade;
    strncpy(novo_paciente->data_cadastro, data_cadastro, 10);
    novo_paciente->data_cadastro[10] = '\0'; // Garante que a data está terminada com '\0'

    return novo_paciente;
}

void liberar_paciente(Paciente* paciente) {
    if (paciente != NULL) {
        free(paciente);
    }
}

void imprimir_paciente(const Paciente* paciente) {
    if (paciente == NULL) {
        printf("Paciente inválido.\n");
        return;
    }

    printf("%-3d %-14s %-30s %-6d %s\n", paciente->id, paciente->cpf,
    paciente->nome, paciente->idade, paciente->data_cadastro);
}