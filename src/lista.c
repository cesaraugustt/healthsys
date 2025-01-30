#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Lista* criar_lista() {
    Lista* lista = (Lista*)malloc(sizeof(lista));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->quantidade = 0;
    }
    return lista;
}

void inserir_paciente_lista(Lista* lista, Paciente paciente) {
    if (lista == NULL) return;

    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo == NULL) return;

    novo->paciente = paciente;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        Node* atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
    lista->quantidade++;
}

Node* buscar_paciente_por_cpf(Lista* lista, const char* cpf) {
    if (lista == NULL || cpf == NULL) return NULL;
    
    Node* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->paciente.cpf, cpf) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}


Node* buscar_paciente_por_nome(Lista* lista, const char* nome) {
    if (lista == NULL || nome == NULL) return NULL;
    
    Node* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->paciente.nome, nome) != NULL) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void remover_paciente_lista(Lista* lista, int id) {
    if (lista == NULL || lista->inicio == NULL) return;
    
    Node* atual = lista->inicio;
    Node* anterior = NULL;
    
    while (atual != NULL && atual->paciente.id != id) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual != NULL) {
        if (anterior == NULL) {
            lista->inicio = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
        lista->quantidade--;
    }
}

void imprimir_lista(Lista* lista) {
    if (lista == NULL) return;
    
    printf("\nID  CPF            Nome                           Idade  Data Cadastro\n");
    printf("----------------------------------------------------------------\n");
    
    Node* atual = lista->inicio;
    while (atual != NULL) {
        imprimir_paciente(&atual->paciente);
        atual = atual->prox;
    }
    printf("----------------------------------------------------------------\n");
    printf("Total de pacientes: %d\n", lista->quantidade);
}

void liberar_lista(Lista* lista) {
    if (lista == NULL) return;
    
    Node* atual = lista->inicio;
    while (atual != NULL) {
        Node* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(lista);
}