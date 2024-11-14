#include "interface_tad.h"

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

        if (index1 != NOT_FOUND_CITY && index2 != NOT_FOUND_CITY){
            add_edge(&graph, index1, index2, distance);
        }
        else printf("Cidades não devidamente adicionadas\n");        
    }

    // Encontra e imprime os melhores centros de distribuição
    find_best_centers(&graph);

    //Liberar memória
    free_graph(&graph);

    return 0;
}
