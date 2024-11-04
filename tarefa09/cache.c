#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_WORD 26

typedef struct {
    int object;
    int next_access;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    int size;
    int capacity;
} MaxHeap;

// Função para criar uma heap com capacidade definida
MaxHeap *createHeap(int capacity) {
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->nodes = (HeapNode *)malloc(capacity * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Função para trocar dois nós na heap
void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Função para manter a propriedade da heap ao inserir um novo nó
void heapifyUp(MaxHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->nodes[parent].next_access >= heap->nodes[index].next_access) {
            break;
        }
        swap(&heap->nodes[parent], &heap->nodes[index]);
        index = parent;
    }
}

// Função para manter a propriedade da heap ao remover o nó raiz
void heapifyDown(MaxHeap *heap, int index) {
    while (2 * index + 1 < heap->size) {
        int child = 2 * index + 1;
        if (child + 1 < heap->size && heap->nodes[child].next_access < heap->nodes[child + 1].next_access) {
            child++;
        }
        if (heap->nodes[index].next_access >= heap->nodes[child].next_access) {
            break;
        }
        swap(&heap->nodes[index], &heap->nodes[child]);
        index = child;
    }
}

// Função para inserir um nó na heap
void insertHeap(MaxHeap *heap, int object, int next_access) {
    if (heap->size < heap->capacity) {
        heap->nodes[heap->size].object = object;
        heap->nodes[heap->size].next_access = next_access;
        heap->size++;
        heapifyUp(heap, heap->size - 1);
    } else if (next_access > heap->nodes[0].next_access) {
        heap->nodes[0].object = object;
        heap->nodes[0].next_access = next_access;
        heapifyDown(heap, 0);
    }
}

// Função para remover o nó de maior prioridade (com maior próximo acesso) da heap
HeapNode extractMax(MaxHeap *heap) {
    HeapNode maxNode = heap->nodes[0];
    heap->nodes[0] = heap->nodes[--heap->size];
    heapifyDown(heap, 0);
    return maxNode;
}

// Função para alocar e inicializar a estrutura de próximos acessos
int *next_access_initialize(int num_objects, int length) {
    int *next_access = malloc(num_objects * sizeof(int));
    for (int i = 0; i < num_objects; i++) {
        next_access[i] = length; // Inicializa como não acessado mais
    }
    return next_access;
}

// Função para alocar e inicializar os acessos futuros
int **future_access_initialize(int num_objects, int length) {
    int **future_access = malloc(num_objects * sizeof(int *));
    for (int i = 0; i < num_objects; i++) {
        future_access[i] = malloc(length * sizeof(int));
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

// Função para preencher a matriz future_acess
void calcular_proximos_acessos(int sequence[], int length, int **future_access, int *contador_acessos, int num_objects) {
    for (int i = length - 1; i >= 0; i--) {
        int obj = sequence[i];
        future_access[obj][contador_acessos[obj]] = i;
        contador_acessos[obj]++;
    }
}

// Função gerencia quais objetos serão mantidos no cache e quando será necessário remover um objeto
int cache(int cache_size, int num_objects, int sequence[], int length) {
    int insercoes = 0;
    int *cache = (int *)malloc(cache_size * sizeof(int));
    int cache_count = 0;

    int *next_access = next_access_initialize(num_objects, length);
    int **future_access = future_access_initialize(num_objects, length);
    int *contador_acessos = (int *)calloc(num_objects, sizeof(int));

    calcular_proximos_acessos(sequence, length, future_access, contador_acessos, num_objects);

    MaxHeap *heap = createHeap(cache_size);

    // Processo de gerenciamento de cache
    for (int i = 0; i < length; i++) {
        int current_object = sequence[i];

        // Atualiza o próximo acesso
        if (contador_acessos[current_object] > 0) {
            contador_acessos[current_object]--;
        }

        if (contador_acessos[current_object] == 0) {
            next_access[current_object] = length; // Se não houver mais acessos futuros, define como fora do intervalo.
        } else {
            next_access[current_object] = future_access[current_object][contador_acessos[current_object] - 1];
        }

        // Verifica se o current_object já está no cache
        int found_in_cache = 0;
        for (int j = 0; j < cache_count; j++) {
            if (cache[j] == current_object) {
                found_in_cache = 1;
                break;
            }
        }

        // Se o objeto não estiver no cache => Inseri-lo
        if (!found_in_cache) {
            if (cache_count >= cache_size) { // Se o cache estiver cheio
                // Decidir qual objeto remover
                HeapNode node = extractMax(heap);
                for (int j = 0; j < cache_count; j++) {
                    if (cache[j] == node.object) {
                        for (int k = j; k < cache_count - 1; k++) {
                            cache[k] = cache[k + 1];
                        }
                        cache_count--;
                        break;
                    }
                }
            }
            cache[cache_count++] = current_object;
            insertHeap(heap, current_object, next_access[current_object]);
            insercoes++;
        } else {
            insertHeap(heap, current_object, next_access[current_object]);
        }
    }

    free(cache);
    free(next_access);
    future_access_free(future_access, num_objects);
    free(contador_acessos);
    free(heap->nodes);
    free(heap);

    return insercoes;
}

int main() {
    int cache_size, num_objects, sequence_length;

    scanf("%d %d %d", &cache_size, &num_objects, &sequence_length);

    int *sequence = (int *)malloc(sequence_length * sizeof(int));

    for (int i = 0; i < sequence_length; i++) {
        scanf("%d", &sequence[i]);
    }

    int result = cache(cache_size, num_objects, sequence, sequence_length);
    printf("%d\n", result);

    free(sequence);

    return 0;
}
