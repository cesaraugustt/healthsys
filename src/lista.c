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

void liberar_lista(Lista* lista) {
    if (lista == NULL) return;

    Node* atual = lista->inicio;
    while (atual != NULL) {
        Node* proximo = atual->proximo;
        liberar_paciente(atual->paciente); // Libera o paciente armazenado no nó
        free(atual);                       // Libera o nó
        atual = proximo;
    }

    free(lista);
}

// void inserir_paciente(Lista* lista, Paciente* paciente) {
//     if (lista == NULL || paciente == NULL) return;

//     Node* novo_node = (Node*)malloc(sizeof(Node));
//     if (novo_node == NULL) {
//         printf("Erro ao alocar memória para o nó.\n");
//         exit(EXIT_FAILURE);
//     }

//     novo_node->paciente = paciente;
//     novo_node->proximo = NULL;

//     if (lista->inicio == NULL) {
//         lista->inicio = novo_node;
//     } else {
//         Node* atual = lista->inicio;
//         while (atual->proximo != NULL) {
//             atual = atual->proximo;
//         }
//         atual->proximo = novo_node;
//     }
//     lista->quantidade++;
// }

void inserir_paciente(Lista* lista, Paciente* paciente) {
    if (lista == NULL || paciente == NULL) return;

    Node* anterior = NULL;
    Node* atual = lista->inicio;

    while (atual != NULL && atual->paciente->id < paciente->id ) {
        anterior = atual;
        atual = atual->proximo;
    }

    Node* novo = (Node*) malloc(sizeof(Node));
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

Paciente* buscar_paciente_por_cpf(Lista* lista, const char* cpf) {
    if (lista == NULL || cpf == NULL) return NULL;

    Node* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->paciente->cpf, cpf) == 0) {
            return atual->paciente;
        }
        atual = atual->proximo;
    }

    return NULL; // CPF não encontrado
}

Paciente* buscar_paciente_por_nome(Lista* lista, const char* nome) {
    if (lista == NULL || nome == NULL) return NULL;

    Node* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->paciente->nome, nome) == 0) {
            return atual->paciente;
        }
        atual = atual->proximo;
    }

    return NULL; // Nome não encontrado
}

// void remover_paciente_por_id(Lista* lista, int id) {
//     

//     Node* anterior = NULL;
//     Node* atual = lista->inicio;

//     while (atual != NULL) {
//         if (atual->paciente->id == id) {
//             // Remove o nó da lista
//             if (anterior == NULL) {
//                 lista->inicio = atual->proximo; // Remove o primeiro nó
//             } else {
//                 anterior->proximo = atual->proximo; // Remove um nó no meio ou final
//             }

//             liberar_paciente(atual->paciente);
//             free(atual);
//             lista->quantidade--;
//             return;
//         }
//     }
// }

void remover_paciente_por_id(Lista* lista, int id) {
    if (lista == NULL || lista->inicio == NULL) return;

    Node* anterior = NULL;
    Node* atual = lista->inicio;

    while (atual != NULL && atual->paciente->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            lista->inicio = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        liberar_paciente(atual->paciente);
        free(atual);
        lista->quantidade--;
    }
}

void imprimir_lista(Lista* lista) {
    if (lista == NULL) return;

    Node* atual = lista->inicio;
    while (atual != NULL) {
        imprimir_paciente(atual->paciente);
        printf("\n");
        atual = atual->proximo;
    }
}