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
            v->alocado = 2*MIN_VETOR;
            v->utilizados = 0;
        }

        for (int i = 0; i<N; i++){
            scanf("%d", &v->dados[i]);
            v->utilizados++;
        }

        printf("0\n");
        return;
    }

    int utilizados_anterior = v->utilizados;

    //Verificar se há espaço o suficiente para alocar os novos elementos
    if (N < (v->alocado - v->utilizados)){
        for (int i = 0; i<N; i++){
            scanf("%d", &v->dados[v->utilizados + i]);
        }
        v->utilizados = v->utilizados + N;

        printf("%d\n", utilizados_anterior+1);
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

        printf("%d\n", utilizados_anterior+1);
        return;    
    }

}   

void bat_free(int endereco, p_vector v){
    if (endereco >= 0 && endereco <= v->utilizados) {
        v->utilizados = endereco;
    }

    //Verificar a necessidade de diminuir o tamanho do vetor
    if (v->utilizados <= v->alocado / 4) {
        int novo_tamanho = v->alocado / 2;

        if (novo_tamanho < MIN_VETOR){
            novo_tamanho = 2*MIN_VETOR;
        }

        int * p_aux = realloc(v->dados, novo_tamanho*sizeof(int));

        if (p_aux != NULL){
            v->dados = p_aux;
            v->alocado = novo_tamanho;
        }
    }
    
    // Exibir o estado atual do vetor
    printf("Esse daqui é nosso vetor:");
    for (int x = 0; x < v->utilizados; x++) {
        printf("%d ", v->dados[x]);
    }
    printf("\n");

    
}

void bat_print(int endereco, p_vector v){
    for (int i = 0; i < v->utilizados - endereco +1; i++){
        printf("%d ", v->dados[endereco -1 + i]);
    }
}

void bat_uso(p_vector v){
    printf("%d de %d", v->utilizados, v->alocado);
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
            int endereco; //Endereço de memória que se quer imprimir
            scanf("%d", &endereco);

            bat_print(endereco, v);
        }

        else if (strcmp(command,"bat-uso") == 0){
            bat_uso(v);
        }

    }

    

    //Imprimindo o vetor
    printf("Esse daqui é nosso vetor:");
    for (int x = 0; x<v->utilizados; x++){
        printf("%d ",v->dados[x]);
    }
    printf("\n");

    printf("%d\n", v->utilizados);
    printf("%d\n", v->alocado);

    // Liberando a memória no final
    free(v->dados);
    free(v);

    return 0;
}