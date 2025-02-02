#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "lista.h"

#define ARQUIVO_BD "bd_paciente.csv"

typedef struct {
    Lista* lista;
    char* arquivo;
    int prox_id;
} BDPaciente;

void carregar_bd(BDPaciente* bd);
void salvar_bd(BDPaciente* bd);
void liberar_bd(BDPaciente* bd);

#endif