#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Inicializa a árvore quaternária com os limites especificados
Quad_tree* initialize_tree(int x_min, int x_max, int y_min, int y_max) {
    Quad_tree *p_node = malloc(sizeof(Quad_tree));
    if (p_node == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    p_node->x_min = x_min;
    p_node->x_max = x_max;
    p_node->y_min = y_min;
    p_node->y_max = y_max;
    for (int i = 0; i < 4; i++) {
        p_node->children[i] = NULL;
    }
    p_node->city = NULL;
    return p_node;
}

// Inicializa uma cidade em um nó da árvore quaternária
void initialize_city(Quad_tree *node, int x, int y, char city_name[MAX_LEN_CITY]) {
    node->city = malloc(sizeof(City));
    if (node->city == NULL) {
        printf("Erro ao alocar memória para a cidade.\n");
        exit(1);
    }
    node->city->x = x;
    node->city->y = y;
    strncpy(node->city->name, city_name, MAX_LEN_CITY);
}

// Verifica se um nó é interno, ou seja, possui pelo menos um filho
int is_no_interno(Quad_tree *node) {
    for (int i = 0; i < 4; i++) {
        if (node->children[i] != NULL) return 1;
    }
    return 0;
}

// Verifica se um nó é vazio, ou seja, é uma folha sem cidade
int is_no_vazio(Quad_tree *node) {
    if (node->city == NULL && !is_no_interno(node)) return 1;
    return 0;
}

// Determina o quadrante de um ponto com base nas coordenadas e limites médios
int which_quadrant(int x, int y, int mid_x, int mid_y) {
    if (x < mid_x && y >= mid_y) return 0;
    if (x >= mid_x && y >= mid_y) return 1;
    if (x < mid_x && y < mid_y) return 2;
    return 3;
}

// Insere uma cidade em um nó da árvore, expandindo a árvore conforme necessário
void insert_city(Quad_tree *node, int x, int y, char *city_name) {
    if (is_no_vazio(node)) {
        initialize_city(node, x, y, city_name);
        printf("Cidade %s inserida no ponto (%d,%d).\n", city_name, x, y);
    } else {
        int mid_x = (node->x_min + node->x_max) / 2;
        int mid_y = (node->y_min + node->y_max) / 2;
        int quadrant = which_quadrant(x, y, mid_x, mid_y);

        if (node->children[quadrant] == NULL) {
            if (quadrant == 0) node->children[quadrant] = initialize_tree(node->x_min, mid_x, mid_y, node->y_max);
            else if (quadrant == 1) node->children[quadrant] = initialize_tree(mid_x, node->x_max, mid_y, node->y_max);
            else if (quadrant == 2) node->children[quadrant] = initialize_tree(node->x_min, mid_x, node->y_min, mid_y);
            else node->children[quadrant] = initialize_tree(mid_x, node->x_max, node->y_min, mid_y);
        }
        insert_city(node->children[quadrant], x, y, city_name);
    }
}

// Busca uma cidade pela posição e retorna informações da cidade, se encontrada
CityInfo* search_city(Quad_tree *node, int x, int y) {
    static CityInfo found_city;
    if (node->city != NULL && node->city->x == x && node->city->y == y) {
        found_city.x = node->city->x;
        found_city.y = node->city->y;
        strncpy(found_city.name, node->city->name, MAX_LEN_CITY);
        return &found_city;
    }
    int mid_x = (node->x_min + node->x_max) / 2;
    int mid_y = (node->y_min + node->y_max) / 2;
    int quadrant = which_quadrant(x, y, mid_x, mid_y);

    if (node->children[quadrant] != NULL) {
        return search_city(node->children[quadrant], x, y);
    }
    return NULL;
}

// Remove uma cidade do nó com as coordenadas especificadas
void remove_city(Quad_tree *node, int x, int y) {
    if (node->city != NULL && node->city->x == x && node->city->y == y) {
        printf("Cidade %s removida do ponto (%d,%d).\n", node->city->name, x, y);
        free(node->city);
        node->city = NULL;
    }
    int mid_x = (node->x_min + node->x_max) / 2;
    int mid_y = (node->y_min + node->y_max) / 2;
    int quadrant = which_quadrant(x, y, mid_x, mid_y);
    if (node->children[quadrant] != NULL) {
        remove_city(node->children[quadrant], x, y);
    }
}

// Busca por cidades dentro de uma região circular com centro (x, y) e raio r
void search_region(Quad_tree *node, int x, int y, int r) {
    if (node == NULL) return;
    if (node->city != NULL) {
        int dx = node->city->x - x;
        int dy = node->city->y - y;
        if ((dx * dx + dy * dy) <= r * r) {
            printf("%s ", node->city->name);
        }
    }
    for (int i = 0; i < 4; i++) {
        if (node->children[i] != NULL) {
            search_region(node->children[i], x, y, r);
        }
    }
}

// Imprime a estrutura da árvore quaternária em profundidade especificada
void print_tree(Quad_tree *node, int depth) {
    if (node == NULL) return;
    if (node->city != NULL) {
        printf("  %*sCidade %s (%d,%d)\n", depth * 2, "", node->city->name, node->city->x, node->city->y);
    } else if (is_no_interno(node)) {
        printf("  %*sI\n", depth * 2, "");
        for (int i = 0; i < 4; i++) {
            if (node->children[i] != NULL) {
                print_tree(node->children[i], depth + 1);
            }
        }
    } else {
        printf("  %*sV\n", depth * 2, "");
    }
}

// Libera a memória da árvore quaternária de forma recursiva
void free_quad_tree(Quad_tree *node) {
    if (node == NULL) return;
    for (int i = 0; i < 4; i++) {
        if (node->children[i] != NULL) {
            free_quad_tree(node->children[i]);
        }
    }
    if (node->city != NULL) {
        free(node->city);
    }
    free(node);
}
