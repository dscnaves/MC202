#include <stdio.h>
#include <stdlib.h>

#define MAX_OBJECTS 100000

// Função para alocar e inicializar a estrutura de próximos acessos
int* next_access_initialize(int num_objects, int length) {
    //O array chamado next_access é usado para para armazenar quando cada objeto será acessado novamente

    int *next_access = malloc(num_objects * sizeof(int *));
    
    for (int i = 0; i < num_objects; i++) {
        next_access[i] = length; // Inicializa como não acessado mais => lenght é um marcador cujo acesso inváido ao vetor é usado para revelar que um objeto não será mais acessado 
    }
    return next_access;
}

// Função para alocar e inicializar os acessos futuros
int** future_access_initialize(int num_objects, int length) {
    //A matriz chamada future_access é aquela onde cada linha corresponde a um objeto, e cada linha armazena as posições na sequência em que esse objeto será acessado no futuro

    int **future_access = malloc(num_objects * sizeof(int **));
    
    for (int i = 0; i < num_objects; i++) {
        future_access[i] = malloc(length * sizeof(int *));
    }
    return future_access;
}

// Função para liberar a memória de acessos futuros
void future_access_free(int **future_access, int num_objects) {
    for (int i = 0; i < num_objects; i++) {
        free(future_access[i]);
    }
    free(future_access);
}

// Função para pré-processar a sequência e calcular os próximos acessos
void calcular_proximos_acessos(int sequence[], int length, int **future_access, int *contador_acessos, int num_objects) {
    //Essa função preenche a matriz future_acess

    //Percorrer a lista de acesso de trás para frente para garantirmos que a matriz seja preenchida  com as posições mais próximas no futuro para cada objeto
    for (int i = length - 1; i >= 0; i--) {
        int obj = sequence[i];
        
        future_access[obj][contador_acessos[obj]] = i;
        //Atualizando a variável que quanta a quantidade de acessos que um objeto teve
        contador_acessos[obj]++;
    }
}



// Função de simulação de cache
int cache(int cache_size, int num_objects, int sequence[], int length) {
    int insercoes = 0;

    int *cache = (int *)malloc(cache_size * sizeof(int));
    int cache_count = 0;

    int *next_access = next_access_initialize(num_objects, length);


 
}

int main() {
    int cache_size, num_objects, sequence_length;

    scanf("%d %d %d", &cache_size, &num_objects, &sequence_length);

    int *sequence = (int *)malloc(sequence_length * sizeof(int));

    for (int i = 0; i < sequence_length; i++) {
        scanf("%d", &sequence[i]);
    }

    int result;


    return 0;
}
