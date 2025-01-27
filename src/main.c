#include <stdio.h>
#include <stdlib.h>
#include "bd_paciente.h"
#include "utils.h"

void exibir_menu(){
    printf("\nHealthSys - Sistema de Gerenciamento de Pacien");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir paciente\n");
    printf("5 - Imprimir lista de pacientes\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    BD_Paciente* bd = criar_bd();
    if (!bd || carregar_bd(bd) != 0)
    {
        printf("Erro ao inicializar o banco de dados!\n");
        return 1;
    }

    char opcao;
    do
    {
        exibir_menu();
        scanf(" %c", &opcao);
        limpar_buff();

        switch (opcao)
        {
        case '1':
            // Consultar paciente
            break;
        case '2':
            // Atualizar paciente
            break;
        case '3':
            // Remover paciente
            break;
        case '4':
            // Inserir paciente
            break;
        case '5':
            // Imprimir lista
            break;
        case '0':
            printf("Salvando dados e encerrando... \n");
            salvar_bd(bd);
            break;
        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != '0');
    
    liberar_bd(bd);
    return 0;
    
}