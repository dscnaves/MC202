#include "improbabilidade.h"

// Função para calcular a improbabilidade
int calculo_improbabilidade(Circuito *circuitos, int circ_num, int alavancas_total, int atual_alavanca, int *configuracao, int *circuitos_usados, int *alavancas_passadas)
{
    int improbabilidade = 0; //Variável armazenará a contribuição total dos circuitos
    
    for (int x = 0; x < circ_num; x++){
        //Verificar se no circuito que estamos analisando, a posição da atual alavanca afeta ou não o circuito
        if (circuitos[x].condicoes[atual_alavanca] == 0)
            //Se a alavanca não afeta, pule o looping para o próximo circuito
            continue;
        else
            //Contador rastreia quantas alavancas relevantes para o circuito já foram consideradas
            alavancas_passadas[x] += 1; //Incremenda array que contabiliza quantas alavancas foram usadas

        //Verificar se circuito já não foi ligado 
        // => Se o circuito não foi contabilizado, verifica se o circuito está ligado 
        if (circuitos_usados[x] == 0 && configuracao[atual_alavanca] == circuitos[x].condicoes[atual_alavanca])
        {
            improbabilidade += circuitos[x].peso;
            circuitos_usados[x] = 1;
        }
    }

    return improbabilidade;
}

// Função é responsável por estimar a improbabilidade máxima que pode ser alcançada a partir do estado atual do backtracking
int calculo_improbabilidade_possivel(Circuito *circuitos, int circ_num, int alavancas_total, int *circuitos_usados, int *alavancas_passadas)
{
    int improbabilidade = 0;

    for (int x = 0; x < circ_num; x++)
    {
        // O circuito ainda não foi usado
        // & Se ainda existem alavancas relevantes para o circuito que não foram consideradas
        if (circuitos_usados[x] == 0 && alavancas_passadas[x] < circuitos[x].alavancas)
        //Ainda tem alavancas do circuito não ligadas que tem possibilidade de serem ativadas
        {
            //Se o circuito ainda pode ser ativado
            improbabilidade += circuitos[x].peso;
        }
    }

    return improbabilidade;
}