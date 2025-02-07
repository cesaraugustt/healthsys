#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

Lista* carregar_bd() {
    FILE* file = fopen(ARQUIVO_BD, "r");
    if (file == NULL) {
        printf("Arquivo CSV não encontrado, iniciando com lista vazia...\n");
        return criar_lista();
    }

    Lista* lista = criar_lista();

    char linha[256];

    // Ignora o cabeçalho
    fgets(linha, sizeof(linha), file);
    
    while (fgets(linha, sizeof(linha), file) != NULL) {
        int id, idade;
        char cpf[15], nome[100], data_cadastro[11];

        // Lê os campos da linha
        if (sscanf(linha, "%d,%14[^,],%99[^,],%d,%10[^,]", &id, cpf, nome, &idade,
            data_cadastro) != 5) {
            // Erro ao ler linha do arquivo csv
            printf("Erro ao ler linha do arquivo csv: %s\n", linha);
            fclose(file);
            return lista;
        }

        // Insere o paciente na lista
        inserir_paciente(lista, criar_paciente(id, cpf, nome, idade, data_cadastro));
    }

    fclose(file);
    return lista;
}

void salvar_bd(Lista* lista) {
    FILE* file = fopen(ARQUIVO_BD, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", ARQUIVO_BD);
        return;
    }

    // Escreve o cabeçalho
    fprintf(file, "ID,CPF,Nome,Idade,Data_Cadastro\n");

    // Percorre a lista e escreve cada paciente
    No* atual = lista->primeiro;
    while (atual != NULL) {
        Paciente* p = atual->paciente;
        fprintf(
            file,
            "%d,%s,%s,%d,%s\n",
            p->id,
            p->cpf,
            p->nome,
            p->idade,
            p->data_cadastro
        );
        atual = atual->proximo;
    }

    fclose(file);
    printf("Dados salvos com sucesso em %s.\n", ARQUIVO_BD);
    }
