#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

static No* criar_no(Paciente* paciente) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novo_no->paciente = paciente;
    novo_no->anterior = NULL;
    novo_no->proximo = NULL;

    return novo_no;
}

Lista* criar_lista() {
    Lista* nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    nova_lista->primeiro = NULL;
    nova_lista->ultimo = NULL;
    
    return nova_lista;
}

void inserir_paciente(Lista* lista, Paciente* paciente) {
    No* no = criar_no(paciente);

    if (lista->primeiro == NULL && lista->ultimo == NULL){
        lista->primeiro = no;
        lista->ultimo = no;
    } else {
        lista->ultimo->proximo = no;
        no->anterior = lista->ultimo;
        lista->ultimo = no;
    }
}

void remover_paciente(Lista* lista, int id) {
    No* atual = lista->primeiro;
    while (atual){
        No* proximo = atual->proximo;
        if (atual->paciente->id == id){
            
            liberar_paciente(atual->paciente);
            free(atual);
            return;
        }
        atual = proximo;
    }
}

void imprimir_pacientes(Lista* lista) {
    No* atual = lista->primeiro;
    if (atual == NULL){
        printf("Lista vazia.\n");
        return;
    } else {
        printf("%-4s %-15s %-30s %-6s %s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");
        while (atual){
            No* proximo = atual->proximo;
            imprimir_paciente(atual->paciente);
            atual = proximo;
        }
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
    while (atual) {
        No* proximo = atual->proximo;
        if (strstr(atual->paciente->nome, nome) != NULL) {
            imprimir_paciente(atual->paciente);
        }
        atual = proximo;
    }
}

void buscar_por_cpf(Lista* lista, const char* cpf) {
    No* atual = lista->primeiro;
    printf("%-4s %-15s %-30s %-6s %s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");
    while (atual) {
        No* proximo = atual->proximo;
        if (strcmp(atual->paciente->cpf, cpf) == 0) {
            imprimir_paciente(atual->paciente);
        }
        atual = proximo;
    }
}