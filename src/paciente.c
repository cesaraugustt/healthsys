#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

Paciente* criar_paciente(int id, const char* cpf, const char* nome, int idade,
const char* data_cadastro) {
    Paciente* paciente = (Paciente*)malloc(sizeof(Paciente));
    if (paciente) {
        paciente->id = id;
        strncpy(paciente->cpf, cpf, 14);
        strcnpy(paciente->nome, nome, 99);
        paciente->idade = idade;
        strncpy(paciente->data_cadastro, data_cadastro, 10);
        paciente->cpf[14] = '\0';
        paciente->nome[99] = '\0';
        paciente->data_cadastro[10] = '\0';    
    }
    return paciente;
}

void liberar_paciente(Paciente* paciente) {
    free(paciente);
}

void imprimir_paciente(const Paciente* paciente) {
    printf("ID: %d, CPF: %s, Idade: %d, Data cadastro: %s\n",
    paciente->id, paciente->cpf, paciente->nome, paciente->idade, paciente->data_cadastro);
}
