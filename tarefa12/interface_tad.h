#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // Inclui INT_MAX

#define NOT_FOUND_CITY -1
#define INF INT_MAX
#define MAX_CITIES 100

// Estrutura para representar uma cidade
typedef struct {
    char name[50];
    int population;
} City;


// Estrutura para representar uma aresta no grafo
typedef struct Edge {
    int destination; // Índice da cidade de destino
    int weight; // Distância entre as cidades | "Peso da aresta"
    struct Edge *next; // Aponta para a próxima aresta na lista de adjacências
} Edge;


/*
- Estrutura para representar uma lista de adjacências
- Uma lista de adjacências para cada cidade
Armazenando as arestas que partem desta cidade
- Só um ponteiro que aponta para o 1° elemento da Lista de Arestas/Conexões
*/
typedef struct AdjList {
    Edge * head;
} AdjList;


// Estrutura para representar o Graph
typedef struct {
    // Número de cidades
    int num_cities;
    // Array contendo cidades
    City * cities;
    // Array contenco as listas de adjacências para armazenar as conexões de cada cidade
    AdjList * adj_lists;
} Graph;

void init_graph(Graph *graph, int num_cities);
void print_graph(Graph *graph);
void add_edge(Graph *graph, int source_city, int destination_city, int weight_edge);
int find_city_index(Graph *graph, char *name);
void dijkstra(Graph *graph, int source_city, int dist[]);
void find_best_centers(Graph *graph);
void free_graph(Graph *graph);

#endif // GRAPH_H
