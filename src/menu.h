#ifndef MENU_H
#define MENU_H

#include "bd_paciente.h"

// Funções do menu
void exibir_menu();
void consultar_paciente(BDPaciente* bd);
void atualizar_paciente(BDPaciente* bd);
void remover_paciente(BDPaciente* bd);
void inserir_paciente(BDPaciente* bd);
void imprimir_pacientes(BDPaciente* bd);

#endif