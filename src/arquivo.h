#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "lista.h" // Inclui a definição de Lista

// Funções do módulo CSV
Lista* carregar_pacientes_csv(const char* nome_arquivo);
void salvar_pacientes_csv(const char* nome_arquivo, Lista* lista);

#endif // CSV_H