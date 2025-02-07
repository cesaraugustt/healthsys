#ifndef MENU_H
#define MENU_H

#include "lista.h"
#include "paciente.h"
#include "arquivo.h"

void exibir_menu();
void menu(Lista* lista);
void consultar_paciente(Lista* lista);
void cadastrar_paciente(Lista* lista);
// void remover_paciente(BDPaciente* bd);
// void inserir_paciente_menu(BDPaciente* bd);

#endif