#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"

BDPaciente* criar_bd() {
    BDPaciente* bd = (BDPaciente*)malloc(sizeof(BDPaciente));
    if (bd != NULL) {
        bd->lista = criar_lista();
        bd->arquivo = strdup(ARQUIVO_BD);
        if (bd->lista == NULL || bd->arquivo == NULL) {
            liberar_bd(bd);
            return NULL;
        }
    }
    return bd;
}

int carregar_bd(BDPaciente* bd) {
    if (bd == NULL) return 1;
    
    FILE* arquivo = fopen(bd->arquivo, "r");
    if (arquivo == NULL) return 1;
    
    char linha[256];
    // Pular a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        Paciente p;
        char* token = strtok(linha, ",");
        if (token != NULL) {
            p.id = atoi(token);
            
            token = strtok(NULL, ",");
            if (token != NULL) strncpy(p.cpf, token, sizeof(p.cpf)-1);
            
            token = strtok(NULL, ",");
            if (token != NULL) strncpy(p.nome, token, sizeof(p.nome)-1);
            
            token = strtok(NULL, ",");
            if (token != NULL) p.idade = atoi(token);
            
            token = strtok(NULL, "\n");
            if (token != NULL) strncpy(p.data_cadastro, token, sizeof(p.data_cadastro)-1);
            
            inserir_paciente_lista(bd->lista, p);
        }
    }
    
    fclose(arquivo);
    return 0;
}

int salvar_bd(BDPaciente* bd) {
    if (bd == NULL) return 1;
    
    FILE* arquivo = fopen(bd->arquivo, "w");
    if (arquivo == NULL) return 1;
    
    // Escrever cabeçalho
    fprintf(arquivo, "ID,CPF,Nome,Idade,Data_Cadastro\n");
    
    Node* atual = bd->lista->inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%d,%s,%s,%d,%s\n",
                atual->paciente.id,
                atual->paciente.cpf,
                atual->paciente.nome,
                atual->paciente.idade,
                atual->paciente.data_cadastro);
        atual = atual->prox;
    }
    
    fclose(arquivo);
    return 0;
}

void liberar_bd(BDPaciente* bd) {
    if (bd != NULL) {
        if (bd->lista != NULL) {
            liberar_lista(bd->lista);
        }
        if (bd->arquivo != NULL) {
            free(bd->arquivo);
        }
        free(bd);
    }
}