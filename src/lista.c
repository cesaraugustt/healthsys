#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "paciente.h"

static No* criar_no(Paciente* paciente) {
    if (paciente == NULL) {
        fprintf(stderr, "Erro ao criar nó: paciente nulo\n");
        return NULL;
    }

    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o nó!\n");
        return NULL;
    }

    novo_no->paciente = paciente;
    novo_no->anterior = NULL;
    novo_no->proximo = NULL;

    return novo_no;
}

Lista* criar_lista() {
    Lista* nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a lista!\n");
        exit(EXIT_FAILURE);
    }
    nova_lista->primeiro = NULL;
    nova_lista->ultimo = NULL;
    
    return nova_lista;
}

void inserir_paciente(Lista* lista, Paciente* paciente) {
    if (lista == NULL || paciente == NULL) {
        fprintf(stderr, "Erro ao inserir paciente: lista ou paciente nulo\n");
        return;
    }

    if (lista->ultimo == NULL) {
        lista->primeiro = lista->ultimo = criar_no(paciente);
    } else {
        No* no = criar_no(paciente);
        if (no == NULL) {
            fprintf(stderr, "Erro ao alocar memória para o nó!\n");
            return;
        }
        lista->ultimo->proximo = no;
        no->anterior = lista->ultimo;
        lista->ultimo = no;
    }
}

void remover_paciente(Lista* lista, int id) {
    if (lista == NULL) {
        fprintf(stderr, "Erro: lista nula.\n");
        return;
    }

    No* atual = lista->primeiro;
    No* anterior = NULL;
    // Percorre a lista ate encontrar o paciente com o ID especificado
    while (atual != NULL && atual->paciente->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        lista->primeiro = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    if (atual->proximo == NULL) {
        lista->ultimo = anterior;
    } else {
        atual->proximo->anterior = anterior;
    }

    liberar_paciente(atual->paciente);
    free(atual);
    printf("Paciente removido com sucesso.\n");
}

void imprimir_lista(Lista* lista) {
    if (lista == NULL) {
        fprintf(stderr, "Erro: lista nula.\n");
        return;
    }

    No* no_atual = lista->primeiro;
    if (no_atual == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    printf("%-4s %-15s %-30s %-6s %s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");

    while (no_atual != NULL) {
        if (no_atual->paciente != NULL) {
            imprimir_paciente(no_atual->paciente);
        } else {
            fprintf(stderr, "Erro: paciente nulo.\n");
        }
        no_atual = no_atual->proximo;
    }
}

void liberar_lista(Lista* lista) {
    No* atual = lista->primeiro;
    while (atual){
        No* proximo = atual->proximo;
        liberar_paciente(atual->paciente);
        free(atual);
        atual = proximo;
    }
    free(lista);
}

void buscar_por_nome(Lista* lista, const char* nome) {
    No* atual = lista->primeiro;
    printf("%-4s %-15s %-30s %-6s %s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");
    while (atual != NULL) {
        if (strstr(atual->paciente->nome, nome) != NULL) {
            imprimir_paciente(atual->paciente);
        }
        atual = atual->proximo;
    }
}

void buscar_por_cpf(Lista* lista, const char* cpf) {
    No* atual = lista->primeiro;
    while (atual != NULL && strcmp(atual->paciente->cpf, cpf) != 0) {
        atual = atual->proximo;
    }

    if (atual != NULL) {
        printf("%-4s %-15s %-30s %-6s %s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");
        imprimir_paciente(atual->paciente);
    }
}
