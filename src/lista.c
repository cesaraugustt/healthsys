#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"
#include "paciente.h"

static No* criar_no(Paciente* paciente) {
    if (paciente == NULL) {
        fprintf(stderr, "Erro ao criar nó: paciente nulo\n");
        return NULL;
    }

    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o nó!\n");
        return NULL;
    }

    /* Inicializa o novo nó com o paciente informado e todos os ponteiros
     * nulos. */
    novo_no->paciente = paciente;
    novo_no->anterior = NULL;
    novo_no->proximo = NULL;

    return novo_no;
}

Lista* criar_lista() {
    Lista* nova_lista = (Lista*)malloc(sizeof(Lista));
    if (nova_lista == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a lista!\n");
        exit(EXIT_FAILURE);
    }
    nova_lista->primeiro = NULL;
    nova_lista->ultimo = NULL;
    
    return nova_lista;
}

void inserir_paciente(Lista* lista, Paciente* paciente) {
    if (lista == NULL || paciente == NULL) {
        fprintf(stderr, "Erro ao inserir paciente: lista ou paciente nulo\n");
        return;
    }

    No* no = criar_no(paciente);
    if (no == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o nó!\n");
        return;
    }

    // Se a lista estiver vazia, o novo nó será o primeiro e o último
    if (lista->ultimo == NULL) { 
        lista->primeiro = lista->ultimo = no;
    } else {
        // Adiciona no final da lista
        no->anterior = lista->ultimo;
        lista->ultimo->proximo = no;
        lista->ultimo = no;
    }
}

void remover_paciente(Lista* lista, int id) {
    if (lista == NULL) {
        fprintf(stderr, "Erro: lista nula.\n");
        return;
    }

    No* atual = lista->primeiro;
    No* anterior = NULL;
    // Percorre a lista ate encontrar o paciente com o ID especificado
    while (atual != NULL && atual->paciente->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    // Atualiza os ponteiros para remover o paciente da lista
    if (anterior == NULL) {
        // O paciente a ser removido é o primeiro da lista
        lista->primeiro = atual->proximo;
    } else {
        // O paciente a ser removido é um nodo intermediario
        anterior->proximo = atual->proximo;
    }

    if (atual->proximo == NULL) {
        // O paciente a ser removido é o ultimo da lista
        lista->ultimo = anterior;
    } else {
        // O paciente a ser removido é um nodo intermediario
        atual->proximo->anterior = anterior;
    }

    // Libera a memoria do paciente e do no
    liberar_paciente(atual->paciente);
    free(atual);
    printf("Paciente removido com sucesso.\n");
}

void imprimir_lista(Lista* lista) {
    if (lista == NULL) {
        fprintf(stderr, "Erro: lista nula.\n");
        return;
    }

    No* no_atual = lista->primeiro;
    if (no_atual == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    // Conta o total de registros
    int total_registros = 0;
    No* temp = lista->primeiro;
    while (temp != NULL) {
        total_registros++;
        temp = temp->proximo;
    }

    int pagina_atual = 1;
    int total_paginas = (total_registros + REGISTROS_POR_PAGINA - 1) / REGISTROS_POR_PAGINA;
    char opcao;

    do {
        system("clear"); // Limpa a tela (use "cls" no Windows)
        printf("\n=== Lista de Pacientes (Página %d/%d) ===\n\n", pagina_atual, total_paginas);
        
        // Imprime o cabeçalho da tabela
        printf("%-4s %-15s %-30s %-6s %s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");

        // Calcula a posição inicial para a página atual
        No* inicio = lista->primeiro;
        for (int i = 0; i < (pagina_atual - 1) * REGISTROS_POR_PAGINA && inicio != NULL; i++) {
            inicio = inicio->proximo;
        }

        // Imprime os registros da página atual
        No* atual = inicio;
        int registros_impressos = 0;
        while (atual != NULL && registros_impressos < REGISTROS_POR_PAGINA) {
            if (atual->paciente != NULL) {
                imprimir_paciente(atual->paciente);
            }
            atual = atual->proximo;
            registros_impressos++;
        }

        printf("\nTotal de registros: %d\n", total_registros);
        printf("\nOpções:\n");
        printf("A - Página anterior\n");
        printf("P - Próxima página\n");
        printf("S - Sair\n");
        printf("Escolha uma opção: ");
        
        scanf(" %c", &opcao);
        opcao = toupper(opcao);

        switch (opcao) {
            case 'A':
                if (pagina_atual > 1) pagina_atual--;
                break;
            case 'P':
                if (pagina_atual < total_paginas) pagina_atual++;
                break;
        }
    } while (opcao != 'S');
}

void liberar_lista(Lista* lista) {
    /* Percorre a lista e libera a memória de cada paciente e seu respectivo
     * nó. */
    No* atual = lista->primeiro;
    while (atual) {
        No* proximo = atual->proximo;
        liberar_paciente(atual->paciente);
        free(atual);
        atual = proximo;
    }

    /* Libera a memória alocada para a lista em si. */
    free(lista);
}

static void to_lower(char* str, char* result) {
    int i;
    for (i = 0; str[i]; i++) {
        result[i] = tolower(str[i]);  // Converte o caractere para minúsculas
    }
    result[i] = '\0';  // Termina a string com um caractere nulo
}

int buscar_por_nome(Lista* lista, const char* nome) {
    if (lista == NULL || nome == NULL) {
        fprintf(stderr, "Erro: lista ou nome de busca inválido\n");
        return 0;
    }

    char nome_lower[100];
    char nome_paciente_lower[100];
    // Converte o nome para minúsculas para que a busca seja case-insensitive
    to_lower((char*)nome, nome_lower);

    No* atual = lista->primeiro;
    int encontrou = 0;

    while (atual != NULL) {
        // Converte o nome do paciente para minúsculas para que a busca seja case-insensitive
        to_lower(atual->paciente->nome, nome_paciente_lower);
        
        if (strstr(nome_paciente_lower, nome_lower) != NULL) {
            if (!encontrou) {
                // Só imprime o cabeçalho se encontrou algum resultado
                printf("%-4s %-15s %-30s %-6s %s\n", 
                       "ID", "CPF", "Nome", "Idade", "Data Cadastro");
            }
            // Imprime os dados do paciente encontrado
            imprimir_paciente(atual->paciente);
            encontrou = 1;
        }
        atual = atual->proximo;
    }

    if (!encontrou) {
        // Informa que nenhuma pessoa foi encontrada com o nome especificado
        printf("\nNenhum paciente encontrado com o nome '%s'\n", nome);
        return 0;
    }

    return 1;
}

int buscar_por_cpf(Lista* lista, const char* cpf) {
    if (lista == NULL || cpf == NULL) {
        fprintf(stderr, "Erro: lista ou CPF de busca inválido\n");
        return 0;
    }

    No* atual = lista->primeiro;
    int encontrou = 0;

    // Percorre a lista e busca o paciente com o CPF especificado
    while (atual != NULL) {
        // Verifica se o CPF do paciente é igual ao CPF de busca
        if (strcmp(atual->paciente->cpf, cpf) == 0) {
            if (!encontrou) {
                // Imprime o cabeçalho da tabela
                printf("%-4s %-15s %-30s %-6s %s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");
                encontrou = 1;
            }
            imprimir_paciente(atual->paciente);
        }
        atual = atual->proximo;
    }

    // Se nenhuma ocorrência do CPF for encontrada, imprime uma mensagem
    if (!encontrou) {
        printf("\nNenhum paciente encontrado com o CPF '%s'\n", cpf);
        return 0;
    }

    return 1;
}
