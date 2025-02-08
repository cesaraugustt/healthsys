#ifndef LISTA_H
#define LISTA_H

#include "paciente.h"

#define REGISTROS_POR_PAGINA 5

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
int buscar_por_nome(Lista* lista, const char* nome);
int buscar_por_cpf(Lista* lista, const char* cpf);
void remover_paciente(Lista* lista, int id);
void imprimir_lista(Lista* lista);
void liberar_lista(Lista* lista);

#endif