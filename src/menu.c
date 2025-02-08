#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "validacao.h"

/**
 * Limpa o buffer de entrada até encontrar um caractere de quebra de linha
 * (\n) ou o final do arquivo (EOF).
 *
 * Essa função é necessária pois as funções de leitura como scanf() e fgets()
 * podem deixar caracteres no buffer de entrada.
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

void consultar_paciente(Lista* lista) {
    printf("\nEscolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
    printf("Opção: ");

    char opcao;
    if (scanf(" %c", &opcao) != 1) {
        printf("Erro ao ler a opção!\n");
        return;
    }
    limpar_buffer();  // Limpa o buffer de entrada

    switch (opcao) {
        case '1': {
            char nome[100];
            printf("Digite o nome: ");
            // Lê uma string com espaços até a quebra de linha
            if (scanf(" %[^\n]", nome) != 1) {
                printf("Erro ao ler o nome!\n");
                return;
            }
            limpar_buffer();
            buscar_por_nome(lista, nome);
            break;
        }
        case '2': {
            char cpf[15];
            printf("Digite o CPF (apenas números): ");
            if (scanf("%14s", cpf) != 1) {  // Limita a 14 caracteres para segurança
                printf("Erro ao ler o CPF!\n");
                return;
            }
            limpar_buffer();

            // Validação do CPF utilizando a função validar_cpf
            if (!validar_cpf(cpf)) {
                printf("CPF inválido!\n");
                return;
            }

            // Formata o CPF para o padrão "XXX.XXX.XXX-XX"
            char cpf_formatado[15];
            formatar_cpf(cpf, cpf_formatado);

            // Realiza a busca utilizando o CPF formatado
            buscar_por_cpf(lista, cpf_formatado);
            break;
        }
        case '3':
            // Retorna ao menu principal sem realizar consulta
            return;
        default:
            printf("Opção inválida!\n");
            return;
    }
}

static int maior_id(Lista* lista) {
    int id = 1;  // Valor padrão para lista vazia
    if (lista != NULL) {
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
            printf("CPF inválido! Digite exatamente 11 números.\n");
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
    // Mostra a lista de pacientes
    consultar_paciente(lista);

    int id;
    printf("Digite o ID do paciente a ser removido: ");
    scanf("%d", &id);
    limpar_buffer();

    char confirmacao;
    printf("Tem certeza? (S/N): ");
    scanf(" %c", &confirmacao);
    // limpar_buffer();

    // Confirma se o usuário tem certeza da operação
    if (confirmacao == 'S' || confirmacao == 's') {
        // Remove o paciente da lista
        remover_paciente(lista, id);
    } else {
        printf("Operação cancelada.\n");
    }
}

void atualizar_paciente_menu(Lista* lista) {
    printf("\n=== Atualizar Paciente ===\n");
    consultar_paciente(lista);

    int id;
    printf("Digite o ID do paciente a ser atualizado: ");
    scanf("%d", &id);
    limpar_buffer();

    // Busca o paciente pelo ID na lista
    No* atual = lista->primeiro;
    Paciente* paciente = NULL;
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

    char novo_cpf[15];
    char novo_nome[100];
    char nova_data[11];
    char idade_str[100];
    int nova_idade;

    // Lê os novos dados informados pelo usuário
    printf("Novo CPF (apenas números, atual: %s | '-' para manter): ", paciente->cpf);
    scanf(" %14s", novo_cpf);
    limpar_buffer();

    printf("Novo nome (atual: %s | '-' para manter): ", paciente->nome);
    scanf(" %99[^\n]", novo_nome);
    limpar_buffer();

    printf("Nova idade (atual: %d | '-' para manter): ", paciente->idade);
    scanf(" %99s", idade_str);
    limpar_buffer();

    printf("Nova data (formato AAAAMMDD, atual: %s | '-' para manter): ", paciente->data_cadastro);
    scanf(" %10s", nova_data);
    limpar_buffer();

    // Validação do CPF (somente se for alterado)
    if (strcmp(novo_cpf, "-") != 0) {
        if (!validar_cpf(novo_cpf)) {
            printf("CPF inválido!\n");
            return;
        }
        // Opcional: formata o CPF para exibição (por exemplo, 12345678909 -> 123.456.789-09)
        char cpf_formatado[15];
        formatar_cpf(novo_cpf, cpf_formatado);
        strcpy(novo_cpf, cpf_formatado);
    } else {
        strcpy(novo_cpf, paciente->cpf);
    }

    // Validação do nome (se for mantido, utiliza o atual)
    if (strcmp(novo_nome, "-") == 0) {
        strcpy(novo_nome, paciente->nome);
    }

    // Validação da idade
    if (strcmp(idade_str, "-") == 0) {
        nova_idade = paciente->idade;
    } else {
        nova_idade = atoi(idade_str);
        if (!validar_idade(nova_idade)) {
            printf("Idade inválida! A idade deve estar entre 0 e 150.\n");
            return;
        }
    }

    // Validação da data
    if (strcmp(nova_data, "-") != 0) {
        if (!validar_data(nova_data)) {
            printf("Data inválida! Verifique se o formato (AAAAMMDD) e os valores estão corretos.\n");
            return;
        }
    } else {
        strcpy(nova_data, paciente->data_cadastro);
    }

    // Atualiza o paciente com os novos dados validados
    atualizar_paciente(paciente, novo_cpf, novo_nome, nova_idade, nova_data);
}

void menu(Lista* lista) {
    char opcao;
    if (lista == NULL) {
        printf("Erro: lista não inicializada!\n");
        return;
    }

    do {
        exibir_menu();
        
        // Lê apenas o primeiro caractere
        if (scanf(" %c", &opcao) != 1) {
            printf("Erro na leitura da opção. Tente novamente.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case '1':
                consultar_paciente(lista);
                break;
            case '2':
                atualizar_paciente_menu(lista);
                break;
            case '3':
                remover_paciente_menu(lista);
                break;
            case '4':
                cadastrar_paciente(lista);
                break;
            case '5':
                if (lista->primeiro == NULL) {
                    printf("\nLista de pacientes está vazia.\n");
                } else {
                    imprimir_lista(lista);
                }
                break;
            case 'Q':
            case 'q':
                printf("Salvando dados e encerrando...\n");
                salvar_bd(lista);
                return;
            default:
                printf("Opção inválida! Por favor, escolha uma opção do menu.\n");
        }
        
        printf("\nPressione ENTER para continuar...");
        getchar();
        
    } while (opcao != 'Q' && opcao != 'q');
}