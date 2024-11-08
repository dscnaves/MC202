#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 1000

//Estrutura para o grafo representado por uma matriz de adjacência
typedef struct Graph {
    int num_vertices;
    int ** adjacency_matrix;
} Graph;

//Creating and allocating the matrix 
Graph * create_matrix(int num_vertices){
    // Aloca memória para a estrutura do grafo
    Graph * graph = malloc(sizeof(Graph));

    // Define o número de vértices no grafo
    graph->num_vertices = num_vertices;

    // Aloca memória para a matriz de adjacência (array de ponteiros para as linhas)
    graph->adjacency_matrix = malloc(num_vertices * sizeof(int *));

    for (int i = 0; i<num_vertices; i++){
        graph->adjacency_matrix[i] = malloc(num_vertices*sizeof(int));
    }

    return graph;
}

void initialize_matrix(Graph * graph, int num_vertices){
    //Inicializa a matriz de adjacência com zeros
    for (int i = 0; i<num_vertices; i++){
        for (int j = 0; j<num_vertices; j++){
            graph->adjacency_matrix[i] = 0;
        }        
    }
    return;
}


int main(){

    return 0;
}