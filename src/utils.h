#ifndef UTILS_H
#define UTILS_H

// Funções auxiliares
int validar_cpf(const char* cpf);
int validar_data(const char* data);
void formatar_cpf(char* cpf_formatado, const char* cpf);
void limpar_buff();

#endif