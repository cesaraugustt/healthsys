#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "lista.h"

#define ARQUIVO_BD "bd_paciente.csv"

Lista* carregar_bd();
void salvar_bd(Lista* lista);

#endif