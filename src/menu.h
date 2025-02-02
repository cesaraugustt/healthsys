#ifndef MENU_H
#define MENU_H

#include "lista.h"
#include "arquivo.h"

// Funções do módulo Menu
void exibir_menu();
void processar_opcao(BDPaciente* bd);
void consultar_paciente(Lista* lista);
void atualizar_paciente(Lista* lista);
void remover_paciente(Lista* lista);
void inserir_paciente_menu(BDPaciente* bd);
void imprimir_lista_pacientes(Lista* lista);

#endif