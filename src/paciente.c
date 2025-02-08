#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

Paciente* criar_paciente(int id, const char* cpf, const char* nome, int idade,
const char* data_cadastro) {
    Paciente* novo_paciente = (Paciente*)malloc(sizeof(Paciente));
    if (novo_paciente == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o paciente!\n");
        return NULL;
    }

    /* Inicializa os campos do paciente com as informações recebidas. */
    novo_paciente->id = id;
    strcpy(novo_paciente->cpf, cpf);
    strcpy(novo_paciente->nome, nome);
    novo_paciente->idade = idade;
    strcpy(novo_paciente->data_cadastro, data_cadastro);
    
    return novo_paciente;
}

void atualizar_paciente(Paciente* paciente, const char* cpf, const char* nome, int idade, const char* data_cadastro) {
    if (paciente == NULL) {
        printf("Paciente inválido.\n");
        return;
    }

    if (strlen(cpf) > 14 || strlen(nome) > 99 || strlen(data_cadastro) > 10) {
        printf("Os dados do paciente não podem exceder os limites de tamanho.\n");
        return;
    }

    strcpy(paciente->cpf, cpf);
    strcpy(paciente->nome, nome);
    paciente->idade = idade;
    strcpy(paciente->data_cadastro, data_cadastro);

    printf("Paciente atualizado com sucesso!\n");
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
    if (paciente == NULL) {
        fprintf(stderr, "Erro: Tentativa de liberar um paciente nulo.\n");
        return;
    }
    free(paciente);
}
