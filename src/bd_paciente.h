#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H

#include "lista.h"

#define ARQUIVO_BD "bd_paciente.csv"

typedef struct {
    Lista* lista;
    char* arquivo;
} BDPaciente;

// Funções para manipulação do banco de dados
BDPaciente* criar_bd();
int carregar_bd(BDPaciente* bd);
int salvar_bd(BDPaciente* bd);
void liberar_bd(BDPaciente* bd);

#endif