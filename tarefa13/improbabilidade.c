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
        printf("Circuito %d Peso %d Alavancas Coectadas %d Configuração: ", x, circuitos[x].peso, circuitos[x].alavancas);
        for (int y = 0; y<alavancas_total; y++){
            printf("%d", circuitos[x].condicoes[y]);
        }
        printf("\n");
    }
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

        for (int j = 0; j<alavancas_conectadas; j++){
            int alavanca_atual;
            scanf("%c%d", &sinal, &alavanca_atual);

            if(strcmp(sinal,'+')){
                circuitos[i].condicoes[j] = 1;
            } else{
                circuitos[i].condicoes[j] = 0;
            }
        }
    }        

}