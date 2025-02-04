#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "paciente.h"

void carregar_bd(BDPaciente *bd) {
    FILE *file = fopen(bd->arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", bd->arquivo);
        return;
    }

    // Cria uma nova lista para armazenar os pacientes
    Lista* lista = criar_lista();
    char linha[256];

    // Ignora o cabeçalho
    if (fgets(linha, sizeof(linha), file) == NULL) {
        fclose(file);
        return;
    }

    // Inicializa o prox_id com um valor baixo
    int max_id = 0;

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), file) != NULL) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = '\0';

        // Divide os campos usando strtok
        char* token;
        char* campos[5]; // Espera-se: ID, CPF, Nome, Idade, Data_Cadastro
        int i = 0;
        token = strtok(linha, ",");
        while (token != NULL && i < 5) {
            campos[i++] = token;
            token = strtok(NULL, ",");
        }

        // Verifica se todos os campos foram lidos
        if (i != 5) {
            fprintf(stderr, "Linha inválida no CSV: %s\n", linha);
            continue;
        }

        // Converte os campos para os tipos corretos
        int id = atoi(campos[0]);
        int idade = atoi(campos[3]);

        // Atualiza o valor máximo de ID para definir prox_id posteriormente
        if (id >= max_id) {
            max_id = id + 1;
        }

        // Cria o paciente utilizando a função de criação
        Paciente* paciente = criar_paciente(
            id,
            campos[1],    // CPF (com pontuação)
            campos[2],    // Nome
            idade,
            campos[4]     // Data_Cadastro
        );

        // Insere o paciente na lista
        inserir_paciente(lista, paciente);
    }

    fclose(file);

    // Atualiza o BD com a lista carregada e define o prox_id
    bd->lista = lista;
    bd->prox_id = max_id;
}
