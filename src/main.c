#include <stdio.h>
#include <stdlib.h>
#include "bd_paciente.h"
#include "menu.h"

BDPaciente* bd;

int main() {
    bd = criar_bd();
    if (!bd) {
        fprintf(stderr, "Erro ao criar banco de dados\n");
        return 1;
    }

    carregar_csv(bd, "bd_paciente.csv");

    char opcao;
    do {
        exibir_menu();
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);

        if (opcao == 'Q' || opcao == 'q') {
            break;
        }

        int opcao_num = opcao - '0';
        if (opcao_num >= 1 && opcao_num <= 6) {
            processar_opcao(opcao_num);
        } else {
            printf("Opção inválida!\n");
        }

    } while (1);

    salvar_csv(bd, "bd_paciente.csv");
    liberar_bd(bd);

    return 0;
}