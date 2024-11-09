#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

//Busca em profundidade (DFS) para detecção de ciclos
void dfsCycleDetection(Graph *graph, int vertex, int *visited, int parent, int *inCycle, int * pai, int * sequencia_acessos_profundidade, int k) {
    
    printf("- %d ->", vertex);

    //Marca o vértice atual como visitado
    visited[vertex] = 1;
    pai[vertex] = parent;
    sequencia_acessos_profundidade[k] = vertex;
    k++;

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
                dfsCycleDetection(graph, i, visited, vertex, inCycle,pai,sequencia_acessos_profundidade, k);
            }

            //Se o vértice vizinho i já foi visitado e não é o pai => Há um ciclo
            else if (i != parent) {
                if (inCycle[vertex] != 1 && inCycle[i] != 1){
                    //Marca tanto o vértice vertex quanto o vértice i como parte de um ciclo
                    inCycle[vertex] = 1;
                    inCycle[i] = 1;

                    //Marcar meio do vertíces pertences ao ciclo
                    printf("\nPor quem passamos no ciclo voltando pelo caminho onde viemos:\n");
                    int current_vertex = pai[vertex];
                    //Se chegamos ao inicio do ciclo ou se chegamos a um nó sem pai => break
                    while(inCycle[current_vertex] != 1 && current_vertex != -1){
                        printf(" °%d° ", current_vertex);
                        
                        inCycle[current_vertex] = 1;
                        current_vertex = pai[current_vertex];
                    }                    
                }                          
            }
        }
    }
}

//Segunda busca em profundidade para atualizar o estado dos vértices no ciclo
void dfsUpdateCycleStatus(Graph *graph, int vertex, int *inCycle, int *pai, int * sequencia_acessos_profundidade) {
    for (int x = 0; x<graph->num_vertices ;x++){
        int current_vertex = sequencia_acessos_profundidade[x];
        
        // Se o pai do vértice atual está dentro de um ciclo
        if (inCycle[pai[current_vertex]] == 1) {
            // E se o vértice atual não está dentro do ciclo
            if (inCycle[current_vertex] == 0) {
                // Marca o vértice atual como "Apagado" (valor 2)
                inCycle[current_vertex] = 2;
            }
        }
    }
    
}

// Função para classificar as lâmpadas com base nas distâncias e ciclos
void classifyLamps(Graph *graph, int source) {
    int distances[MAX_VERTEX];  //Distância mínima de cada lâmpada em relação à lâmpada de origem (source)
    int inCycle[MAX_VERTEX] = {0};
    int visited[MAX_VERTEX] = {0};
    int pai[MAX_VERTEX] = {0};

    int sequencia_acessos_profundidade[MAX_VERTEX];
    int k = 0;

    //Inicialmente consideramos que todas as lâmpadas estão não acessíveis
    for (int i = 0; i < graph->num_vertices; i++) {
        distances[i] = -1;  // Inicializa distâncias como -1 (não acessível)
    }

    //BFS garante que a distância calculada para cada vértice é a mínima em termos de número de arestas
    bfs(graph, source, distances);


    print_matrix(graph);
    printf("\n");
    for(int i=0; i<graph->num_vertices; i++){
        printf("%d ", distances[i]);
    }
    printf("\n");



    //Marcar as lâmpadas que fazem parte de ciclos
    //Vértice inicial (source) não tem um "pai" => -1 indica isso porque nenhum vértice tem esse valor
    dfsCycleDetection(graph, source, visited, -1, inCycle, pai, sequencia_acessos_profundidade,k);  // Detecta ciclos



    printf("\n");
    for(int i=0; i<graph->num_vertices; i++){
        printf("%d ", inCycle[i]);
    }
    printf("\n");



    //Nova chamada para a função dfsUpdateCycleStatus para atualizar o estado dos vértices no ciclo
    for (int i = 0; i < graph->num_vertices; i++) visited[i] = 0; // Reinicia o array visited
    dfsUpdateCycleStatus(graph, source, visited, inCycle, pai);

    //Exibe as lâmpadas em ordem de distância e status
    //Primeira iteração: percorre todos os valores possíveis de distância (d)
    for (int d = 0; d < graph->num_vertices; d++) {
        //Percorre todos os vértices do grafo (i) para encontrar as lâmpadas cuja distances[i] corresponde à distância d
        for (int i = 0; i < graph->num_vertices; i++) {
            //A lâmpada i de distândia d é acessível/energizada a partir da fonte
            if (distances[i] == d && distances[i] != -1) {
                if (inCycle[i] == 1)
                    printf("%d a distancia %d: queimada\n", i, d);
                else if (inCycle[i] == 2)
                    printf("%d a distancia %d: apagada\n", i, d);
                else if ((inCycle[i] == 0)){
                    printf("%d a distancia %d: acesa\n", i, d);
                }
            }
        }
    }
}


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