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
            }else{
                ligada = 0;
                break;
            }
        }
        if(ligada == 1){
            improbabilidade += circuitos[x].peso;
        }
    }
    return improbabilidade;
}

void backtracking(Circuito * circuitos, int circ_num, int alavancas_total, int atual_alavanca, int *melhor_improbabilidade, int *melhor_configuracao){
    //Caso base: Todas as alavancas já foram visitadas => Já formamos uma sequência completa => Cálculo da probabilidade
    if(atual_alavanca == alavancas_total){

    }

}

int main(){
    int circ_num, alavancas_total, peso, alavancas_conectadas;

    scanf("%d %d", &circ_num, &alavancas_total);

    // int * configuracao;
    // configuracao = malloc(alavancas_total*sizeof(int));

    Circuito * circuitos;
    circuitos =  malloc(circ_num*sizeof(Circuito));


    // int melhor_improbabilidade = 0; // Maior improbabilidade encontrada
    // int * melhor_configuracao;   // Configuração correspondente
    // melhor_configuracao = malloc(alavancas_total*sizeof(int));
    
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

    imprime_circuitos(circuitos,circ_num,alavancas_total);  

    int * configuracao_teste = {-1,-1,+1,+1};
    int imp = calculo_improbabilidade(circuitos,circ_num,alavancas_total,configuracao_teste);

    return 0;

}