#ifndef LISTA_H
#define LISTA_H

#include "paciente.h"

typedef struct No {
    Paciente* paciente;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
    int tamanho; // Número de elementos na lista
} Lista;

Lista* criar_lista();
void inserir_paciente(Lista* lista, Paciente* paciente);
Paciente* buscar_paciente_por_cpf(Lista* lista, const char* cpf);
Paciente* buscar_paciente_por_nome(Lista* lista, const char* nome);
void remover_paciente_por_id(Lista* lista, int id);
void imprimir_lista(Lista* lista);
void liberar_lista(Lista* lista);

#endif