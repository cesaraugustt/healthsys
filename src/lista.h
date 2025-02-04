#ifndef LISTA_H
#define LISTA_H

#include "paciente.h"

typedef struct No {
    Paciente* paciente;
    struct No* anterior;
    struct No* proximo;
} No;

typedef struct lista {
    No* primeiro;
    No* ultimo;
} Lista;

Lista* criar_lista();
void inserir_paciente(Lista* lista, Paciente* paciente);
void buscar_por_nome(Lista* lista, const char* nome);
void buscar_por_cpf(Lista* lista, const char* cpf);
void remover_paciente(Lista* lista, int id);
void imprimir_pacientes(Lista* lista);
void liberar_lista(Lista* lista);

#endif