#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "improbabilidade.h"

// Função principal
int main() {
    int circ_num, alavancas_total;
    Circuito *circuitos;
    int *configuracao, *melhor_configuracao, *circuitos_usados, *alavancas_passadas;
    int melhor_improbabilidade = 0;

    // Leitura dos dados de entrada
    ler_dados_entrada(&circ_num, &alavancas_total, &circuitos);

    // Inicialização das estruturas de dados
    inicializar_estruturas(alavancas_total, circ_num, &configuracao, &melhor_configuracao, &circuitos_usados, &alavancas_passadas);

    // Execução do backtracking
    backtracking(circuitos, circ_num, alavancas_total, 0, 0, configuracao, circuitos_usados, alavancas_passadas, &melhor_improbabilidade, melhor_configuracao);

    // Impressão dos resultados
    imprimir_resultados(melhor_improbabilidade, melhor_configuracao, alavancas_total);

    // Liberação de memória
    libera_memoria(circuitos, circ_num, melhor_configuracao, configuracao, alavancas_passadas, circuitos_usados);

    return 0;
}