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

int calculo_improbabilidade(Circuito * circuitos, int circ_num, int alavancas_total, int *configuracao){
    int improbabilidade = 0;
    for(int x = 0; x<circ_num; x++){
        int ligada = 0;
        for(int y = 0; y<alavancas_total; y++){
            if(circuitos[x].condicoes[y] == configuracao[y]){
                ligada = 1;
                break;
            }
        }
        if(ligada == 1){
            improbabilidade += circuitos[x].peso;
        }
    }
    return improbabilidade;
}

void backtracking(Circuito * circuitos, int circ_num, int alavancas_total, int atual_alavanca, int *configuracao, int *melhor_improbabilidade, int *melhor_configuracao){
    //Caso base: Todas as alavancas já foram visitadas => Já formamos uma sequência completa => Cálculo da probabilidade
    if(atual_alavanca == alavancas_total){
        int improbabilidade = calculo_improbabilidade(circuitos,circ_num,alavancas_total,configuracao);
        if(improbabilidade > *melhor_improbabilidade){
            *melhor_improbabilidade = improbabilidade;
            for(int x = 0; x<alavancas_total; x++){
                melhor_configuracao[x] = configuracao[x];
            }
        }
        return;
    }

    //Se a configuração ainda não foi totalmente preenchida => Preenchemos a posição que estamos
    
    //Preenchendo com alavanca para cima
    configuracao[atual_alavanca] = +1;
    backtracking(circuitos, circ_num, alavancas_total, atual_alavanca+1, configuracao, melhor_improbabilidade, melhor_configuracao); 
    //Preenchendo com alavanca para baixo
    configuracao[atual_alavanca] = -1;
    backtracking(circuitos, circ_num, alavancas_total, atual_alavanca+1, configuracao, melhor_improbabilidade, melhor_configuracao); 
}

int main(){
    int circ_num, alavancas_total, peso, alavancas_conectadas;

    scanf("%d %d", &circ_num, &alavancas_total);

    int * configuracao;
    configuracao = malloc(alavancas_total*sizeof(int));

    Circuito * circuitos;
    circuitos =  malloc(circ_num*sizeof(Circuito));


    int melhor_improbabilidade = 0; // Maior improbabilidade encontrada
    int * melhor_configuracao;   // Configuração correspondente
    melhor_configuracao = malloc(alavancas_total*sizeof(int));
    
    for(int i = 0; i<circ_num; i++){

        char sinal;
        scanf("%d %d", &peso, &alavancas_conectadas);
        circuitos[i].peso = peso;
        circuitos[i].alavancas = alavancas_conectadas;
        circuitos[i].condicoes = malloc(alavancas_total*sizeof(int));

        //Inicializando o circuito
        for(int j = 0; j<alavancas_total; j++){
            circuitos[i].condicoes[j] = 0;
        }

        for (int j = 0; j<alavancas_conectadas; j++){
            int alavanca_atual;
            scanf(" %c%d", &sinal, &alavanca_atual);

            if(sinal == '+'){
                circuitos[i].condicoes[alavanca_atual] = +1;
            } else{
                circuitos[i].condicoes[alavanca_atual] = -1;
            }
        }
    }

    backtracking(circuitos,circ_num,alavancas_total, 0, configuracao, &melhor_improbabilidade, melhor_configuracao);

    printf("%d\n", melhor_improbabilidade);
    for(int i = 0; i<alavancas_total; i++){
        if(melhor_configuracao[i] == +1){
            printf("+%d ", i);
        }else{
            printf("-%d ", i);
        }
    }
    printf("\n");

    // int configuracao_teste[] = {-1,-1,+1,-1};
    // int imp = calculo_improbabilidade(circuitos,circ_num,alavancas_total,configuracao_teste);

    //printf("teste: %d\n", imp);
    return 0;

}