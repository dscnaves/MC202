#ifndef CACHE_SIMULATION_H
#define CACHE_SIMULATION_H

// Função para alocar e inicializar a estrutura de próximos acessos
int* next_access_initialize(int num_objects, int length);

// Função para alocar e inicializar os acessos futuros
int** future_access_initialize(int num_objects, int length);

// Função para liberar a memória de acessos futuros
void future_access_free(int **future_access, int num_objects);

// Função que preenche a matriz future_access com os próximos acessos
void calcular_proximos_acessos(int sequence[], int length, int **future_access, int *contador_acessos, int num_objects);

// Função que determina qual objeto dentro do cache deve ser removido
int encontrar_objeto_para_remover(int cache[], int cache_count, int next_access[]);

// Função que simula o gerenciamento de objetos no cache e retorna o número de inserções
int cache(int cache_size, int num_objects, int sequence[], int length);

#endif
