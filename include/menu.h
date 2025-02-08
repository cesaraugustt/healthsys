#ifndef MENU_H
#define MENU_H

#include "lista.h"
#include "paciente.h"
#include "arquivo.h"

void exibir_menu();
void menu(Lista* lista);
int consultar_paciente(Lista* lista);
void cadastrar_paciente(Lista* lista);
void remover_paciente_menu(Lista* lista);
void atualizar_paciente_menu(Lista* lista);

#endif