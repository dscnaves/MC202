#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX 1000

// Estrutura para o grafo representado por uma matriz de adjacência
typedef struct Graph {
    int num_vertices;
    int **adjacency_matrix;
} Graph;

// Criação e alocação da matriz de adjacência
Graph *create_matrix(int num_vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adjacency_matrix = malloc(num_vertices * sizeof(int *));
    for (int i = 0; i < num_vertices; i++) {
        graph->adjacency_matrix[i] = malloc(num_vertices * sizeof(int));
    }
    return graph;
}

// Inicializa a matriz com zeros
void initialize_matrix(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        for (int j = 0; j < graph->num_vertices; j++) {
            graph->adjacency_matrix[i][j] = 0;
        }
    }
}

// Constrói a matriz com as conexões corretas
void build_matrix(Graph *graph, int num_connections) {
    int x, y;
    for (int i = 0; i < num_connections; i++) {
        scanf("%d %d", &x, &y);
        graph->adjacency_matrix[x][y] = 1;
        graph->adjacency_matrix[y][x] = 1;
    }
}

// Libera a memória alocada para a matriz
void free_matrix(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        free(graph->adjacency_matrix[i]);
    }
    free(graph->adjacency_matrix);
    free(graph);
}

// Realiza busca em largura (BFS) para calcular distâncias a partir do vértice de origem
void bfs(Graph *graph, int start_vertex, int *distances) {
    int visited[MAX_VERTEX] = {0};
    int queue[MAX_VERTEX];
    int front = 0, rear = 0;

    visited[start_vertex] = 1;
    distances[start_vertex] = 0;
    queue[rear++] = start_vertex;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 0; i < graph->num_vertices; i++) {
            if (graph->adjacency_matrix[current][i] && !visited[i]) {
                visited[i] = 1;
                distances[i] = distances[current] + 1;
                queue[rear++] = i;
            }
        }
    }
}

// Busca em profundidade iterativa para detecção de ciclos
void dfsCycleDetection_iterative(Graph *graph, int start_vertex, int *inCycle) {
    int visited[MAX_VERTEX] = {0};
    int stack[MAX_VERTEX];
    int parent[MAX_VERTEX];
    int top = -1;

    stack[++top] = start_vertex;
    parent[start_vertex] = -1;

    while (top >= 0) {
        int current = stack[top--];
        visited[current] = 1;

        for (int i = 0; i < graph->num_vertices; i++) {
            if (graph->adjacency_matrix[current][i]) {
                if (!visited[i]) {
                    parent[i] = current;
                    stack[++top] = i;
                } else if (i != parent[current]) {  // Ciclo detectado
                    inCycle[current] = 1;
                    inCycle[i] = 1;
                    int cycle_vertex = parent[current];
                    while (cycle_vertex != -1 && inCycle[cycle_vertex] == 0) {
                        inCycle[cycle_vertex] = 1;
                        cycle_vertex = parent[cycle_vertex];
                    }
                }
            }
        }
    }
}

// Classifica as lâmpadas com base nas distâncias e nos ciclos
void classifyLamps(Graph *graph, int source) {
    int distances[MAX_VERTEX];
    int inCycle[MAX_VERTEX] = {0};

    for (int i = 0; i < graph->num_vertices; i++) {
        distances[i] = -1;
    }

    // Calcula distâncias mínimas a partir do vértice de origem
    bfs(graph, source, distances);

    // Detecta ciclos e marca os vértices em ciclos
    dfsCycleDetection_iterative(graph, source, inCycle);

    // Exibe as lâmpadas com base na distância e no estado
    for (int d = 0; d < graph->num_vertices; d++) {
        for (int i = 0; i < graph->num_vertices; i++) {
            if (distances[i] == d && distances[i] != -1) {
                if (inCycle[i] == 1) {
                    printf("%d a distancia %d: queimada\n", i, d);
                } else if (inCycle[i] == 2) {
                    printf("%d a distancia %d: apagada\n", i, d);
                } else {
                    printf("%d a distancia %d: acesa\n", i, d);
                }
            }
        }
    }
}

// Função principal
int main() {
    int num_vertices, num_connections, source;
    scanf("%d %d %d", &num_vertices, &num_connections, &source);

    Graph *graph = create_matrix(num_vertices);
    initialize_matrix(graph);
    build_matrix(graph, num_connections);

    classifyLamps(graph, source);

    free_matrix(graph);
    return 0;
}
