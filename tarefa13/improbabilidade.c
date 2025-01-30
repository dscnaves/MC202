#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Circuito{
    /* Armazena todas as informações relevantes de um circuito */
    int peso;
    int alavancas;
    int * condicoes;
}Circuito;

void imprime_circuitos(Circuito * circuitos, int circ_num, int alavancas_total){
    for (int x = 0; x<circ_num; x++){
        printf("Circuito %d Peso %d Alavancas Conectadas %d Configuração: ", x, circuitos[x].peso, circuitos[x].alavancas);
        for (int y = 0; y<alavancas_total; y++){
            printf("%d ", circuitos[x].condicoes[y]);
        }
        printf("\n");
    }
}

// Função para calcular a soma dos pesos de todos os circuitos
int calcular_peso_total(Circuito *circuitos, int circ_num) {
    int total = 0;
    for (int i = 0; i < circ_num; i++) {
        total += circuitos[i].peso; // Soma o peso de cada circuito
    }
    return total;
}

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


void backtracking(Circuito *circuitos, int circ_num, int alavancas_total, int atual_alavanca, int improb_atual,
                  int *configuracao, int *circuitos_usados, int *alavancas_passadas, int *melhor_improbabilidade, int *melhor_configuracao)
{


    // Caso base: Todas as alavancas já foram visitadas
    if (atual_alavanca == alavancas_total)
    {
        //Se a improbabilidade atual for maior que a melhor improbabilidade prevista
        if (improb_atual > *melhor_improbabilidade)
        {
            *melhor_improbabilidade = improb_atual;
            //Salva a configuração de maior improbabilidade
            for (int x = 0; x < alavancas_total; x++)
            {
                melhor_configuracao[x] = configuracao[x];
            }
        }
        return;
    }

    // Analisa se é possivel a partir do estado atual chegar a um estado melhor, se nao conseguir, para o backtracking
    int improbabilidade_maxima_futuro = improb_atual + calculo_improbabilidade_possivel(circuitos, circ_num, alavancas_total, circuitos_usados, alavancas_passadas);
    
    //Se a maxima improbabilidade possível para dada configuração é menor que a melhor improbabilidade já encontrada
    if (improbabilidade_maxima_futuro <= *melhor_improbabilidade)
        //Parar backtracking, pois não faz sentido continuar preenchendo alavancas para cima e para baixo que não levaram a melhor improb
        return;

    //Arrays para salvar estado atual 
    int *circuitos_usados_nivel = malloc(circ_num * sizeof(int));
    int *alavancas_passadas_nivel = malloc(circ_num * sizeof(int));

    for (int i = 0; i < circ_num; i++)
    {
        circuitos_usados_nivel[i] = circuitos_usados[i];
        alavancas_passadas_nivel[i] = alavancas_passadas[i];
    }


    // Preenchendo com alavanca para cima
    configuracao[atual_alavanca] = +1;
    int improbabilidade_cima = improb_atual + calculo_improbabilidade(circuitos, circ_num, alavancas_total, atual_alavanca, configuracao, circuitos_usados, alavancas_passadas);
    backtracking(circuitos, circ_num, alavancas_total, atual_alavanca + 1, improbabilidade_cima, configuracao, circuitos_usados, alavancas_passadas, melhor_improbabilidade, melhor_configuracao);


    for (int i = 0; i < circ_num; i++)
    {
        circuitos_usados[i] = circuitos_usados_nivel[i];
        alavancas_passadas[i] = alavancas_passadas_nivel[i];
    }


    // Preenchendo com alavanca para baixo
    configuracao[atual_alavanca] = -1;
    int improbabilidade_baixo = improb_atual + calculo_improbabilidade(circuitos, circ_num, alavancas_total, atual_alavanca, configuracao, circuitos_usados, alavancas_passadas);
    backtracking(circuitos, circ_num, alavancas_total, atual_alavanca + 1, improbabilidade_baixo, configuracao, circuitos_usados, alavancas_passadas, melhor_improbabilidade, melhor_configuracao);


    free(circuitos_usados_nivel);
    free(alavancas_passadas_nivel);
}

void libera_memoria(Circuito *circuitos, int circ_num, int *melhor_configuracao, int *configuracao) {
    for (int i = 0; i < circ_num; i++) {
        free(circuitos[i].condicoes); // Libera a memória das condições de cada circuito
    }
    free(circuitos); // Libera a memória do array de circuitos
    free(melhor_configuracao); // Libera a memória da melhor configuração
    free(configuracao); // Libera a memória da configuração
}

int main() {
    int circ_num, alavancas_total;

    // Leitura do número de circuitos e alavancas
    scanf("%d %d", &circ_num, &alavancas_total);

    // Alocação de memória para a configuração e para os circuitos
    int *configuracao = malloc(alavancas_total * sizeof(int));
    Circuito *circuitos = malloc(circ_num * sizeof(Circuito));
    int melhor_improbabilidade = 0; // Maior improbabilidade encontrada
    int *melhor_configuracao = malloc(alavancas_total * sizeof(int)); // Configuração correspondente

    // Leitura da descrição de cada circuito
    for (int i = 0; i < circ_num; i++) {
        char sinal;
        int peso, alavancas_conectadas;
        
        // Leitura do peso e do número de alavancas conectadas
        scanf("%d %d", &peso, &alavancas_conectadas);
        circuitos[i].peso = peso;
        circuitos[i].alavancas = alavancas_conectadas;
        circuitos[i].condicoes = malloc(alavancas_total * sizeof(int));

        // Inicializando as condições como 0
        for (int j = 0; j < alavancas_total; j++) {
            circuitos[i].condicoes[j] = 0;
        }

        // Leitura das condições das alavancas
        for (int j = 0; j < alavancas_conectadas; j++) {
            int alavanca_atual;
            scanf(" %c%d", &sinal, &alavanca_atual);
            circuitos[i].condicoes[alavanca_atual] = (sinal == '+') ? +1 : -1;
        }
    }

    // Calcula a improbabilidade inicial máxima (metade do peso total dos circuitos)
    int limite = calcular_peso_total(circuitos, circ_num) / 2;

    // Chama a função de backtracking com poda
    backtracking(circuitos, circ_num, alavancas_total, 0, configuracao, 
                 &melhor_improbabilidade, melhor_configuracao, limite);

    // Imprime a melhor improbabilidade e a configuração correspondente
    printf("%d\n", melhor_improbabilidade);
    for (int i = 0; i < alavancas_total; i++) {
        printf("%c%d ", (melhor_configuracao[i] == +1) ? '+' : '-', i);
    }
    printf("\n");

    // Libera a memória alocada
    libera_memoria(circuitos, circ_num, melhor_configuracao, configuracao);

    return 0;
}
