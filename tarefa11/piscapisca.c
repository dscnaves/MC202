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

//Initiazlizing the matrix with zerous
void initialize_matrix(Graph * graph){
    for (int i = 0; i<graph->num_vertices; i++){
        for (int j = 0; j<graph->num_vertices; j++){
            graph->adjacency_matrix[i][j] = 0;
        }        
    }
    return;
}

//Building the matrix with the right conections
void build_matrix(Graph * graph, int num_conections){
    int x,y;
    for (int i = 0; i<num_conections; i++){
        scanf("%d %d",&x,&y);

        graph->adjacency_matrix[x][y] = 1;
        graph->adjacency_matrix[y][x] = 1;
    }
}

//Printing the matriz
void print_matrix(Graph * graph){
    for(int i = 0; i<graph->num_vertices; i++){
        for(int j = 0; j<graph->num_vertices; j++){
            printf("%d ", graph->adjacency_matrix[i][j]);
        }
        printf("\n");
    }
    return;
}

void free_matrix(Graph *graph){
    for (int i = 0; i<graph->num_vertices; i++){
        free(graph->adjacency_matrix[i]);
    }
    free(graph->adjacency_matrix);
    free(graph);
}

int main(){
    //Reading of data
    int num_vertices, num_conections;
    scanf("%d %d", &num_vertices, &num_conections);

    //Creating and allocating the matrix 
    Graph * graph = create_matrix(num_vertices);

    //Initiazlizing the matrix with zerous
    initialize_matrix(graph);

    //Building the matrix with the right conections
    build_matrix(graph, num_conections);

    print_matrix(graph);

    free_matrix(graph);
    

    return 0;
}