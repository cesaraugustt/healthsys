#ifndef VALIDACAO_H
#define VALIDACAO_H

// Retorna 1 se válido, 0 se inválido
int validar_cpf(const char* cpf);
int validar_data(const char* data);
int validar_idade(int idade);

// Funções de formatação
void formatar_cpf(const char* cpf_entrada, char* cpf_formatado);

#endif