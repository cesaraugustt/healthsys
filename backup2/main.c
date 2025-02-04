#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "menu.h"

void imprimir_bd(BDPaciente* bd) {
    if (bd == NULL) {
        printf("BDPaciente está nulo.\n");
        return;
    }

    printf("BDPaciente:\n");
    printf("  Arquivo: %s\n", bd->arquivo);
    printf("  Proximo ID: %d\n", bd->prox_id);

    if (bd->lista == NULL) {
        printf("  Lista de pacientes está vazia.\n");
        return;
    }

    printf("  Pacientes na lista:\n");
    imprimir_lista(bd->lista);
}

int main() {
    BDPaciente* bd = (BDPaciente*)malloc(sizeof(BDPaciente));
    if (bd == NULL) {
        printf("Erro ao alocar memória para o BDPaciente.\n");
        exit(EXIT_FAILURE);
    }
    bd->arquivo = strdup(ARQUIVO_BD);
    carregar_bd(bd);
    // imprimir_bd(bd);
    processar_opcao(bd);
    return 0;
}