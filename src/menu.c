#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "utils.h"

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

void consultar_paciente(BDPaciente* bd) {
    printf("\nEscolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
    printf("Opção: ");

    char opcao;
    scanf(" %c", &opcao);
    limpar_buffer();

    Node* resultado = NULL;
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
            char cpf[15];
            printf("Digite o CPF (formato xxx.xxx.xxx-xx): ");
            fgets(cpf, sizeof(cpf), stdin);
            cpf[strcspn(cpf, "\n")] = 0;
            resultado = buscar_paciente_por_cpf(bd->lista, cpf);
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
        imprimir_paciente(&resultado->paciente);
    } else {
        printf("Paciente não encontrado.\n");
    }
}

void atualizar_paciente(BDPaciente* bd) {
    printf("\nPrimeiro, vamos localizar o paciente que deseja atualizar.\n");
    
    imprimir_pacientes(bd);
    
    int id;
    printf("\nDigite o ID do registro a ser atualizado: ");
    scanf("%d", &id);
    limpar_buffer();

    Node* atual = bd->lista->inicio;
    while (atual && atual->paciente.id != id) {
        atual = atual->prox;
    }

    if (!atual) {
        printf("Paciente não encontrado!\n");
        return;
    }

    printf("\nDigite o novo valor para os campos (ou '-' para manter o valor atual):\n");
    
    char cpf[15], nome[100], data[11];
    int idade;

    printf("CPF atual: %s\nNovo CPF (xxx.xxx.xxx-xx): ", atual->paciente.cpf);
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;

    printf("Nome atual: %s\nNovo nome: ", atual->paciente.nome);
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Idade atual: %d\nNova idade: ", atual->paciente.idade);
    char idade_str[10];
    fgets(idade_str, sizeof(idade_str), stdin);
    idade_str[strcspn(idade_str, "\n")] = 0;

    printf("Data atual: %s\nNova data (AAAA-MM-DD): ", atual->paciente.data_cadastro);
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = 0;

    Paciente temp = atual->paciente;
    if (strcmp(cpf, "-") != 0 && validar_cpf(cpf)) strcpy(temp.cpf, cpf);
    if (strcmp(nome, "-") != 0) strcpy(temp.nome, nome);
    if (strcmp(idade_str, "-") != 0) temp.idade = atoi(idade_str);
    if (strcmp(data, "-") != 0 && validar_data(data)) strcpy(temp.data_cadastro, data);

    printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n");
    printf("ID  CPF            Nome                           Idade  Data Cadastro\n");
    printf("----------------------------------------------------------------\n");
    imprimir_paciente(&temp);

    char confirma;
    scanf(" %c", &confirma);
    limpar_buffer();

    if (confirma == 'S' || confirma == 's') {
        atual->paciente = temp;
        salvar_bd(bd);
        printf("Registro atualizado com sucesso.\n");
    } else {
        printf("Operação cancelada.\n");
    }
}

void remover_paciente(BDPaciente* bd) {
    printf("\nPrimeiro, vamos localizar o paciente que deseja remover.\n");
    
    imprimir_pacientes(bd);
    
    int id;
    printf("\nDigite o ID do registro a ser removido: ");
    scanf("%d", &id);
    limpar_buffer();

    Node* atual = bd->lista->inicio;
    while (atual && atual->paciente.id != id) {
        atual = atual->prox;
    }

    if (!atual) {
        printf("Paciente não encontrado!\n");
        return;
    }

    printf("\nTem certeza que deseja excluir o registro abaixo? (S/N)\n");
    printf("ID  CPF            Nome                           Idade  Data Cadastro\n");
    printf("----------------------------------------------------------------\n");
    imprimir_paciente(&atual->paciente);

    char confirma;
    scanf(" %c", &confirma);
    limpar_buffer();

    if (confirma == 'S' || confirma == 's') {
        remover_paciente_lista(bd->lista, id);
        salvar_bd(bd);
        printf("Registro removido com sucesso.\n");
    } else {
        printf("Operação cancelada.\n");
    }
}

void inserir_paciente(BDPaciente* bd) {
    Paciente novo;
    char cpf[15], nome[100], data[11];

    // Gerar novo ID
    int maior_id = 0;
    Node* atual = bd->lista->inicio;
    while (atual != NULL) {
        if (atual->paciente.id > maior_id) {
            maior_id = atual->paciente.id;
        }
        atual = atual->prox;
    }
    novo.id = maior_id + 1;

    printf("\nPara inserir um novo registro, digite os valores para os campos:\n");

    do {
        printf("CPF (xxx.xxx.xxx-xx): ");
        fgets(cpf, sizeof(cpf), stdin);
        cpf[strcspn(cpf, "\n")] = 0;
    } while (!validar_cpf(cpf));
    strcpy(novo.cpf, cpf);

    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    strcpy(novo.nome, nome);

    printf("Idade: ");
    scanf("%d", &novo.idade);
    limpar_buffer();

    do {
        printf("Data de Cadastro (AAAA-MM-DD): ");
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = 0;
    } while (!validar_data(data));
    strcpy(novo.data_cadastro, data);

    printf("\nConfirma a inserção do registro abaixo? (S/N)\n");
    printf("ID  CPF            Nome                           Idade  Data Cadastro\n");
    printf("----------------------------------------------------------------\n");
    imprimir_paciente(&novo);

    char confirma;
    scanf(" %c", &confirma);
    limpar_buffer();

    if (confirma == 'S' || confirma == 's') {
        inserir_paciente_lista(bd->lista, novo);
        salvar_bd(bd);
        printf("Registro inserido com sucesso.\n");
    } else {
        printf("Operação cancelada.\n");
    }
}

void imprimir_pacientes(BDPaciente* bd) {
    imprimir_lista(bd->lista);
}