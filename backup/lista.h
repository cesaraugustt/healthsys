#ifndef LISTA_H
#define LISTA_H

#include "paciente.h"

typedef struct node {
    Paciente* paciente;
    Node* proximo;
} Node;

typedef struct {
    Node* inicio;
    int quantidade; // Número de elementos na lista
} Lista;

Lista* criar_lista();
void inserir_paciente(Lista* lista, Paciente* paciente);
void remover_paciente_por_id(Lista* lista, int id);
Node* buscar_paciente_por_cpf(Lista* lista, const char* cpf);
Node* buscar_paciente_por_nome(Lista* lista, const char* nome);
void imprimir_lista(Lista* lista);
void liberar_lista(Lista* lista);

#endif