#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

Lista* carregar_bd() {
    // Abre o arquivo CSV para leitura
    FILE* file = fopen(ARQUIVO_BD, "r");
    if (file == NULL) {
        printf("Arquivo CSV não encontrado, iniciando com lista vazia...\n");
        return criar_lista(); // Retorna lista vazia se o arquivo não existir
    }

    // Cria uma nova lista de pacientes
    Lista* lista = criar_lista();
    if (lista == NULL) {
        fprintf(stderr, "Erro ao criar lista\n");
        fclose(file);
        return NULL; // Retorna NULL em caso de erro na criação da lista
    }

    char linha[256];

    // Ignora o cabeçalho do arquivo CSV
    if (fgets(linha, sizeof(linha), file) == NULL) {
        fprintf(stderr, "Erro ao ler o cabeçalho do arquivo\n");
        fclose(file);
        liberar_lista(lista);
        return NULL; // Retorna NULL se houver erro ao ler o cabeçalho
    }
    
    // Lê cada linha do arquivo CSV
    while (fgets(linha, sizeof(linha), file) != NULL) {
        int id, idade;
        char cpf[15], nome[100], data_cadastro[11];

        // Extrai os campos da linha lida
        if (sscanf(linha, "%d,%14[^,],%99[^,],%d,%10[^,]", &id, cpf, nome, &idade, data_cadastro) != 5) {
            printf("Erro ao ler linha do arquivo csv: %s\n", linha);
            continue; // Continua para a próxima linha em caso de erro de leitura
        }

        // Cria um novo paciente com os dados lidos
        Paciente* paciente = criar_paciente(id, cpf, nome, idade, data_cadastro);
        if (paciente == NULL) {
            fprintf(stderr, "Erro ao criar paciente\n");
            continue; // Continua para a próxima linha se ocorrer erro na criação do paciente
        }

        // Insere o paciente na lista
        inserir_paciente(lista, paciente);
    }

    fclose(file); // Fecha o arquivo após a leitura
    return lista; // Retorna a lista populada
}

void salvar_bd(Lista* lista) {
    // Abre o arquivo CSV para escrita
    FILE* file = fopen(ARQUIVO_BD, "w");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", ARQUIVO_BD);
        return;
    }

    // Escreve o cabeçalho do arquivo CSV
    fprintf(file, "ID,CPF,Nome,Idade,Data_Cadastro\n");

    // Percorre a lista e escreve cada paciente no arquivo
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

    // Fecha o arquivo após a escrita
    fclose(file);
    printf("Dados salvos com sucesso em %s.\n", ARQUIVO_BD);
}