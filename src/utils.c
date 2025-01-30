#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

int validar_cpf(const char* cpf) {
    if (strlen(cpf) != 14) return 0;
    
    // Formato xxx.xxx.xxx-xx
    if (cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-') return 0;
    
    for (int i = 0; i < 14; i++) {
        if (i == 3 || i == 7 || i == 11) continue;
        if (!isdigit(cpf[i])) return 0;
    }
    
    return 1;
}

int validar_data(const char* data) {
    if (strlen(data) != 10) return 0;
    
    // Formato AAAA-MM-DD
    if (data[4] != '-' || data[7] != '-') return 0;
    
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(data[i])) return 0;
    }
    
    return 1;
}

void formatar_cpf(char* cpf_formatado, const char* cpf) {
    int j = 0;
    for (int i = 0; i < 14; i++) {
        if (i == 3 || i == 7) {
            cpf_formatado[i] = '.';
        } else if (i == 11) {
            cpf_formatado[i] = '-';
        } else {
            cpf_formatado[i] = cpf[j++];
        }
    }
    cpf_formatado[14] = '\0';
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}