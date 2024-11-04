#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_WORD 26

typedef struct ListNode {
    int access_index;
    struct ListNode *next;
} ListNode;

typedef struct {
    int object;
    int next_access; //Chave de prioridade
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
    int maior_filho;
    int esquerda = 2 * index + 1;  // Índice do filho à esquerda
    int direita = 2 * index + 2;   // Índice do filho à direita

    // Enquanto houver um filho à esquerda (i.e., o nó tem pelo menos um filho)
    while (esquerda < heap->size) {
        // Assume inicialmente que o filho à esquerda é o maior
        maior_filho = esquerda;

        // Se o filho à direita existir e tiver um próximo acesso maior que o filho à esquerda
        if (direita < heap->size && heap->nodes[direita].next_access > heap->nodes[esquerda].next_access) {
            maior_filho = direita;
        }

        // Se o pai tiver um próximo acesso maior ou igual ao maior dos filhos, a propriedade da heap está mantida
        if (heap->nodes[index].next_access >= heap->nodes[maior_filho].next_access) {
            break;
        }

        // Caso contrário, troca o pai com o maior dos filhos
        swap(&heap->nodes[index], &heap->nodes[maior_filho]);

        // Atualiza o índice do pai e recalcula os índices dos filhos
        index = maior_filho;
        esquerda = 2 * index + 1;
        direita = 2 * index + 2;
    }
}

// Função para inserir um nó na heap
void insertHeap(MaxHeap *heap, int object, int next_access) {
    //Se o heap tem espaço
    if (heap->size < heap->capacity) {
        heap->nodes[heap->size].object = object; //Inserindo o objeto no heap no final
        heap->nodes[heap->size].next_access = next_access; //Ajustando a prioridade desse objeto inserido
        heap->size++;
        heapifyUp(heap, heap->size - 1); //Manutenção da escala de prioridade do heap
    } 
    //Se o heap está cheio
    else if (next_access > heap->nodes[0].next_access) {
        heap->nodes[0].object = object; //"Retira a raiz" que sempre tem a maior prioridade e inseri o objeto
        heap->nodes[0].next_access = next_access;
        heapifyDown(heap, 0); //Manutenção da escala de prioridade do heap
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

// Função para alocar e inicializar o array de "listas ligadas" acessos futuros
ListNode **future_access_initialize(int num_objects) {
    ListNode **future_access = malloc(num_objects * sizeof(ListNode *));
    for (int i = 0; i < num_objects; i++) {
        future_access[i] = NULL;
    }
    return future_access;
}

// Função para liberar a memória de acessos futuros
void future_access_free(ListNode **future_access, int num_objects) {
    for (int i = 0; i < num_objects; i++) {
        ListNode *current = future_access[i];
        while (current != NULL) {
            ListNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(future_access);
}

// Função para preencher a estrutura future_access
void calcular_proximos_acessos(int sequence[], int length, ListNode **future_access, int num_objects) {
    //Percorre a sequência de acessos de trás para frente: length - 1 até 0
    for (int i = length - 1; i >= 0; i--) {

        //Em cada iteração, obj é o objeto acessado na posição i da sequência
        int obj = sequence[i];

        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
        newNode->access_index = i; //Armazena o índice da posição onde obj será acessado naquele nó

        //O novo nó é inserido no início da lista ligada do objeto obj
        newNode->next = future_access[obj]; //Novo nó aponte para o antigo início da lista
        future_access[obj] = newNode; //Atualiza o início da lista para o novo nó
    }
}

int find_position_heap(MaxHeap * heap, int object){
    for (int g = 0; g < heap->size; g++){
        if (heap->nodes[g].object == object) return g;
    }
    return -1;
}

void update_heap_priority(MaxHeap * heap, int object, int new_priority){
    //Localiza posição
    int position = find_position_heap(heap, object);

    //Atualizar prioridade do objeto
    heap->nodes[position].next_access = new_priority;

    //Reajustar a posição na heap de forma a manter a propriedade da heap
    heapifyUp(heap,position);
    return;
}

// Função gerencia quais objetos serão mantidos no cache e quando será necessário remover um objeto
int cache(int cache_size, int num_objects, int sequence[], int length) {
    int insercoes = 0;

    //Alocando array para armazenar os objetos atualmente no cache
    int *cache = (int *)malloc(cache_size * sizeof(int));
    int cache_count = 0; //Mantém o número atual de objetos no cache e aponta para a próxima posição disponível para um novo objeto

    //Array que armazena o próximo acesso de cada objeto
    int *next_access = next_access_initialize(num_objects, length);
    //Um array de ponteiros para listas ligadas, onde cada lista representa os índices futuros de acesso para cada objeto
    ListNode **future_access = future_access_initialize(num_objects);
    
    //Preenche future_access para cada objeto com todos os índices futuros em que ele será acessado
    calcular_proximos_acessos(sequence, length, future_access, num_objects);

    MaxHeap *heap = createHeap(cache_size);

    // Processo de gerenciamento de cache:

    //Loop Principal para Processar Cada Acesso
    for (int i = 0; i < length; i++) {
        int current_object = sequence[i];

        //A função atualiza o próximo acesso do objeto removendo o nó atual da lista ligada future_acess[i]
        if (future_access[current_object] != NULL) {
            ListNode *temp = future_access[current_object];
            future_access[current_object] = future_access[current_object]->next;
            free(temp);
        }

        if (future_access[current_object] == NULL) {
            next_access[current_object] = length; // Se não houver mais acessos futuros, define como fora do intervalo.
        } else { //Caso contrário, o próximo acesso é atualizado para o índice do próximo nó na lista ligada
            next_access[current_object] = future_access[current_object]->access_index;
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

            if (cache_count >= cache_size) { // Se o cache estiver cheio => Remover um elemento
                // Decidir qual objeto remover
                HeapNode node = extractMax(heap);

                //Manter o array cache compacto, sem lacunas, espaços vazios
                for (int j = 0; j < cache_count; j++) { //Encontrar o índice do objeto node.object no array cache
                    if (cache[j] == node.object) {
                        for (int k = j; k < cache_count - 1; k++) {
                            cache[k] = cache[k + 1];
                        }
                        cache_count--;
                        break;
                    }
                }
            }
            
            //Inserir objeto
            cache[cache_count++] = current_object; //Inserir no cache
            insertHeap(heap, current_object, next_access[current_object]); //Inserir na fila de prioridade

            //Incrementa número de inserções
            insercoes++;
            //printf("*");
  
        
        } else { //Se o objeto estiver no cache => Ajustar fila de prioridades 
            //printf(" ");
            /*
            -> Posição heap
            -> Atualizar prioridade
            -> Atulizar a posição => heapup
            */

           update_heap_priority(heap,current_object,next_access[current_object]);

            
        }
 
        // printf("%2d | ", current_object);
        // for(int k = 0; k < cache_count; k++){
        //     printf("%2d, ", heap->nodes[k].object);
        // }
        // printf("\n "); 
        // printf("%2d > ", next_access[current_object]);
        // for(int k = 0; k < cache_count; k++){
        //     printf("%2d, ", heap->nodes[k].next_access);
        // }
        // printf("\n");
        // printf("\n");
    }

    free(cache);
    free(next_access);
    future_access_free(future_access, num_objects);
    free(heap->nodes);
    free(heap);

    return insercoes;
}

int main() {
    int cache_size, num_objects, sequence_length;

    scanf("%d %d %d", &cache_size, &num_objects, &sequence_length);

    //Array contendo a sequência de acessos aos objetos
    int *sequence = (int *)malloc(sequence_length * sizeof(int));

    for (int i = 0; i < sequence_length; i++) {
        scanf("%d", &sequence[i]);
    }

    int result = cache(cache_size, num_objects, sequence, sequence_length);
    printf("%d\n", result);

    free(sequence);

    return 0;
}
