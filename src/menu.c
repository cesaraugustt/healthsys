#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "validacao.h"

/**
 * Limpa o buffer de entrada até encontrar um caractere de quebra de linha (\n) ou o final do arquivo (EOF).
 *
 * Essa função é necessária pois as funções de leitura como scanf() e fgets() podem deixar caracteres no buffer de entrada.
 */
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

int consultar_paciente(Lista* lista) {
    if (lista == NULL) {
        fprintf(stderr, "Erro: lista nula!\n");
        return 0;
    }

    printf("\nEscolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
    printf("Opção: ");

    char opcao;
    if (scanf(" %c", &opcao) != 1) {
        printf("Erro ao ler a opção!\n");
        return 0;
    }
    limpar_buffer();  // Limpa o buffer de entrada

    switch (opcao) {
        case '1': {
            char nome[100];
            printf("Digite o nome: ");
            // Lê uma string com espaços até a quebra de linha
            if (scanf(" %[^\n]", nome) != 1) {
                printf("Erro ao ler o nome!\n");
                return 0;
            }
            limpar_buffer();
            return buscar_por_nome(lista, nome);
        }
        case '2': {
            char cpf[15];
            printf("Digite o CPF (apenas números): ");
            if (scanf("%14s", cpf) != 1) {  // Limita a 14 caracteres para segurança
                printf("Erro ao ler o CPF!\n");
                return 0;
            }
            limpar_buffer();

            // Validação do CPF
            if (!validar_cpf(cpf)) {
                printf("CPF inválido!\n");
                return 0;
            }

            // Formata o CPF para o padrão "XXX.XXX.XXX-XX"
            char cpf_formatado[15];
            formatar_cpf(cpf, cpf_formatado);

            // Realiza a busca utilizando o CPF formatado
            return buscar_por_cpf(lista, cpf_formatado);
        }
        case '3':
            // Retorna ao menu principal sem realizar consulta
            return 0;
        default:
            printf("Opção inválida!\n");
            return 0;
    }
    return 0;
}

static int maior_id(Lista* lista) {
    int id = 1;  // Valor padrão para lista vazia
    if (lista != NULL && lista->ultimo != NULL) {
        id = lista->ultimo->paciente->id + 1;  // Incrementa o maior ID encontrado
    }
    return id;
}

void cadastrar_paciente(Lista* lista) {
    printf("\n=== Inserir Paciente ===\n");
    
    char cpf_numeros[12], cpf_formatado[15];
    char nome[100], data_input[9], data_cadastro[11];
    int idade;

    // Lê e valida CPF
    do {
        printf("CPF (apenas números): ");
        scanf("%11s", cpf_numeros);
        limpar_buffer();
        
        // Verifica se o CPF é válido
        if (!validar_cpf(cpf_numeros)) {
            printf("CPF inválido!\n");
            continue;
        }
        
        // Formata o CPF para o padrão com pontuação
        formatar_cpf(cpf_numeros, cpf_formatado);
        break;
    } while (1);

    // Lê o nome do paciente
    printf("Nome: ");
    scanf(" %99[^\n]", nome);
    limpar_buffer();

    // Lê e valida idade
    do {
        printf("Idade: ");
        if (scanf("%d", &idade) != 1) {
            printf("Por favor, digite um número válido.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();
        
        // Verifica se a idade está dentro dos limites permitidos
        if (!validar_idade(idade)) {
            printf("Idade inválida! Digite um valor entre 0 e 150.\n");
            continue;
        }
        break;
    } while (1);

    // Lê e valida data de cadastro
    do {
        printf("Data (AAAAMMDD): ");
        scanf("%8s", data_input);
        limpar_buffer();
        
        // Verifica se a data está no formato correto e é válida
        if (!validar_data(data_input)) {
            printf("Data inválida! Use o formato AAAAMMDD (ex: 20240207).\n");
            continue;
        }
        
        // Formata a data para o padrão AAAA-MM-DD
        sprintf(data_cadastro, "%.4s-%.2s-%.2s", 
                data_input, data_input + 4, data_input + 6);
        break;
    } while (1);

    // Cria e insere o paciente na lista
    Paciente* p = criar_paciente(maior_id(lista), cpf_formatado, nome, idade, data_cadastro);
    if (p != NULL) {
        inserir_paciente(lista, p);
        printf("\nPaciente cadastrado com sucesso!\n");
        printf("%-4s %-15s %-30s %-6s %s\n", 
               "ID", "CPF", "Nome", "Idade", "Data Cadastro");
        imprimir_paciente(p);
    } else {
        printf("Erro ao criar paciente!\n");
    }
}

void remover_paciente_menu(Lista* lista) {
    printf("\n=== Remover Paciente ===\n");
    if (!consultar_paciente(lista)) return;

    int id;
    printf("Digite o ID do paciente a ser removido: ");
    if (scanf("%d", &id) != 1) {
        printf("ID inválido!\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    char confirmacao;
    printf("Tem certeza? (S/N): ");
    if (scanf(" %c", &confirmacao) != 1 || (confirmacao != 'S' && confirmacao != 's')) {
        printf("Operação cancelada.\n");
        return;
    }
    limpar_buffer();

    remover_paciente(lista, id);
}

void atualizar_paciente_menu(Lista* lista) {
    printf("\n=== Atualizar Paciente ===\n");
    if (!consultar_paciente(lista)) return;

    int id;
    printf("Digite o ID do paciente a ser atualizado: ");
    if (scanf("%d", &id) != 1) {
        printf("Erro na leitura do ID. Tente novamente.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    // Busca o paciente a ser atualizado na lista
    No* atual = lista->primeiro;
    while (atual && atual->paciente->id != id) {
        atual = atual->proximo;
    }

    if (!atual) {
        printf("ID inválido!\n");
        return;
    }

    Paciente* paciente = atual->paciente;
    if (!paciente) {
        printf("Erro: paciente nulo!\n");
        return;
    }

    char input[100];
    char novo_cpf[15], novo_nome[100], nova_data[11];
    int nova_idade;

    // Lê o novo CPF (ou mantém o atual se o usuário digitar '-')
    printf("Novo CPF (apenas números, atual: %s | '-' para manter): ", paciente->cpf);
    if (scanf(" %14s", input) != 1) {
        printf("Erro na leitura do CPF. Tente novamente.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    if (strcmp(input, "-") != 0) {
        // Verifica se o CPF é válido antes de formatar
        if (!validar_cpf(input)) {
            printf("CPF inválido!\n");
            return;
        }
        // Formata o CPF para o padrão "XXX.XXX.XXX-XX"
        formatar_cpf(input, novo_cpf);
    } else {
        strcpy(novo_cpf, paciente->cpf);
    }

    // Lê o novo nome (ou mantém o atual se o usuário digitar '-')
    printf("Novo nome (atual: %s | '-' para manter): ", paciente->nome);
    if (scanf(" %99[^\n]", input) != 1) {
        printf("Erro na leitura do nome. Tente novamente.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    if (strcmp(input, "-")) {
        strcpy(novo_nome, input);
    } else {
        strcpy(novo_nome, paciente->nome);
    }

    // Lê a nova idade (ou mantém a atual se o usuário digitar '-')
    printf("Nova idade (atual: %d | '-' para manter): ", paciente->idade);
    if (scanf(" %99s", input) != 1) {
        printf("Erro na leitura da idade. Tente novamente.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    if (strcmp(input, "-")) {
        int idade_temp = atoi(input);
        if (validar_idade(idade_temp)) {
            nova_idade = idade_temp;
        } else {
            printf("Idade inválida!\n");
            return;
        }
    } else {
        nova_idade = paciente->idade;
    }

    // Lê a nova data (ou mantém a atual se o usuário digitar '-')
    printf("Nova data (formato AAAAMMDD, atual: %s | '-' para manter): ", paciente->data_cadastro);
    if (scanf(" %10s", input) != 1) {
        printf("Erro na leitura da data. Tente novamente.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    if (strcmp(input, "-") && validar_data(input)) {
        sprintf(nova_data, "%.4s-%.2s-%.2s", input, input + 4, input + 6);
    } else {
        strcpy(nova_data, paciente->data_cadastro);
    }

    // Atualiza os dados do paciente
    atualizar_paciente(paciente, novo_cpf, novo_nome, nova_idade, nova_data);
}

void menu(Lista* lista) {
    char opcao;

    // Verifica se a lista foi inicializada corretamente
    if (lista == NULL) {
        printf("Erro: lista não inicializada!\n");
        return;
    }

    do {
        exibir_menu();

        // Lê a opção escolhida pelo usuário (apenas o primeiro caractere)
        if (scanf(" %c", &opcao) != 1) {
            printf("Erro na leitura da opção. Tente novamente.\n");
            limpar_buffer();
            continue;  // Retorna ao início do loop
        }
        limpar_buffer();  // Limpa o buffer de entrada

        // Executa a ação correspondente à opção escolhida
        switch (opcao) {
            case '1':
                consultar_paciente(lista);  // Consulta um paciente
                break;
            case '2':
                atualizar_paciente_menu(lista);  // Atualiza os dados de um paciente
                break;
            case '3':
                remover_paciente_menu(lista);  // Remove um paciente da lista
                break;
            case '4':
                cadastrar_paciente(lista);  // Cadastra um novo paciente
                break;
            case '5':
                // Verifica se a lista de pacientes está vazia
                if (lista->primeiro == NULL) {
                    printf("\nLista de pacientes está vazia.\n");
                } else {
                    imprimir_lista(lista);  // Imprime a lista de pacientes
                }
                break;
            case 'Q':
            case 'q':
                printf("Salvando dados e encerrando...\n");
                salvar_bd(lista);  // Salva os dados no banco de dados
                return;  // Encerra a função
            default:
                printf("Opção inválida! Por favor, escolha uma opção do menu.\n");
        }
    } while (opcao != 'Q' && opcao != 'q');  // Continua até que o usuário escolha sair
}