#include "interface_tad.h"

int main(){
    //Reading of data
    int num_vertices, num_conections, source;
    scanf("%d %d %d", &num_vertices, &num_conections, &source);

    //Creating and allocating the matrix 
    Graph * graph = create_matrix(num_vertices);

    //Initiazlizing the matrix with zerous
    initialize_matrix(graph);

    //Building the matrix with the right conections
    build_matrix(graph, num_conections);

    //Classifica as lâmpadas e exibe o estado de cada uma
    classifyLamps(graph, source);
    
    //Libera a memória alocada para o grafo
    free_matrix(graph);
    
    return 0;
}