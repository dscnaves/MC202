#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 100

// Estrutura para representar uma cidade
typedef struct {
    char name[50];
    int population;
} City;


// Estrutura para representar uma aresta no grafo
typedef struct Edge {
    int dest; // Índice da cidade de destino
    int weight; // Distância entre as cidades | "Peso da aresta"
    struct Edge *next; // Aponta para a próxima aresta na lista de adjacências
} Edge;


/*
- Estrutura para representar uma lista de adjacências
- Uma lista de adjacências para cada cidade
Armazenando as arestas que partem desta cidade
*/
typedef struct AdjList {
    Edge * head;
} AdjList;


// Estrutura para representar o Graph
typedef struct {
    // Número de cidades
    int num_cities;
    // #Array contendo cidades
    City * cities;
    // #Array contenco as listas de adjacências para armazenar as conexões de cada cidade
    AdjList * adj_lists;
} Graph;

void init_graph(Graph * graph, int num_cities) {
    graph->num_cities = num_cities;

    graph->cities = malloc(num_cities * sizeof(City));

    graph->adj_lists = malloc(num_cities * sizeof(AdjList));

    for (int i = 0; i < num_cities; i++) {
        graph->adj_lists[i].head = NULL;
    }
}

// Função para imprimir o grafo
void print_graph(Graph *graph) {
    printf("Grafo de Cidades:\n");

    for (int i = 0; i < graph->num_cities; i++) {
        printf("Cidade: %s (População: %d) -> ", graph->cities[i].name, graph->cities[i].population);
        
        // Percorre a lista de adjacências da cidade atual
        Edge *edge = graph->adj_lists[i].head;
        while (edge != NULL) {
            printf(" %s (Distância: %d) ", graph->cities[edge->dest].name, edge->weight);
            edge = edge->next;
            
            if (edge != NULL) {
                printf("->");
            }
        }
        printf("\n");
    }
}

int main(){
    int num_cities; //, num_routes;
    scanf("%d", &num_cities);

    Graph graph;

    init_graph(&graph, num_cities);

    print_graph(&graph);


    return 0;
}
