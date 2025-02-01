#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"
#include "lista.h"
#include "utils.h"

// Função para limpar o buffer de entrada
static void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Exibe o menu principal
void exibir_menu() {
    printf("\n=== Sistema de Gerenciamento de Pacientes ===\n");
    printf("1. Consultar paciente\n");
    printf("2. Atualizar paciente\n");
    printf("3. Remover paciente\n");
    printf("4. Inserir paciente\n");
    printf("5. Imprimir lista de pacientes\n");
    printf("Q. Sair\n");
    printf("Escolha uma opção: ");
}

// Processa a opção selecionada pelo usuário
void processar_opcao(Lista* lista) {
    char opcao;
    scanf(" %c", &opcao);
    limpar_buffer();

    switch (toupper(opcao)) {
        case '1':
            consultar_paciente(lista);
            break;
        case '2':
            atualizar_paciente(lista);
            break;
        case '3':
            remover_paciente(lista);
            break;
        case '4':
            inserir_paciente_menu(lista);
            break;
        case '5':
            imprimir_lista_pacientes(lista);
            break;
        case 'Q':
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opção inválida!\n");
    }
}

// Funcionalidade de consulta
void consultar_paciente(Lista* lista) {
    printf("\n=== Consultar Paciente ===\n");
    printf("1. Buscar por nome\n");
    printf("2. Buscar por CPF\n");
    printf("3. Voltar\n");
    printf("Escolha o modo de busca: ");

    char opcao;
    scanf(" %c", &opcao);
    limpar_buffer();

    if (opcao == '3') return;

    if (opcao == '1') {
        char nome[100];
        printf("Digite o nome: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0'; // Remove a quebra de linha

        No* atual = lista->inicio;
        int encontrados = 0;

        printf("\nResultados da busca:\n");
        while (atual != NULL) {
            if (strstr(atual->paciente->nome, nome) != NULL) {
                imprimir_paciente(atual->paciente);
                encontrados++;
            }
            atual = atual->proximo;
        }

        if (encontrados == 0) {
            printf("Nenhum paciente encontrado.\n");
        }

    } else if (opcao == '2') {
        char cpf[15];
        printf("Digite o CPF (com pontuação): ");
        fgets(cpf, sizeof(cpf), stdin);
        cpf[strcspn(cpf, "\n")] = '\0';

        Paciente* p = buscar_paciente_por_cpf(lista, cpf);
        if (p != NULL) {
            imprimir_paciente(p);
        } else {
            printf("Paciente não encontrado.\n");
        }
    }
}

// Funcionalidade de atualização
void atualizar_paciente(Lista* lista) {
    printf("\n=== Atualizar Paciente ===\n");
    imprimir_lista_pacientes(lista);

    int id;
    printf("Digite o ID do paciente a ser atualizado: ");
    scanf("%d", &id);
    limpar_buffer();

    No* atual = lista->inicio;
    Paciente* paciente = NULL;

    // Busca o paciente pelo ID
    while (atual != NULL) {
        if (atual->paciente->id == id) {
            paciente = atual->paciente;
            break;
        }
        atual = atual->proximo;
    }

    if (paciente == NULL) {
        printf("ID inválido!\n");
        return;
    }

    // Solicita novos valores
    char novo_cpf[15], novo_nome[100], nova_data[11], temp[100];
    int nova_idade;

    printf("Novo CPF (atual: %s | '-' para manter): ", paciente->cpf);
    fgets(novo_cpf, sizeof(novo_cpf), stdin);
    novo_cpf[strcspn(novo_cpf, "\n")] = '\0';

    printf("Novo nome (atual: %s | '-' para manter): ", paciente->nome);
    fgets(novo_nome, sizeof(novo_nome), stdin);
    novo_nome[strcspn(novo_nome, "\n")] = '\0';

    printf("Nova idade (atual: %d | '-' para manter): ", paciente->idade);
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';

    printf("Nova data (atual: %s | '-' para manter): ", paciente->data_cadastro);
    fgets(nova_data, sizeof(nova_data), stdin);
    nova_data[strcspn(nova_data, "\n")] = '\0';

    // Atualiza os campos (se não for '-')
    if (strcmp(novo_cpf, "-") != 0) {
        if (validar_cpf(novo_cpf)) {
            strcpy(paciente->cpf, novo_cpf);
        } else {
            printf("CPF inválido!\n");
            return;
        }
    }

    if (strcmp(novo_nome, "-") != 0) {
        strcpy(paciente->nome, novo_nome);
    }

    if (strcmp(temp, "-") != 0) {
        nova_idade = atoi(temp);
        paciente->idade = nova_idade;
    }

    if (strcmp(nova_data, "-") != 0) {
        if (validar_data(nova_data)) {
            strcpy(paciente->data_cadastro, nova_data);
        } else {
            printf("Data inválida!\n");
            return;
        }
    }

    printf("Paciente atualizado com sucesso!\n");
}

// Funcionalidade de remoção
void remover_paciente(Lista* lista) {
    printf("\n=== Remover Paciente ===\n");
    imprimir_lista_pacientes(lista);

    int id;
    printf("Digite o ID do paciente a ser removido: ");
    scanf("%d", &id);
    limpar_buffer();

    char confirmacao;
    printf("Tem certeza? (S/N): ");
    scanf(" %c", &confirmacao);

    if (toupper(confirmacao) == 'S') {
        remover_paciente_por_id(lista, id); // Função a ser implementada na lista
        printf("Paciente removido!\n");
    } else {
        printf("Operação cancelada.\n");
    }
}

// Funcionalidade de inserção
void inserir_paciente_menu(Lista* lista) {
    printf("\n=== Inserir Paciente ===\n");

    // Gera o próximo ID
    int novo_id = 1;
    No* atual = lista->inicio;
    while (atual != NULL) {
        if (atual->paciente->id >= novo_id) {
            novo_id = atual->paciente->id + 1;
        }
        atual = atual->proximo;
    }

    // Coleta os dados
    char cpf[15], nome[100], data[11];
    int idade;

    printf("CPF (com pontuação): ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &idade);
    limpar_buffer();

    printf("Data (AAAA-MM-DD): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';

    // Valida os dados
    if (!validar_cpf(cpf) || !validar_data(data)) {
        printf("Dados inválidos!\n");
        return;
    }

    // Cria e insere o paciente
    Paciente* p = criar_paciente(novo_id, cpf, nome, idade, data);
    inserir_paciente(lista, p);
    printf("Paciente inserido com sucesso!\n");
}

// Funcionalidade de impressão da lista
void imprimir_lista_pacientes(Lista* lista) {
    printf("\n=== Lista de Pacientes ===\n");
    printf("ID | CPF           | Nome              | Idade | Data Cadastro\n");
    printf("--------------------------------------------------------------\n");

    No* atual = lista->inicio;
    while (atual != NULL) {
        Paciente* p = atual->paciente;
        printf("%-2d | %-13s | %-17s | %-5d | %s\n",
               p->id, p->cpf, p->nome, p->idade, p->data_cadastro);
        atual = atual->proximo;
    }
}