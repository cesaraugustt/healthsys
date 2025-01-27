#ifndef LISTA_H
#define LISTA_H

#include "paciente.h"

typedef struct {
    Paciente paciente;
    struct Node* prox;
} Node;

typedef struct {
    Node* inicio;
    int quantidade;    
} Lista;

// Funções para manipulação da lista
Lista* criar_lista();
void inserir_paciente_lista(Lista* lista, Paciente paciente);
Node* buscar_paciente_cpf(Lista* lista, const char* cpf);
Node* buscar_paciente_nome(Lista* lista, const char* nome);
void remover_paciente_lista(Lista* lista, int id);
void imprimir_lista(Lista* lista);
void liberar_lista(Lista* lista);

#endif