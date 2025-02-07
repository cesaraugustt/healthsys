#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibir_menu() {
    printf("\nHealthSys - Sistema de Gerenciamento de Pacientes\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir paciente\n");
    printf("5 - Imprimir lista de pacientes\n");
    printf("Q - Sair\n");
    printf("Escolha uma opção: ");
}

void consultar_paciente(Lista* lista) {
    printf("\nEscolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
    printf("Opção: ");

    char opcao;
    scanf(" %c", &opcao);
    // limpar_buffer();

    // No* resultado = NULL;
    switch (opcao) {
        case '1': {
            char nome[100];
            printf("Digite o nome: ");
            scanf(" %[^\n]", nome); // Lê uma string com espaços até a quebra de linha
            buscar_por_nome(lista, nome);
            break;
        }
        case '2': {
            char cpf[15];
            printf("Digite o CPF: ");
            scanf("%s", cpf); // Lê uma string sem espaços
            buscar_por_cpf(lista, cpf);
            break;
        }
        case '3':
            return;
        default:
            printf("Opção inválida!\n");
            return;
    }

    // if (resultado) {
    //     printf("\nID  CPF            Nome                           Idade  Data Cadastro\n");
    //     imprimir_paciente(resultado->paciente);
    //     printf("----------------------------------------------------------------\n");
    // } else {
    //     printf("Paciente não encontrado.\n");
    // }
}

static int maior_id(Lista* lista) {
    int id = 0;
    if (lista != NULL) {
        id = lista->ultimo->paciente->id + 1;
    }
    return id;
}
void cadastrar_paciente(Lista* lista) {
    printf("\n=== Inserir Paciente ===\n");

    // Declaração das variáveis
    char cpf[15], nome[100], data_cadastro[11];
    int idade;

    // Lê o CPF (não contém espaços, então %s é suficiente)
    printf("CPF (com pontuação): ");
    scanf("%14s", cpf);  // Lê até 14 caracteres e adiciona o terminador nulo

    // Lê o Nome (que pode conter espaços)
    // O espaço antes de %99[^\n] faz o scanf ignorar qualquer caractere em branco remanescente (como o \n)
    printf("Nome: ");
    scanf(" %99[^\n]", nome);  // Lê até 99 caracteres ou até encontrar uma nova linha

    // Lê a Idade
    printf("Idade: ");
    scanf("%d", &idade);

    // Lê a Data (como a data não contém espaços, %s é adequado)
    printf("Data (AAAA-MM-DD): ");
    scanf("%10s", data_cadastro);  // Lê até 10 caracteres

    // Valida os dados
    // if (!validar_cpf(cpf) || !validar_data(data_cadastro)) {
    //     printf("Dados inválidos!\n");
    //     return;
    // }

    // Cria e insere o paciente
    Paciente* p = criar_paciente(maior_id(lista), cpf, nome, idade, data_cadastro);
    inserir_paciente(lista, p);
    printf("Paciente inserido com sucesso!\n");
}

void menu(Lista* lista) {
    char opcao;
    do {
        exibir_menu();
        scanf(" %c", &opcao);
        // limpar_buffer();

        switch (opcao) {
            case '1':
                consultar_paciente(lista);
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
                cadastrar_paciente(lista);
                break;
            case '5':
                imprimir_lista(lista);
                break;
            case 'Q':
            case 'q':
                printf("Salvando dados e encerrando...\n");
                salvar_bd(lista);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 'Q' && opcao != 'q');
}