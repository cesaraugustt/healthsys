#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Lista* criar_lista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) {
        printf("Erro ao alocar memória para a lista.\n");
        exit(EXIT_FAILURE);
    }

    lista->inicio = NULL;
    lista->quantidade = 0;
    return lista;
}

void inserir_paciente(Lista* lista, Paciente* paciente) { // Insere ao final da lista
    if (lista == NULL || paciente == NULL) return;

    No* anterior = NULL;
    No* atual = lista->inicio;

    while (atual != NULL && atual->paciente->id < paciente->id ) {
        anterior = atual;
        atual = atual->proximo;
    }

    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    novo->paciente = paciente;

    // Encadeamento do novo nó
    if (anterior == NULL) {
        novo->proximo = lista->inicio;
        lista->inicio = novo;
    } else {
        novo->proximo = anterior->proximo;
        anterior->proximo = novo;
    }

    lista->quantidade++;
}

void imprimir_lista(Lista* lista) {
    if (lista == NULL) return;

    printf("\nID  CPF            Nome                           Idade  Data Cadastro\n");
    printf("----------------------------------------------------------------\n");

    No* atual = lista->inicio;
    while (atual != NULL) {
        imprimir_paciente(atual->paciente);
        atual = atual->proximo;
    }
    printf("----------------------------------------------------------------\n");
}

void liberar_lista(Lista* lista) {
    if (lista == NULL) return;

    No* atual = lista->inicio;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        liberar_paciente(atual->paciente); // Libera o paciente armazenado no nó
        free(atual);                       // Libera o nó
        atual = proximo;
    }
    free(lista);
}

No* buscar_paciente_por_nome(Lista* lista, const char* nome) {
    if (lista == NULL || nome == NULL) return NULL;
    
    No* atual = lista->inicio;
    while (atual != NULL) {
        if (strstr(atual->paciente->nome, nome) != 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

No* buscar_paciente_por_cpf(Lista* lista, const char* cpf) {
    if (lista == NULL || cpf == NULL) return NULL;
    
    No* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->paciente->cpf, cpf) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}