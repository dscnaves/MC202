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

// Função para executar o backtracking
void executar_backtracking(Circuito *circuitos, int circ_num, int alavancas_total, int *configuracao, int *circuitos_usados, int *alavancas_passadas, int *melhor_improbabilidade, int *melhor_configuracao) {
    backtracking(circuitos, circ_num, alavancas_total, 0, 0, configuracao, circuitos_usados, alavancas_passadas, melhor_improbabilidade, melhor_configuracao);
}

// Função para imprimir os resultados
void imprimir_resultados(int melhor_improbabilidade, int *melhor_configuracao, int alavancas_total) {
    printf("%d\n", melhor_improbabilidade);
    for (int i = 0; i < alavancas_total; i++) {
        printf("%c%d ", (melhor_configuracao[i] == +1) ? '+' : '-', i);
    }
    printf("\n");
}

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