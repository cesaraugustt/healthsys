#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H

#include "lista.h"

#define ARQUIVO_BD "bd_paciente.csv"

typedef struct {
    Lista* lista;
    char* arquivo;
} BD_Paciente;

// Funções para manipulação do banco de dados
BD_Paciente* criar_bd();
int carregar_bd(BD_Paciente* bd);
int salvar_bd(BD_Paciente* bd);
void liberar_bd(BD_Paciente* bd);

#endif