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
    Edge * head_AjdList;
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

int main(){
    int num_cities, num_routes;
    scanf("%d", &num_cities);

    Graph graph;
    


    return 0;
}
