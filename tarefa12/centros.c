#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // Inclui INT_MAX

#define NOT_FOUND_city -1
#define INF INT_MAXf

// Estrutura para representar uma cidade
typedef struct {
    char name[50];
    int population;
} City;


// Estrutura para representar uma aresta no grafo
typedef struct Edge {
    int destination; // Índice da cidade de destino
    int weight; // Distância entre as cidades | "Peso da aresta"
    struct Edge *next; // Aponta para a próxima aresta na lista de adjacências
} Edge;


/*
- Estrutura para representar uma lista de adjacências
- Uma lista de adjacências para cada cidade
Armazenando as arestas que partem desta cidade
- Só um ponteiro que aponta para o 1° elemento da Lista de Arestas/Conexões
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
        Edge * edge = graph->adj_lists[i].head;
        while (edge != NULL) {
            printf(" %s (Distância: %d) ", graph->cities[edge->destination].name, edge->weight);
            edge = edge->next;
            
            if (edge != NULL) {
                printf("->");
            }
        }
        printf("\n");
        printf("\n");
    }
}

// Adiciona uma conexão (aresta) entre duas cidades (nós) no grafo
void add_edge(Graph * graph, int source_city, int destination_city, int weight_egde) {
    //Criando ligação de A->B:
    Edge * newEdge = (Edge *)malloc(sizeof(Edge));
    
    newEdge->destination = destination_city;
    newEdge->weight = weight_egde;

    /*Define o ponteiro next da nova Edge para apontar para a cabeça atual da lista de adjacências de source (graph->adj_lists[source].head)*/
    newEdge->next = graph->adj_lists[source_city].head;

    /*Atualiza graph->adj_lists[source].head para apontar para a nova Edge, tornando-a a nova cabeça da lista*/
    graph->adj_lists[source_city].head = newEdge;

    //Criando ligação bidirecional de B->A:
    newEdge = (Edge *)malloc(sizeof(Edge));
    newEdge->destination = source_city;
    newEdge->weight = weight_egde;    
    newEdge->next = graph->adj_lists[destination_city].head;
    graph->adj_lists[destination_city].head = newEdge;
}

//Procura uma cidade pelo nome e retorna seu índice
int find_city_index(Graph * graph, char * name) {
    for (int i = 0; i < graph->num_cities; i++) {
        if (strcmp(graph->cities[i].name, name) == 0) {
            return i;
        }
    }
    //Se não encontrar a cidade, retorna -1
    return NOT_FOUND_city;
}

//Calcular a menor distância de uma cidade de origem a todas as outras no grafo
void dijkstra(Graph *graph, int source_city, int dist[]) {
    int visited[MAX_CITIES] = {0};

    //Armazenando as menores distâncias encontradas da cidade de origem src_city até cada cidade
    for (int i = 0; i < graph->num_cities; i++) {
        dist[i] = INT_MAX; //Inicializar com uma distância "infinita" para marcar que a distância não foi contabilizada
    }
    dist[source_city] = 0; //A distância da cidade de origem com ela mesma é zero

    // Todas as cidades acessíveis a partir da origem já terão sido processadas
    for (int i = 0; i < graph->num_cities - 1; i++) {
        int min_dist = INT_MAX;
        int lower_distance_index = -1; //Index da cidade de menor distancia até source

        for (int j = 0; j < graph->num_cities; j++) {
            //Se a cidade_destino u não foi visitada && a distância entre a cidade origem-u é menor que a mínima
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j]; //A cidadeu é a cidade de distância mínima
                lower_distance_index = j;
            }
        }

        if (lower_distance_index == -1) break;




        /* Atualiza a distância de uma cidade para outra cidade adjacente 
        se for encontrado um caminho mais curto ao se passar por uma cidade intermediária*/

        
        // Um ponteiro que será usado para percorrer todas as conexões (arestas) da cidade lower_distance
        // Inicializando current_edge para apontar para a lista de adjacências da cidade lower_distance
        Edge *current_edge = graph->adj_lists[lower_distance_index].head;

        // Percorre todas as arestas partindo de lower_distance
        while (current_edge != NULL) {
            // Armazena o índice da cidade adjacente conectada diretamente a lower_distance por meio da aresta current_edge
            int dest_city = current_edge->destination;

            /*
            Verifica se dest_city ainda não foi visitada (ou seja, ainda não processamos essa cidade como destino final)
            Verifica se a distância de source até dest_city, passando por lower_distance, é menor que a menor distância conhecida até dest_city diretamente
            */
            if (!visited[dest_city] && dist[lower_distance_index] + current_edge->weight < dist[dest_city]) {
                //Calcula a nova distância até dest_city, passando por lower_distance
                dist[dest_city] = dist[lower_distance_index] + current_edge->weight;
            }
            //Ir para próxima conexão de lower_dist
            current_edge = current_edge->next;
        }
    }
}


int main(){
    int num_cities, num_routes;
    scanf("%d", &num_cities);
    
    Graph graph;

    init_graph(&graph, num_cities);

    // Lendo as cidades e suas populações
    for (int i = 0; i < num_cities; i++) {
        scanf("%s %d", graph.cities[i].name, &graph.cities[i].population);
    }

    // Lendo o número de rotas
    scanf("%d", &num_routes);
    for (int i = 0; i < num_routes; i++) {
        char city1[50], city2[50];
        int distance;
        scanf("%s %s %d", city1, city2, &distance);

        int index1 = find_city_index(&graph, city1);
        int index2 = find_city_index(&graph, city2);

        if (index1 != NOT_FOUND_city && index2 != NOT_FOUND_city){
            add_edge(&graph, index1, index2, distance);
        }
        else printf("Cidades não devidamente adicionadas");        
    }
    
    print_graph(&graph);


    return 0;
}
