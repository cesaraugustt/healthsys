#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"
#include "menu.h"

extern BDPaciente* bd;

void consultar_paciente() {
    int opcao_consulta;
    do {
        printf("\nEscolha o modo de consulta:\n");
        printf("1 - Por nome\n");
        printf("2 - Por CPF\n");
        printf("3 - Retornar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao_consulta);

        switch (opcao_consulta) {
            case 1: {
                char nome[100];
                printf("Digite o nome do paciente: ");
                scanf(" %[^\n]", nome);

                Paciente* paciente = buscar_paciente_por_nome(bd, nome);
                if (paciente) {
                    printf("\nPaciente encontrado:\n");
                    imprimir_paciente(paciente);
                } else {
                    printf("\nPaciente não encontrado.\n");
                }
                break;
            }

            case 2: {
            char cpf[15];
            printf("Digite o CPF do paciente (apenas dígitos): ");
            scanf(" %s", cpf);

            Paciente* paciente = buscar_paciente_por_cpf(bd, cpf);
            if (paciente) {
                printf("\nPaciente encontrado:\n");
                imprimir_paciente(paciente);
            } else {
                printf("\nPaciente não encontrado.\n");
            }
            break;
            }

            case 3: { 
                printf("\nRetornand ao menu principal...\n");
                return;
            }

            default: {
                printf("\nOpção inválida! Tente novamente.\n");
                break;
            }
        }
    } while (1);
}

void exibir_menu() {
    printf("\nHealthSys - Sistema de Gerenciamento de Pacientes\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir paciente\n");
    printf("5 - Imprimir lista de pacientes\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

void processar_opcao(int opcao) {
    switch (opcao)
    {
        case 1: {
            consultar_paciente();
            break;
        }

        case 2: {
            int id;
            printf("Digite o ID do paciente a ser atualizado: ");
            scanf("%d", id);

            // Busca paciente pelo ID
            Paciente* paciente = NULL;
            Node* atual = bd->inicio;
            while (atual) {
                if (atual->paciente->id == id) {
                    paciente = atual->paciente;
                    break;
                }
                atual = atual->proximo;
            }

            if (paciente) {
                char cpf[15], nome[100], data_cadastro[11];
                int idade;

                printf("Digite o novo CPF (apenas dígitos, ou '-' para manter o atual): ");
                scanf(" %s", cpf);
                if (strcmp(cpf, "-") != 0) {
                    strncpy(paciente->cpf, cpf, 14);
                }

                printf("Digite o novo nome (ou '-' para manter o atual): ");
                scanf(" %[^\n]", nome);
                if (strcmp(nome, "-") != 0) {
                    strncpy(paciente->nome, nome, 99);
                }

                printf("Digite a nova idade (ou -1 para manter a atual): ");
                scanf("%d", &idade);
                if (idade != -1) {
                    paciente->idade = idade;
                }

                printf("Digite a nova data de cadastro (AAAA-MM-DD, ou '-' para manter a atual): ");
                scanf(" %s", data_cadastro);
                if (strcmp(data_cadastro, "-") != 0) {
                    strncpy(paciente->data_cadastro, data_cadastro, 10);
                }

                printf("\nPaciente atualizado com sucesso:\n");
                imprimir_paciente(paciente);
            } else {
                printf("\nPaciente não encontrado. \n");
            }
            break;
        }

        case 3: { // Remover paciente
            int id;
            printf("Digite o ID do paciente a ser removido: ");
            scanf("%d", &id);

            // Busca paciente pelo ID
            Paciente* paciente = NULL;
            Node* atual = bd->inicio;
            while (atual) {
                if (atual->paciente->id == id) {
                    paciente = atual->paciente;
                    break;
                }
                atual = atual->proximo;
            }

            if (paciente) {
                char confirmacao;
                printf("\nTem certeza de que deseha remover o paciene abaixo? (S/N)\n");
                imprimir_paciente(paciente);
                scanf(" %c", &confirmacao);

                if (confirmacao == 'S' || confirmacao == 's') {
                    remover_paciente(bd, id);
                    printf("\nPaciente removido com sucesso.\n");
                } else {
                    printf("\nRemoção cancelada.\n");
                }
            } else {
                printf("\nPaciente não encontrado.\n");
            }
            break;
        }

        case 4: {
            char cpf[15], nome[100], data_cadastro[11];
            int idade;

            printf("Digite o CPF do novo paciente (apenas dígitos): ");
            scanf(" %s", cpf);

            printf("Digite o nome do novo paciente: ");
            scanf(" %[^\n]", nome);

            printf("Digite a idade do novo paciente: ");
            scanf("%d", &idade);

            printf("Digite a data de cadastro do novo paciente (AAAA-MM-DD): ");
            scanf(" %s", data_cadastro);

            Paciente* novo_paciente = criar_paciente(0, cpf, nome, idade, data_cadastro):
            if (novo_paciente) {
                inserir_paciente(bd, novo_paciente);
                printf("\nPaciente inserido com sucesso:\n");
                imprimir_paciente(novo_paciente);
            } else {
                printf("\nErro ao criar paciente.\n");
            }
            break;
        }

        case 5: {
            printf("\nLista de pacientes:\n");
            imprimir_todos_pacientes(bd);
            break;
        }

        default: {
            printf("\nOpção inválida!\n");
            break;
        }
    }
}