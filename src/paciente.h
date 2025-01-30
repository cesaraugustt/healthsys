#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
} Paciente;

// Funções para manipulação de pacientes
Paciente* criar_paciente(int id, const char* cpf, const char* nome, int idade, const char* data_cadastro);
void imprimir_paciente(const Paciente* paciente);
void liberar_paciente(Paciente* paciente);

#endif