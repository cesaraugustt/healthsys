#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "lista.h"
#include "paciente.h"

// Função para carregar pacientes de um arquivo CSV
void carregar_bd(BDPaciente* bd) {
    FILE* arquivo = fopen(bd->arquivo, "r");
    if (arquivo == NULL) {
        printf("Arquivo %s não encontrado. Iniciando com lista vazia.\n", bd->arquivo);
        bd->prox_id = 1;
        return criar_lista(); // Retorna uma lista vazia se o arquivo não existir
    }

    Lista* lista = criar_lista();
    char linha[256];

    // Ignora o cabeçalho do CSV
    fgets(linha, sizeof(linha), arquivo);

    // Variável para acompanhar o maior ID encontrado
    int max_id = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = '\0';

        // Divide os campos usando strtok
        char* token;
        char* campos[5]; // ID, CPF, Nome, Idade, Data_Cadastro
        int i = 0;

        token = strtok(linha, ",");
        while (token != NULL && i < 5) {
            campos[i++] = token;
            token = strtok(NULL, ",");
        }

        // Verifica se todos os campos foram lidos
        if (i != 5) {
            printf("Linha inválida no CSV: %s\n", linha);
            continue;
        }

        // Converte os campos para os tipos corretos
        int id = atoi(campos[0]);
        int idade = atoi(campos[3]);

        // Atualiza o maior ID
        if (id >= max_id) {
            max_id = id + 1;
        }

        // Cria o paciente e insere na lista
        Paciente* paciente = criar_paciente(
            id,
            campos[1],    // CPF (com pontuação)
            campos[2],    // Nome
            idade,
            campos[4]     // Data_Cadastro
        );

        inserir_paciente(bd->lista, paciente);
    }
    // Atualiza o prox_id do BDPaciente
    bd->prox_id = max_id;

    fclose(arquivo);
    // return bd->lista;
}

// Função para salvar pacientes em um arquivo CSV
void salvar_pacientes_bd(BDPaciente* bd) {
    FILE* arquivo = fopen(bd->arquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s para escrita.\n", bd->arquivo);
        return;
    }

    // Escreve o cabeçalho
    fprintf(arquivo, "ID,CPF,Nome,Idade,Data_Cadastro\n");

    // Percorre a lista e escreve cada paciente
    Node* atual = bd->lista->inicio;
    while (atual != NULL) {
        Paciente* p = atual->paciente;
        fprintf(
            arquivo,
            "%d,%s,%s,%d,%s\n",
            p->id,
            p->cpf,
            p->nome,
            p->idade,
            p->data_cadastro
        );
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso em %s.\n", bd->arquivo);
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