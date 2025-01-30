#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"

BDPaciente* criar_bd() {
    BDPaciente* bd = (BDPaciente*)malloc(sizeof(BDPaciente));
    if (bd) {
        bd->inicio = NULL;
        bd->proximo_id = 1;
    }
    return bd;
}

void liberar_bd(BDPaciente* bd) {
    Node* atual = bd->inicio;
    while (atual)
    {
        Node* proximo = atual->proximo;
        liberar_paciente(atual->paciente);
        free(atual);
        atual = proximo;
    }
    free(bd);
}

void carregar_csv(BDPaciente* bd, const char* arquivo) {
    FILE* file = fopen(arquivo, "r");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return;
    }
    
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        int id, idade;
        char cpf[15], nome[100], data_cadastro[11];
        if (sscanf(linha, "%d,%[^,],%[^,],%d,%s", &id, cpf, nome, &idade, data_cadastro) == 5) {
            Paciente* paciente = criar_paciente(id, cpf, nome, idade, data_cadastro);
            inserir_paciente(bd, paciente);
        }
    }
    fclose(file);
}

void salvar_csv(const BDPaciente* bd, const char* arquivo) {
    FILE* file = fopen(arquivo, "w");
    if (!file)
    {
        perror("Erro ao abrir arquivo");
        return;
    }

    Node* atual = bd->inicio;
    while (atual)
    {
        fprintf(file, "%d,%s,%s,%d,%s\n", atual->paciente->id, atual->paciente->cpf,
        atual->paciente->nome, atual->paciente->idade, atual->paciente->data_cadastro);
        atual = atual->proximo;
    }
    fclose(file);
}

void inserir_paciente(BDPaciente* bd, Paciente* paciente) {
    Node* novo_node= (Node*)malloc(sizeof(Node));
    if (novo_node)
    {
        novo_node->paciente = paciente;
        novo_node->proximo = bd->inicio;
        bd->inicio = novo_node;
        paciente->id = bd->proximo_id++;
    }
}

Paciente* buscar_paciente_por_cpf(const BDPaciente* bd, const char* cpf) {
    Node* atual = bd->inicio;
    while (atual) {
        if (strcmp(atual->paciente->cpf, cpf) == 0) {
            return atual->proximo;
        }
        atual = atual->proximo;
    }
    return NULL;
}

Paciente* buscar_paciente_por_nome(const BDPaciente* bd, const char* nome) {
    Node* atual = bd->inicio;
    while (atual) {
        if (strcmp(atual->paciente->nome, nome) == 0) {
            return atual->proximo;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void remover_paciente(BDPaciente* bd, int id) {
    Node* anterior = NULL;
    Node* atual = bd->inicio;
    while (atual) {
        if (atual->paciente->id == id) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                bd->inicio = atual->proximo;
            }
            liberar_paciente(atual->paciente);
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void imprimir_todos_pacientes(const BDPaciente* bd) {
    Node* atual = bd->inicio;
    while (atual) {
        imprimir_paciente(atual->paciente);
        atual = atual->proximo;
    }
}