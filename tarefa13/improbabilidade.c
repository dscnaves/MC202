#include <stdio.h>
#include <stdlib.h>

typedef struct Circuito{
    /* Armazena todas as informações relevantes de um circuito */
    int peso;
    int num_alav;
    int * condicoes;
}Circuito;


int main(){

    int * configuracao;
    Circuito * circuitos;

    int melhor_improbabilidade = 0; // Maior improbabilidade encontrada
    int * melhor_configuracao;   // Configuração correspondente


}