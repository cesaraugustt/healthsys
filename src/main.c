#include <stdio.h>
#include <stdlib.h>
#include "bd_paciente.h"
#include "menu.h"
#include "utils.h"

int main() {
    BDPaciente* bd = criar_bd();
    if (!bd || carregar_bd(bd) != 0) {
        printf("Erro ao inicializar o banco de dados!\n");
        return 1;
    }

    char opcao;
    do {
        exibir_menu();
        scanf(" %c", &opcao);
        limpar_buffer();

        switch (opcao) {
            case '1':
                consultar_paciente(bd);
                break;
            case '2':
                atualizar_paciente(bd);
                break;
            case '3':
                remover_paciente(bd);
                break;
            case '4':
                inserir_paciente(bd);
                break;
            case '5':
                imprimir_pacientes(bd);
                break;
            case 'Q':
            case 'q':
                printf("Salvando dados e encerrando...\n");
                salvar_bd(bd);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 'Q' && opcao != 'q');

    liberar_bd(bd);
    return 0;
}