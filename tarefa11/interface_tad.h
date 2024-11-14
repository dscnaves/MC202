#ifndef interface_tad
#define interface_tad

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX 1000

//Estrutura para o grafo representado por uma matriz de adjacência
typedef struct Graph {
    int num_vertices;
    int ** adjacency_matrix;
} Graph;

Graph* create_matrix(int num_vertices);
void initialize_matrix(Graph *graph);
void build_matrix(Graph *graph, int num_conections);
void print_matrix(Graph *graph);
void free_matrix(Graph *graph);

void bfs(Graph *graph, int start_vertex, int *distances);
void dfsWithAccessSequence(Graph *graph, int vertex, int *visited, int *sequencia_acessos, int *index);
void getAccessSequence(Graph *graph, int start_vertex, int *sequencia_acessos);
void dfsCycleDetection(Graph *graph, int vertex, int *visited, int parent, int *inCycle, int *pai);
void dfsUpdateCycleStatus(Graph *graph, int vertex, int *inCycle, int *pai, int *sequencia_acessos_profundidade);
void classifyLamps(Graph *graph, int source);

#endif // interface_tad