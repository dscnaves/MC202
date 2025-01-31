#include "improbabilidade.h"

// Função para atualizar a melhor configuração encontrada
void atualizar_melhor_configuracao(int alavancas_total, int improb_atual, int *melhor_improbabilidade, int *configuracao, int *melhor_configuracao) {
    if (improb_atual > *melhor_improbabilidade) {
        *melhor_improbabilidade = improb_atual;
        for (int x = 0; x < alavancas_total; x++) {
            melhor_configuracao[x] = configuracao[x];
        }
    }
}

// Função para salvar o estado atual dos arrays circuitos_usados e alavancas_passadas
void salvar_estado(int circ_num, int *circuitos_usados, int *alavancas_passadas, int **circuitos_usados_nivel, int **alavancas_passadas_nivel) {
    *circuitos_usados_nivel = malloc(circ_num * sizeof(int));
    *alavancas_passadas_nivel = malloc(circ_num * sizeof(int));

    for (int i = 0; i < circ_num; i++) {
        (*circuitos_usados_nivel)[i] = circuitos_usados[i];
        (*alavancas_passadas_nivel)[i] = alavancas_passadas[i];
    }
}

// Função para restaurar o estado dos arrays circuitos_usados e alavancas_passadas
void restaurar_estado(int circ_num, int *circuitos_usados, int *alavancas_passadas, int *circuitos_usados_nivel, int *alavancas_passadas_nivel) {
    for (int i = 0; i < circ_num; i++) {
        circuitos_usados[i] = circuitos_usados_nivel[i];
        alavancas_passadas[i] = alavancas_passadas_nivel[i];
    }
}

void backtracking(Circuito *circuitos, int circ_num, int alavancas_total, int atual_alavanca, int improb_atual,
                  int *configuracao, int *circuitos_usados, int *alavancas_passadas, int *melhor_improbabilidade, int *melhor_configuracao)
{
    // Caso base: Todas as alavancas já foram visitadas
    if (atual_alavanca == alavancas_total) {
        atualizar_melhor_configuracao(alavancas_total, improb_atual, melhor_improbabilidade, configuracao, melhor_configuracao);
        return;
    }

    /* PODA: Evitando caminhos inúteis */

    // Analisa se é possível a partir do estado atual chegar a um estado melhor, se não conseguir, para o backtracking
    int improbabilidade_maxima_futuro = improb_atual + calculo_improbabilidade_possivel(circuitos, circ_num, alavancas_total, circuitos_usados, alavancas_passadas);

    // Se a máxima improbabilidade possível para dada configuração é menor que a melhor improbabilidade já encontrada
    if (improbabilidade_maxima_futuro <= *melhor_improbabilidade)
        // Parar backtracking, pois não faz sentido continuar preenchendo alavancas para cima e para baixo que não levaram a melhor improb
        return;


    // Arrays para salvar estado atual dos arrays circuitos_usados
    // e alavancas_passadas para ser possível restaurá-los após cada tentativa
    int *circuitos_usados_nivel, *alavancas_passadas_nivel;
    salvar_estado(circ_num, circuitos_usados, alavancas_passadas, &circuitos_usados_nivel, &alavancas_passadas_nivel);


    // Preenchendo com alavanca para cima
    configuracao[atual_alavanca] = +1;
    int improbabilidade_cima = improb_atual + calculo_improbabilidade(circuitos, circ_num, alavancas_total, atual_alavanca, configuracao, circuitos_usados, alavancas_passadas);
    //A função chama a si mesma recursivamente para explorar as configurações das próximas alavancas (atual_alavanca + 1)
    backtracking(circuitos, circ_num, alavancas_total, atual_alavanca + 1, improbabilidade_cima, configuracao, circuitos_usados, alavancas_passadas, melhor_improbabilidade, melhor_configuracao);


    // Restaurando ao nível "original"
    restaurar_estado(circ_num, circuitos_usados, alavancas_passadas, circuitos_usados_nivel, alavancas_passadas_nivel);


    // Preenchendo com alavanca para baixo
    configuracao[atual_alavanca] = -1;
    int improbabilidade_baixo = improb_atual + calculo_improbabilidade(circuitos, circ_num, alavancas_total, atual_alavanca, configuracao, circuitos_usados, alavancas_passadas);
    backtracking(circuitos, circ_num, alavancas_total, atual_alavanca + 1, improbabilidade_baixo, configuracao, circuitos_usados, alavancas_passadas, melhor_improbabilidade, melhor_configuracao);

    //Liberando memória
    free(circuitos_usados_nivel);
    free(alavancas_passadas_nivel);
}
