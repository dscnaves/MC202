#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

typedef struct {
    int object;
    int next_use;
} CacheItem;

void swap(CacheItem* a, CacheItem* b) {
    CacheItem temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(CacheItem heap[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].next_use < heap[smallest].next_use) {
        smallest = left;
    }

    if (right < n && heap[right].next_use < heap[smallest].next_use) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, n, smallest);
    }
}

void push(CacheItem heap[], int* size, CacheItem item) {
    heap[*size] = item;
    (*size)++;
    int i = *size - 1;
    while (i != 0 && heap[(i - 1) / 2].next_use > heap[i].next_use) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

CacheItem pop(CacheItem heap[], int* size) {
    CacheItem root = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify(heap, *size, 0);
    return root;
}

void preprocess_next_occurrences(int sequence[], int sequence_length, int num_objects, int **future_access) {
    int *next_occurrence = (int *)malloc(num_objects * sizeof(int));

    for (int i = 0; i < num_objects; i++) {
        next_occurrence[i] = sequence_length;  // Initialize to "infinite" (end of sequence)
    }

    for (int i = sequence_length - 1; i >= 0; i--) {
        future_access[i] = (int *)malloc(num_objects * sizeof(int));
        for (int j = 0; j < num_objects; j++) {
            future_access[i][j] = next_occurrence[j];
        }
        next_occurrence[sequence[i]] = i;
    }

    free(next_occurrence);
}

int cache_simulation(int cache_size, int num_objects, int sequence[], int sequence_length) {
    int insertions = 0;

    CacheItem* heap = (CacheItem*)malloc(cache_size * sizeof(CacheItem));
    int heap_size = 0;

    int** future_access = (int**)malloc(sequence_length * sizeof(int*));
    int* in_cache = (int*)calloc(num_objects, sizeof(int));

    preprocess_next_occurrences(sequence, sequence_length, num_objects, future_access);

    for (int i = 0; i < sequence_length; i++) {
        int obj = sequence[i];

        if (in_cache[obj]) {
            for (int j = 0; j < heap_size; j++) {
                if (heap[j].object == obj) {
                    heap[j].next_use = future_access[i][obj];
                    heapify(heap, heap_size, j);
                    break;
                }
            }
        } else {
            if (heap_size >= cache_size) {
                CacheItem removed = pop(heap, &heap_size);
                in_cache[removed.object] = 0;
            }

            CacheItem new_item = {obj, future_access[i][obj]};
            push(heap, &heap_size, new_item);
            in_cache[obj] = 1;
            insertions++;
        }
    }

    for (int i = 0; i < sequence_length; i++) {
        free(future_access[i]);
    }

    free(future_access);
    free(heap);
    free(in_cache);

    return insertions;
}

int main() {
    int cache_size, num_objects, sequence_length;
    scanf("%d %d %d", &cache_size, &num_objects, &sequence_length);

    int* sequence = (int*)malloc(sequence_length * sizeof(int));
    for (int i = 0; i < sequence_length; i++) {
        scanf("%d", &sequence[i]);
    }

    int result = cache_simulation(cache_size, num_objects, sequence, sequence_length);
    printf("%d\n", result);

    free(sequence);
    return 0;
}
