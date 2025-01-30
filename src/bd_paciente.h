#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H

#include "paciente.h"

typedef struct Node {
    Paciente* paciente;
    struct Node* proximo;
} Node;

typedef struct {
    Node* inicio;
    int proximo_id;
} BDPaciente;

BDPaciente* criar_bd();
void liberar_bd(BDPaciente* bd);
void carregar_csv(BDPaciente* bd, const char* arquivo);
void salvar_csv(BDPaciente* bd, const char* arquivo);
void inserir_csv(BDPaciente* bd, Paciente* paciente);
Paciente* buscar_paciente_por_cpf(const BDPaciente* bd, const char* cpf);
Paciente* buscar_paciente_por_nome(const BDPaciente* bd, const char* nome);
void remover_paciente(BDPaciente* bd, int id);
void imprimir_todos_pacientes(const BDPaciente* bd);

#endif