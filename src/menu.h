#ifndef MENU_H
#define MENU_H

#include "lista.h"

// Funções do módulo Menu
void exibir_menu();
void processar_opcao(Lista* lista);
void consultar_paciente(Lista* lista);
void atualizar_paciente(Lista* lista);
void remover_paciente(Lista* lista);
void inserir_paciente_menu(Lista* lista);
void imprimir_lista_pacientes(Lista* lista);

#endif // MENU_H