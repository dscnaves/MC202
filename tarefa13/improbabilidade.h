#ifndef CIRCUITO_H
#define CIRCUITO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Circuito {
    /* Armazena todas as informações relevantes de um circuito */
    int peso;
    int alavancas;
    int *condicoes;
} Circuito;

void imprime_circuitos(Circuito *circuitos, int circ_num, int alavancas_total);
int calcular_peso_total(Circuito *circuitos, int circ_num);
int calculo_improbabilidade(Circuito *circuitos, int circ_num, int alavancas_total, int atual_alavanca, int *configuracao, int *circuitos_usados, int *alavancas_passadas);
int calculo_improbabilidade_possivel(Circuito *circuitos, int circ_num, int alavancas_total, int *circuitos_usados, int *alavancas_passadas);
void atualizar_melhor_configuracao(int alavancas_total, int improb_atual, int *melhor_improbabilidade, int *configuracao, int *melhor_configuracao);
void salvar_estado(int circ_num, int *circuitos_usados, int *alavancas_passadas, int **circuitos_usados_nivel, int **alavancas_passadas_nivel);
void restaurar_estado(int circ_num, int *circuitos_usados, int *alavancas_passadas, int *circuitos_usados_nivel, int *alavancas_passadas_nivel);
void backtracking(Circuito *circuitos, int circ_num, int alavancas_total, int atual_alavanca, int improb_atual, int *configuracao, int *circuitos_usados, int *alavancas_passadas, int *melhor_improbabilidade, int *melhor_configuracao);
void libera_memoria(Circuito *circuitos, int circ_num, int *melhor_configuracao, int *configuracao, int *alavancas_passadas, int *circuitos_usados);
void ler_dados_entrada(int *circ_num, int *alavancas_total, Circuito **circuitos);
void inicializar_estruturas(int alavancas_total, int circ_num, int **configuracao, int **melhor_configuracao, int **circuitos_usados, int **alavancas_passadas);
void executar_backtracking(Circuito *circuitos, int circ_num, int alavancas_total, int *configuracao, int *circuitos_usados, int *alavancas_passadas, int *melhor_improbabilidade, int *melhor_configuracao);
void imprimir_resultados(int melhor_improbabilidade, int *melhor_configuracao, int alavancas_total);

#endif // CIRCUITO_H