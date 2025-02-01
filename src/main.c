#include <stdio.h>
#include "lista.h"
#include "arquivo.h"
#include "menu.h"

int main() {
    // Carrega os pacientes do arquivo CSV
    Lista* lista = carregar_pacientes_csv("bd_paciente.csv");

    char opcao = '\0';  // Inicializando 'opcao' com um valor default
    do {
        exibir_menu();              // Exibe o menu principal
        processar_opcao(lista);     // Processa a opção escolhida pelo usuário
        
        // Solicita ao usuário uma opção
        printf("\nEscolha uma opção (ou 'Q' para sair): ");
        scanf(" %c", &opcao);  // Usa o espaço antes de %c para garantir que o 'Enter' anterior seja consumido
        
        printf("\nPressione Enter para continuar...");
        while (getchar() != '\n');  // Aguarda confirmação do usuário
    } while (opcao != 'Q' && opcao != 'q');

    // Salva os dados atualizados no arquivo CSV
    salvar_pacientes_csv("bd_paciente.csv", lista);

    // Libera toda a memória alocada
    liberar_lista(lista);

    return 0;
}
