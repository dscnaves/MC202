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
            v->dados = malloc(2*MIN_VETOR*sizeof(int));
            v->alocado = MIN_VETOR;
            v->utilizados = 0;
        }

        for (int i = 0; i<N; i++){
            scanf("%d", &v->dados[i]);
            v->utilizados++;
        }

        printf("%p\n", &v->dados[0]);
        return;
    }

    //Verificar se há espaço o suficiente para alocar os novos elementos
    if (N < (v->alocado - v->utilizados)){
        for (int i = 0; i<N; i++){
            scanf("%d", &v->dados[v->utilizados + i]);
        }
        v->utilizados = v->utilizados + N;

        printf("%p\n", &v->dados[0]);
        return;
    }

    //Expandir a memória
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
        }


        v->alocado = 2*(N + v->utilizados);
        v->utilizados = N + v->utilizados;  

        printf("%p\n", &v->dados[0]);
        return;    
    }

}   

void bat_free(int endereco, p_vector v){

    for (int i = 0; i < (v->alocado-1 - endereco); i++){
        v->dados[endereco + i] = -1;
    }

     printf("Esse daqui é nosso vetor:");
        for (int x = 0; x<v->utilizados; x++){
            printf("%d ",v->dados[x]);
        }
        printf("\n");

    v->utilizados = endereco;

    //Verificar necessidade de reduzir o vetor
    if (v->utilizados <= (v->alocado/4)){
        
        int * p_aux = v->dados;
        
        if (v->alocado/2 <= MIN_VETOR){
            v->dados = malloc((2*MIN_VETOR)*sizeof(int));
            v->alocado = 2*MIN_VETOR;
        }
        else {
            v->dados = malloc((v->alocado/2)*sizeof(int));      
            v->alocado = v->alocado/2;
        }

        for (int i = 0; i<v->utilizados; i++){
            v->dados[i] = p_aux[i];
        }  
        free(p_aux);

    }

}

int main(){
    int n; //Número de operações a serem realizadas
    scanf("%d", &n);

    //Declarando e alocando a bat-memória
    p_vector v = malloc(sizeof(Vector));
    v->dados = NULL;
    
    char command[10];
    for (int x = 0; x<n; x++){
        scanf("%s", command);

        if (strcmp(command,"bat-alloc") == 0){
            int N; //Qtde de números alocados
            scanf("%d", &N);
            bat_alloc(N, v);

        printf("Esse daqui é nosso vetor:");
        for (int x = 0; x<v->utilizados; x++){
            printf("%d ",v->dados[x]);
        }
        printf("\n");

        }

        else if (strcmp(command,"bat-free") == 0){
            int endereco; //Endereço de memória que se quer liberar
            scanf("%d", &endereco);

            bat_free(endereco,v);
            
        }

        else if (strcmp(command,"bat-print") == 0){
            p_vector v_print; //Endereço de memória que se quer imprimir
            scanf("%p", &v_print);

            for (int i = 0; i < v_print->utilizados; i++){
                printf("%d ", v_print->dados[i]);
            }
            printf("\n");
        }

        else if (strcmp(command,"bat-uso") == 0){

        }

    }

    // Liberando a memória no final
    free(v->dados);
    free(v);

    //Imprimindo o vetor
    printf("Esse daqui é nosso vetor:");
    for (int x = 0; x<v->utilizados; x++){
        printf("%d ",v->dados[x]);
    }
    printf("\n");

    printf("%d\n", v->utilizados);
    printf("%d\n", v->alocado);

    return 0;
}