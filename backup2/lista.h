#ifndef LISTA_H
#define LISTA_H

#include "paciente.h"

typedef struct No {
    Paciente* paciente;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
    int quantidade; // Número de elementos na lista
} Lista;

Lista* criar_lista();
void inserir_paciente(Lista* lista, Paciente* paciente);
void remover_paciente_por_id(Lista* lista, int id);
No* buscar_paciente_por_cpf(Lista* lista, const char* cpf);
No* buscar_paciente_por_nome(Lista* lista, const char* nome);
void imprimir_lista(Lista* lista);
void liberar_lista(Lista* lista);

#endif