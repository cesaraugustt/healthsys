#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

// Remove caracteres não numéricos do CPF (pontuações)
static void remover_pontuacao_cpf(char* cpf_limpo, const char* cpf_com_pontuacao) {
    int j = 0;
    for (int i = 0; cpf_com_pontuacao[i] != '\0'; i++) {
        if (isdigit(cpf_com_pontuacao[i])) {
            cpf_limpo[j++] = cpf_com_pontuacao[i];
        }
    }
    cpf_limpo[j] = '\0';
}

// Valida se um CPF (com pontuação) é válido
int validar_cpf(const char* cpf_com_pontuacao) {
    char cpf[12]; // CPF sem pontuação (11 dígitos + '\0')
    remover_pontuacao_cpf(cpf, cpf_com_pontuacao);

    // Verifica se tem 11 dígitos
    if (strlen(cpf) != 11) {
        return 0;
    }

    // Verifica se todos os dígitos são iguais (CPF inválido)
    int todos_iguais = 1;
    for (int i = 1; i < 11; i++) {
        if (cpf[i] != cpf[0]) {
            todos_iguais = 0;
            break;
        }
    }
    if (todos_iguais) {
        return 0;
    }

    // Cálculo dos dígitos verificadores
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * (10 - i);
    }
    int primeiro_digito = (soma % 11 < 2) ? 0 : 11 - (soma % 11);

    if (primeiro_digito != (cpf[9] - '0')) {
        return 0;
    }

    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * (11 - i);
    }
    int segundo_digito = (soma % 11 < 2) ? 0 : 11 - (soma % 11);

    if (segundo_digito != (cpf[10] - '0')) {
        return 0;
    }

    return 1; // CPF válido
}

// Valida se uma data está no formato AAAA-MM-DD e é válida
int validar_data(const char* data) {
    // Verifica o formato usando sscanf
    int ano, mes, dia;
    if (sscanf(data, "%d-%d-%d", &ano, &mes, &dia) != 3) {
        return 0; // Formato inválido
    }

    // Valida ano (1900-2100 como exemplo)
    if (ano < 1900 || ano > 2100) {
        return 0;
    }

    // Valida mês
    if (mes < 1 || mes > 12) {
        return 0;
    }

    // Valida dia
    int dias_por_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajusta fevereiro para anos bissextos
    if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
        dias_por_mes[1] = 29;
    }

    if (dia < 1 || dia > dias_por_mes[mes - 1]) {
        return 0;
    }

    return 1; // Data válida
}