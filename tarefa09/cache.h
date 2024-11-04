#ifndef CACHE_H
#define CACHE_H

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
    int next_access;
    int index_cache;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    int size;
    int capacity;
} MaxHeap;

// Funções de manipulação da heap
MaxHeap *createHeap(int capacity);
void swap(HeapNode *a, HeapNode *b, int *heap_positions);
void heapifyUp(MaxHeap *heap, int index, int *heap_positions);
void heapifyDown(MaxHeap *heap, int index, int *heap_positions);
void insertHeap(MaxHeap *heap, int object, int next_access, int *heap_positions);
HeapNode extractMax(MaxHeap *heap, int *heap_positions);
void update_heap_priority(MaxHeap *heap, int object, int new_priority, int *heap_positions);

// Funções de manipulação de acessos futuros
int *next_access_initialize(int num_objects, int length);
ListNode **future_access_initialize(int num_objects);
void future_access_free(ListNode **future_access, int num_objects);
void calcular_proximos_acessos(int sequence[], int length, ListNode **future_access, int num_objects);
void atualizar_proximo_acesso(int current_object, int length, ListNode **future_access, int *next_access);

// Funções de manipulação do cache
int *createCachePositions(int num_objects);
int verificar_objeto_no_cache(int current_object, int *cache_positions);
void inserir_no_cache(int current_object, int *cache, int *cache_count, int cache_size, MaxHeap *heap, int *cache_positions, int *heap_positions, int *next_access);
int cache(int cache_size, int num_objects, int sequence[], int length);

#endif // CACHE_H
