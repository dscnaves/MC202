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

//Realiza uma busca em largura (Breadth-First Search, BFS) para calcular as distâncias entre um vértice de origem (start_vertex) e todos os outros vértices do grafo
void bfs(Graph *graph, int start_vertex, int *distances) {
    //Array para marcar os vértices visitados
    int visited[MAX_VERTEX] = {0};
    
    //Fila de prioridade FIFO para o controle dos vértices a serem processados
    int priority_queue[MAX_VERTEX];
    int front = 0; //"Frente" => Posição da fila de onde o próximo vértice será retirado para ser processado
    int rear = 0; //"Traseira" => Posição na qual o próximo vértice será inserido na fila

    //Marca o vértice inicial como visitado
    visited[start_vertex] = 1;
    //A distância para o vértice inicial é zero
    distances[start_vertex] = 0;
    //Adiciona o vértice inicial à fila
    priority_queue[rear++] = start_vertex;

    //Processamento da fila enquanto houver vértices => Quando (front == rear) => significa que todos os vértices acessíveis a partir do vértice inicial foram visitados
    while (front < rear) {
        //Pega o vértice na frente da fila (current) e avança o ponteiro front, indicando que esse vértice será processado
        int current = priority_queue[front++];

        //Explora todos os vértices adjacentes ao vértice atual (current)
        //Iterar sob todos os vertices do grafo
        for (int i = 0; i < graph->num_vertices; i++) {
            //Verifica se existe uma aresta entre current e i && e se i ainda não foi visitado
            if (graph->adjacency_matrix[current][i] && !visited[i]) {
                visited[i] = 1;
                distances[i] = distances[current] + 1; //i está um passo mais distante da origem do que current
                //Adiciona o vértice i ao final da fila para que ele seja processado após os vértices que já estão na fila
                priority_queue[rear++] = i;
            }
        }
    }
}

// Implementação da busca em profundidade (DFS) para detecção de ciclos
void dfsCycleDetection(Graph *graph, int vertex, int *visited, int parent, int *inCycle) {
    //Marca o vértice atual como visitado
    visited[vertex] = 1;

    //Itera sobre todos os vértices para verificar adjacências
    for (int i = 0; i < graph->num_vertices; i++) {
        
        //Se há uma aresta entre o vértice atual e o vértice i
        if (graph->adjacency_matrix[vertex][i] == 1) {
            
            //Há uma conexão
            //Se o vértice vizinho i ainda não foi visitado
            if (!visited[i]) {
                /* -> Se i não foi visitado, chamamos a dfsCycleDetection recursivamente para explorar i
                -> Vertex passa a ser o pai de i
                -> Continuando a busca até que não haja mais vértices não visitados conectados a i */
                dfsCycleDetection(graph, i, visited, vertex, inCycle);
            }

            //Se o vértice vizinho i já foi visitado e não é o pai => Há um ciclo
            else if (i != parent) {
                //Marca tanto o vértice vertex quanto o vértice i como parte de um ciclo
                inCycle[vertex] = 1;
                inCycle[i] = 1;
            }
        }
    }
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