#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validacao.h"

#include <ctype.h>

int validar_cpf(const char* cpf) {
    // Verifica se tem exatamente 11 dígitos e apenas números
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }
    // Verifica se a string termina após 11 caracteres
    if (cpf[11] != '\0') {
        return 0;
    }

    // Verifica se todos os dígitos são iguais
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

    // Cálculo do primeiro dígito verificador
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * (10 - i);
    }
    int primeiro_digito = (soma % 11) < 2 ? 0 : 11 - (soma % 11);

    if (primeiro_digito != (cpf[9] - '0')) {
        return 0;
    }

    // Cálculo do segundo dígito verificador
    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * (11 - i);
    }
    int segundo_digito = (soma % 11) < 2 ? 0 : 11 - (soma % 11);

    if (segundo_digito != (cpf[10] - '0')) {
        return 0;
    }

    return 1;
}

void formatar_cpf(const char* cpf_entrada, char* cpf_formatado) {
    // Formata o CPF no padr o "XXX.XXX.XXX-XX"
    sprintf(cpf_formatado, "%c%c%c.%c%c%c.%c%c%c-%c%c",
            cpf_entrada[0], cpf_entrada[1], cpf_entrada[2],
            cpf_entrada[3], cpf_entrada[4], cpf_entrada[5],
            cpf_entrada[6], cpf_entrada[7], cpf_entrada[8],
            cpf_entrada[9], cpf_entrada[10]);
}

int validar_data(const char* data) {
    int ano, mes, dia;
    
    // Extrai o ano, mês e dia da string de data
    sscanf(data, "%4d%2d%2d", &ano, &mes, &dia);

    // Verifica se o ano, mês e dia estão dentro dos limites aceitáveis
    if (ano < 1900 || ano > 2100 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return 0;
    }

    return 1;
}

int validar_idade(int idade) {
    // Verifica se a idade está dentro dos limites permitidos (0 a 150)
    return (idade >= 0 && idade <= 150);
}
