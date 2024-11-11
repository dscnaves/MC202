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

// Função de busca em profundidade (DFS) que registra a sequência de acessos
void dfsWithAccessSequence(Graph *graph, int vertex, int *visited, int *sequencia_acessos, int *index) {
    visited[vertex] = 1; // Marca o vértice atual como visitado
    sequencia_acessos[(*index)++] = vertex; // Armazena o vértice atual na sequência de acessos e incrementa o índice

    // Itera sobre todos os vértices para verificar adjacências
    for (int i = 0; i < graph->num_vertices; i++) {
        // Se há uma aresta entre o vértice atual e o vértice i e i não foi visitado
        if (graph->adjacency_matrix[vertex][i] == 1 && !visited[i]) {
            dfsWithAccessSequence(graph, i, visited, sequencia_acessos, index); // Chamada recursiva para continuar a DFS
        }
    }
}

// Função auxiliar para obter a sequência de acessos a partir de um vértice inicial
void getAccessSequence(Graph *graph, int start_vertex, int *sequencia_acessos) {
    int visited[MAX_VERTEX] = {0}; // Array para controlar os vértices visitados
    int index = 0; // Índice inicial para a sequência de acessos

    // Inicializa o array `sequencia_acessos` com -1 para indicar posições vazias
    for (int i = 0; i < graph->num_vertices; i++) {
        sequencia_acessos[i] = -1;
    }

    // Chama a DFS para obter a sequência de acessos
    dfsWithAccessSequence(graph, start_vertex, visited, sequencia_acessos, &index);
}


//Busca em profundidade (DFS) para detecção de ciclos
void dfsCycleDetection(Graph *graph, int vertex, int *visited, int parent, int *inCycle, int * pai) {

    //Marca o vértice atual como visitado
    visited[vertex] = 1;
    pai[vertex] = parent;

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
                dfsCycleDetection(graph, i, visited, vertex, inCycle,pai);
            }

            //Se o vértice vizinho i já foi visitado e não é o pai => Há um ciclo
            else if (i != parent) {
                if (inCycle[vertex] != 1 && inCycle[i] != 1){
                    //Marca tanto o vértice vertex quanto o vértice i como parte de um ciclo
                    inCycle[vertex] = 1;
                    inCycle[i] = 1;

                    //Marcar meio do vertíces pertences ao ciclo
                    int current_vertex = pai[vertex];
                    //Se chegamos ao inicio do ciclo ou se chegamos a um nó sem pai => break
                    while(inCycle[current_vertex] != 1 && current_vertex != -1){                       
                        inCycle[current_vertex] = 1;
                        current_vertex = pai[current_vertex];
                    }                    
                }
                //Caso onde há ciclos imendados
                else if (inCycle[vertex] != 1 && inCycle[i] == 1) {
                    //Marca tanto o vértice vertex quanto o vértice i como parte de um ciclo
                    inCycle[vertex] = 1;
                    
                    //Marcar meio do vertíces pertences ao ciclo
                    int current_vertex = pai[vertex];
                    //Se chegamos ao inicio do ciclo ou se chegamos a um nó sem pai => break
                    while(inCycle[current_vertex] != 1 && current_vertex != -1){                       
                        inCycle[current_vertex] = 1;
                        current_vertex = pai[current_vertex];
                    }
                }                       
            }
        }
    }
}

// Segunda busca em profundidade para atualizar o estado dos vértices no ciclo
void dfsUpdateCycleStatus(Graph *graph, int vertex, int *inCycle, int *pai, int *sequencia_acessos_profundidade) {
    for (int x = 0; x < graph->num_vertices; x++) {
        int current_vertex = sequencia_acessos_profundidade[x];

        // Verifica se chegamos ao final da sequência de acessos
        if (current_vertex == -1) {
            break;
        }

        // Verifica se o pai do vértice atual está em um ciclo e o próprio vértice ainda não faz parte de um ciclo ou não está marcado
        if (pai[current_vertex] != -1 && inCycle[pai[current_vertex]] == 1 && inCycle[current_vertex] == 0) {
            // Marca o vértice atual como "Apagado" (valor 2)
            inCycle[current_vertex] = 2;
        }
    }
}



// Função para classificar as lâmpadas com base nas distâncias e ciclos
void classifyLamps(Graph *graph, int source) {
    int distances[MAX_VERTEX];  //Distância mínima de cada lâmpada em relação à lâmpada de origem (source)
    int inCycle[MAX_VERTEX] = {0};
    int visited[MAX_VERTEX] = {0};
    int pai[MAX_VERTEX];
    for (int i = 0; i < MAX_VERTEX; i++) pai[i] = -1;

    int sequencia_acessos_profundidade[MAX_VERTEX] = {-1}; // Array para armazenar a sequência de acessos

    //Inicialmente consideramos que todas as lâmpadas estão não acessíveis
    for (int i = 0; i < graph->num_vertices; i++) {
        distances[i] = -1;  // Inicializa distâncias como -1 (não acessível)
    }

    //BFS garante que a distância calculada para cada vértice é a mínima em termos de número de arestas
    bfs(graph, source, distances);

    //Marcar as lâmpadas que fazem parte de ciclos
    //Vértice inicial (source) não tem um "pai" => -1 indica isso porque nenhum vértice tem esse valor
    dfsCycleDetection(graph, source, visited, -1, inCycle, pai);  // Detecta ciclos

    // Obtém a sequência de acessos por DFS a partir do vértice de origem
    getAccessSequence(graph, source, sequencia_acessos_profundidade);

    //Atualizar o estado dos vértices no ciclo
    dfsUpdateCycleStatus(graph, source, inCycle, pai, sequencia_acessos_profundidade);

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