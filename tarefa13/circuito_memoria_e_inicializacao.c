#include "improbabilidade.h"

//Função para liberar memória
void libera_memoria(Circuito *circuitos, int circ_num, int *melhor_configuracao, int *configuracao, int *alavancas_passadas, int *circuitos_usados)
{
    for (int i = 0; i < circ_num; i++){
        free(circuitos[i].condicoes); // Libera a memória das condições de cada circuito
    }

    free(circuitos);            // Libera a memória do array de circuitos
    free(melhor_configuracao);  // Libera a memória da melhor configuração
    free(configuracao);         // Libera a memória da configuração
    free(circuitos_usados);     //Libera a memória dos circuitos usados
    free(alavancas_passadas);   //Libera a memória do número de alavancas relevantes já passadas
}


// Função para ler os dados de entrada
void ler_dados_entrada(int *circ_num, int *alavancas_total, Circuito **circuitos) {
    scanf("%d %d", circ_num, alavancas_total);

    *circuitos = malloc(*circ_num * sizeof(Circuito));
    for (int i = 0; i < *circ_num; i++) {
        char sinal;
        int peso, alavancas_conectadas;

        // Leitura do peso e do número de alavancas conectadas
        scanf("%d %d", &peso, &alavancas_conectadas);
        (*circuitos)[i].peso = peso;
        (*circuitos)[i].alavancas = alavancas_conectadas;
        (*circuitos)[i].condicoes = malloc(*alavancas_total * sizeof(int));

        // Inicializando as condições como 0
        for (int j = 0; j < *alavancas_total; j++) {
            (*circuitos)[i].condicoes[j] = 0;
        }

        // Leitura das condições das alavancas
        for (int j = 0; j < alavancas_conectadas; j++) {
            int alavanca_atual;
            scanf(" %c%d", &sinal, &alavanca_atual);
            (*circuitos)[i].condicoes[alavanca_atual] = (sinal == '+') ? +1 : -1;
        }
    }
}

// Função para inicializar as estruturas de dados
void inicializar_estruturas(int alavancas_total, int circ_num, int **configuracao, int **melhor_configuracao, int **circuitos_usados, int **alavancas_passadas) {
    *configuracao = malloc(alavancas_total * sizeof(int));
    *melhor_configuracao = malloc(alavancas_total * sizeof(int));
    *circuitos_usados = malloc(circ_num * sizeof(int));
    *alavancas_passadas = malloc(circ_num * sizeof(int));

    for (int i = 0; i < alavancas_total; i++) {
        (*configuracao)[i] = 0;
        (*melhor_configuracao)[i] = 0;
    }

    for (int i = 0; i < circ_num; i++) {
        (*circuitos_usados)[i] = 0;
        (*alavancas_passadas)[i] = 0;
    }
}

// Função para imprimir os resultados
void imprimir_resultados(int melhor_improbabilidade, int *melhor_configuracao, int alavancas_total) {
    printf("%d\n", melhor_improbabilidade);
    for (int i = 0; i < alavancas_total; i++) {
        printf("%c%d ", (melhor_configuracao[i] == +1) ? '+' : '-', i);
    }
    printf("\n");
}