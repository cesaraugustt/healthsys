#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "arquivo.h"

void exibir_menu() {
    printf("\nHealthSys - Sistema de Gerenciamento de Pacientes\n");
    printf("1. Consultar paciente\n");
    printf("2. Atualizar paciente\n");
    printf("3. Remover paciente\n");
    printf("4. Inserir paciente\n");
    printf("5. Imprimir lista de pacientes\n");
    printf("Q. Sair\n");
    printf("Escolha uma opção: ");
}

void processar_opcao(BDPaciente* bd) {
    char opcao;
    do {
        exibir_menu();
        scanf(" %c", &opcao);
        limpar_buffer();

        switch (opcao) {
            case '1':
                consultar_paciente(bd->lista);
                // printf("consultar_paciente()");
                break;
            case '2':
                // atualizar_paciente(bd->lista);
                printf("atualizar_paciente()");
                break;
            case '3':
                // remover_paciente(bd->lista);
                printf("remover_paciente()");
                break;
            case '4':
                // inserir_paciente_menu(bd);
                printf("cadastrar_paciente");
                break;
            case '5':
                imprimir_lista(bd->lista);
                break;
            case 'Q':
            case 'q':
                printf("Salvando dados e encerrando...\n");
                //salvar_pacientes_bd(bd);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 'Q' && opcao != 'q');
}

void consultar_paciente(BDPaciente* bd) {
    printf("\nEscolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
    printf("Opção: ");

    char opcao;
    scanf(" %c", &opcao);
    limpar_buffer();

    No* resultado = NULL;
    switch (opcao) {
        case '1': {
            char nome[100];
            printf("Digite o nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            resultado = buscar_paciente_por_nome(bd->lista, nome);
            break;
        }
        case '2': {
            // char cpf[15];
            // printf("Digite o CPF: ");
            // fgets(cpf, sizeof(cpf), stdin);
            // cpf[strcspn(cpf, "\n")] = 0;
            // resultado = buscar_paciente_por_cpf(bd->lista, cpf);
            break;
        }
        case '3':
            return;
        default:
            printf("Opção inválida!\n");
            return;
    }

    if (resultado) {
        printf("\nID  CPF            Nome                           Idade  Data Cadastro\n");
        printf("----------------------------------------------------------------\n");
        imprimir_paciente(resultado->paciente);
    } else {
        printf("Paciente não encontrado.\n");
    }
}