#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

int main() {
    int size;
    scanf("%d", &size);

    // Inicializa a árvore quaternária com os limites especificados
    Quad_tree *root = initialize_tree(0, size, 0, size);
    int running = 1;  // Variável de controle para manter o loop rodando => Condição de parada explicita do enunciado

    while (running) {
        char command[2];
        scanf("%s", command);

        // Inserção
        if (strcmp(command, "i") == 0) {
            int x, y;
            char city_name[MAX_LEN_CITY];
            scanf("%d %d %s", &x, &y, city_name);
            insert_city(root, x, y, city_name);
        }

        // Busca por ponto
        else if (strcmp(command, "b") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            CityInfo *city = search_city(root, x, y);

            if (city != NULL) {
                printf("Cidade %s encontrada no ponto (%d,%d).\n", city->name, city->x, city->y);
            } else {
                printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", x, y);
            }
        }

        // Busca por região
        else if (strcmp(command, "o") == 0) {
            int x, y, r;
            scanf("%d %d %d", &x, &y, &r);
            printf("Cidades a distancia %d de (%d,%d): ", r, x, y);
            search_region(root, x, y, r);
            printf("\n");
        }

        // Remoção
        else if (strcmp(command, "r") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            remove_city(root, x, y);
        }

        // Impressão
        else if (strcmp(command, "p") == 0) {
            printf("Árvore:\n");
            int depth = 1;
            print_tree(root, depth);
        }

        // Encerrar o sistema
        else if (strcmp(command, "s") == 0) {
            printf("Sistema encerrado.\n");
            free_quad_tree(root);
            running = 0;  // Define running como 0 para sair do loop
        }
    }

    return 0;
}