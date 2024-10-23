#include <stdio.h>
#include <stdlib.h>

// Função para alocar e inicializar a estrutura de próximos acessos
int* inicializar_prox_acesso(int num_objects, int length) {
    int *prox_acesso = (int *)malloc(num_objects * sizeof(int));
    for (int i = 0; i < num_objects; i++) {
        prox_acesso[i] = length; // Inicializa como não acessado mais
    }
    return prox_acesso;
}


// Função de simulação de cache
int cache_simulation(int cache_size, int num_objects, int sequence[], int length) {
    int insercoes = 0;

    int *cache = (int *)malloc(cache_size * sizeof(int));
    int cache_count = 0;

    int *prox_acesso = inicializar_prox_acesso(num_objects, length);


 
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
