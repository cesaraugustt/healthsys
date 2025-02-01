#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// Função para criar uma nova lista vazia
Lista* criar_lista() {
    Lista* nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a lista.\n");
        exit(EXIT_FAILURE);
    }

    nova_lista->inicio = NULL;
    nova_lista->tamanho = 0;
    return nova_lista;
}

// Função para liberar a memória alocada para a lista
void liberar_lista(Lista* lista) {
    if (lista == NULL) return;

    No* atual = lista->inicio;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        liberar_paciente(atual->paciente); // Libera o paciente armazenado no nó
        free(atual);                       // Libera o nó
        atual = proximo;
    }

    free(lista); // Libera a estrutura da lista
}

// Função para inserir um paciente na lista
void inserir_paciente(Lista* lista, Paciente* paciente) {
    if (lista == NULL || paciente == NULL) return;

    // Cria um novo nó para o paciente
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o nó.\n");
        exit(EXIT_FAILURE);
    }

    novo_no->paciente = paciente;
    novo_no->proximo = lista->inicio; // Insere no início da lista
    lista->inicio = novo_no;
    lista->tamanho++;
}

// Função para buscar um paciente pelo CPF
Paciente* buscar_paciente_por_cpf(Lista* lista, const char* cpf) {
    if (lista == NULL || cpf == NULL) return NULL;

    No* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->paciente->cpf, cpf) == 0) {
            return atual->paciente; // Retorna o paciente encontrado
        }
        atual = atual->proximo;
    }

    return NULL; // CPF não encontrado
}

// Função para buscar um paciente pelo nome
Paciente* buscar_paciente_por_nome(Lista* lista, const char* nome) {
    if (lista == NULL || nome == NULL) return NULL;

    No* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->paciente->nome, nome) == 0) {
            return atual->paciente; // Retorna o paciente encontrado
        }
        atual = atual->proximo;
    }

    return NULL; // Nome não encontrado
}

// Função para remover um paciente da lista pelo ID
void remover_paciente_por_id(Lista* lista, int id) {
    if (lista == NULL) return;

    No* anterior = NULL;
    No* atual = lista->inicio;

    while (atual != NULL) {
        if (atual->paciente->id == id) {
            // Remove o nó da lista
            if (anterior == NULL) {
                lista->inicio = atual->proximo; // Remove o primeiro nó
            } else {
                anterior->proximo = atual->proximo; // Remove um nó no meio ou final
            }

            liberar_paciente(atual->paciente); // Libera o paciente
            free(atual);                       // Libera o nó
            lista->tamanho--;
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }
}

// Função para imprimir todos os pacientes da lista
void imprimir_lista(Lista* lista) {
    if (lista == NULL) return;

    No* atual = lista->inicio;
    while (atual != NULL) {
        imprimir_paciente(atual->paciente);
        printf("\n");
        atual = atual->proximo;
    }
}