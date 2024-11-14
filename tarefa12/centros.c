#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // Inclui INT_MAX

#define NOT_FOUND_city -1
#define INF INT_MAX
#define MAX_CITIES 100

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
    if (graph->cities == NULL){
        printf("Erro de alocação de memória array cities");
        exit(1);
    }

    graph->adj_lists = malloc(num_cities * sizeof(AdjList));
    if (graph->adj_lists == NULL){
        printf("Erro de alocação de memória array adj_lists");
        exit(1);
    }


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
void add_edge(Graph * graph, int source_city, int destination_city, int weight_edge) {
    //Criando ligação de A->B:
    Edge * newEdge = (Edge *)malloc(sizeof(Edge));
    if (newEdge == NULL){
        printf("Erro de alocação de memória aresta newEgde");
        exit(1);
    }
    
    newEdge->destination = destination_city;
    newEdge->weight = weight_edge;

    /*Define o ponteiro next da nova Edge para apontar para a cabeça atual da lista de adjacências de source (graph->adj_lists[source].head)*/
    newEdge->next = graph->adj_lists[source_city].head;

    /*Atualiza graph->adj_lists[source].head para apontar para a nova Edge, tornando-a a nova cabeça da lista*/
    graph->adj_lists[source_city].head = newEdge;


    //Criando ligação bidirecional de B->A:
    newEdge = (Edge *)malloc(sizeof(Edge));
    if (newEdge == NULL){
        printf("Erro de alocação de memória aresta newEgde");
        exit(1);
    }
    newEdge->destination = source_city;
    newEdge->weight = weight_edge;    
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
        dist[i] = INF; //Inicializar com uma distância "infinita" para marcar que a distância não foi contabilizada
    }
    dist[source_city] = 0; //A distância da cidade de origem com ela mesma é zero

    // Todas as cidades acessíveis a partir da origem já terão sido processadas
    for (int i = 0; i < graph->num_cities - 1; i++) {
        int min_dist = INF;
        int lower_distance_index = -1; //Index da cidade de menor distancia até source

        for (int j = 0; j < graph->num_cities; j++) {
            //Se a cidade_destino u não foi visitada && a distância entre a cidade origem-u é menor que a mínima
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j]; //A cidadeu é a cidade de distância mínima
                lower_distance_index = j;
            }
        }

        if (lower_distance_index == -1) break;

        // Significa que já encontramos o menor caminho até a cidade lower_distance e não precisamos processá-la novamente
        visited[lower_distance_index] = 1;


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

/*
Responsável por encontrar o melhor par de cidades para instalar dois centros de distribuição
Objetivo: minimizar a "maior distância de atendimento" de qualquer cidade até o centro de distribuição mais próximo
*/
void find_best_centers(Graph *graph) {
    //Índices das cidades escolhidas para os centros de distribuição
    int best_city1 = -1, best_city2 = -1;
    //Menor "maior distância de atendimento" entre todas as cidades e o centro mais próximo
    int min_max_distance = MAX_CITIES;
    int max_population_sum = 0;

    //Laço para Testar Pares de Cidades
    //Percorre cada cidade i no grafo
    for (int i = 0; i < graph->num_cities; i++) {
        //Percorre cada cidade j após i, para formar pares únicos de cidades (i, j)
        //Garante não repetição de combiação enntre cidades
        for (int j = i + 1; j < graph->num_cities; j++) {

        //Calcular Distâncias para Cada Par de Cidades:
            int dist_from_i[MAX_CITIES], dist_from_j[MAX_CITIES];
            dijkstra(graph, i, dist_from_i);
            dijkstra(graph, j, dist_from_j);

        // Calcular a Maior Distância de Atendimento para o Par de Cidades (i, j):
            // Armazena a maior distância de atendimento para o par de cidades (i, j)
            int max_distance = 0;
            //Percorre cada cidade k e calcula a menor distância de k até o centro de distribuição mais próximo entre i e j
            for (int k = 0; k < graph->num_cities; k++) {
                // Menor valor entre dist_from_i[k] e dist_from_j[k]
                int min_distance = dist_from_i[k] < dist_from_j[k] ? dist_from_i[k] : dist_from_j[k];
                /*Se min_distance é maior que o max_distance atual, ele é atualizado
                Isso nos dá a maior distância de atendimento para qualquer cidade com os centros localizados em i e j
                */
                if (min_distance > max_distance) {
                    max_distance = min_distance;
                }
            }

            int population_sum = graph->cities[i].population + graph->cities[j].population;
            /*Se max_distance for menor que min_max_distance, então o par (i, j) é uma opção melhor
            pois reduz a maior distância de atendimento
            ||
            Se max_distance é igual a min_max_distance, o par com a maior soma populacional (population_sum) é preferido
            */
            if (max_distance < min_max_distance ||
                (max_distance == min_max_distance && population_sum > max_population_sum)) {
                min_max_distance = max_distance;
                max_population_sum = population_sum;
                best_city1 = i;
                best_city2 = j;
            }
        }
    }

    printf("Centros de distribuicao: %s e %s\n", graph->cities[best_city1].name, graph->cities[best_city2].name);
    printf("Distancia de atendimento: %d\n", min_max_distance);
}

void free_graph(Graph *graph) {
    // Libera todas as arestas:
    //Para cada lista de adjacência
    for (int i = 0; i < graph->num_cities; i++) {
        //Inicializa a variável current para começar liberando pelo início da lista de adj
        Edge *current = graph->adj_lists[i].head;
        //Para cada aresta
        while (current != NULL) {
            Edge *temp = current;
            current = current->next;
            //Libera a aresta
            free(temp);
        }
    }

    // Libera arrays de cidades e listas de adjacências
    free(graph->cities);
    free(graph->adj_lists);
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
        else printf("Cidades não devidamente adicionadas\n");        
    }

    // Encontra e imprime os melhores centros de distribuição
    find_best_centers(&graph);

    return 0;
}
