#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct {
    int id;
    char cpf[15]; // CPF com pontuação (XXX.XXX.XXX-XX) + '\n'
    char nome[100];
    int idade;
    char data_cadastro[11]; // Data com pontuação (AAAA-MM-DD) + '\n'
} Paciente;

Paciente* criar_paciente(int id, const char* cpf, const char* nome, int idade, const char* data_cadastro);
void atualizar_paciente(Paciente* paciente, const char* cpf, const char* nome, int idade, const char* data_cadastro);
void imprimir_paciente(const Paciente* paciente);
void liberar_paciente(Paciente* paciente);

#endif