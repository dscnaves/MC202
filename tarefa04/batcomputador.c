#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_VETOR 8 //Tamanho mínimo do vetor

typedef struct {
    int * dados;
    int alocado;
    int utilizados;
} Vector;

typedef Vector * p_vector;

void bat_alloc(int N, p_vector v){ //N é o tamanho do vetor

    //Se o vetor estiver vazio / 1° alocação
    if (v->dados == NULL){
        if (N >= MIN_VETOR) {        
            v->dados = malloc(2*N*sizeof(int));
            v->alocado = 2*N;
            v->utilizados = 0;
        }

        else {
            v->dados = malloc(MIN_VETOR*sizeof(int));
            v->alocado = MIN_VETOR;
            v->utilizados = 0;
        }

        for (int i = 0; i<N; i++){
            scanf("%d", &v->dados[i]);
            v->utilizados++;
        }

        printf("%p", &v->dados[0]);
        return;
    }

    //Verificar se há espaço o suficiente para alocar os novos elementos
    if (N < (v->alocado - v->utilizados)){
        for (int i = 0; i<N; i++){
            scanf("%d", &v->dados[v->utilizados + i]);
           v->utilizados++;
        }
        printf("%p", &v->dados[0]);
        return;
    }

    else {
        int * p_aux;
        p_aux = v->dados;

        v->dados = malloc(2*(N + v->utilizados)*sizeof(int));      
   
        for (int i = 0; i<v->utilizados; i++){
            v->dados[i] = p_aux[i];
        }  
        free(p_aux);

        for (int i = 0; i<N; i++){
            scanf("%d", &v->dados[v->utilizados+i]);
            v->utilizados++;
        }

        N = N + v->utilizados;
        v->alocado = 2*N;
        v->utilizados = N;    
        printf("%p", &v->dados[0]);
        return;    
    }

}   

int main(){

    int n; //Número de operações a serem realizadas
    scanf("%d", &n);

    //Declarando e alocando a bat-memória
    p_vector v;
    v = malloc(sizeof(Vector));
    
    char command[10];
    for (int x = 0; x<n; x++){
        scanf("%s", command);

        if (strcmp(command,"bat-alloc") == 0){
            int N; //Qtde de números alocados
            scanf("%d", &N);
            bat_alloc(N, v);
        }

        else if (strcmp(command,"bat-free") == 0){
            p_vector v; //Endereço de memória que se quer liberar
            scanf("%p", &v);

            free(v->dados);
            free(v);
        }

        else if (strcmp(command,"bat-print") == 0){
            p_vector v; //Endereço de memória que se quer imprimir
            scanf("%p", &v);

            for (int i = 0; i < v->utilizados; i++){
                printf("%d ", v->dados[i]);
            }
        }

        else if (strcmp(command,"bat-uso") == 0){

        }

    }

    return 0;
}