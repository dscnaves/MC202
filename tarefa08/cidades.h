#ifndef CIDADES_H
#define CIDADES_H

#define MAX_LEN_CITY 11

// Estrutura para armazenar dados da cidade
typedef struct City {
    int x, y;
    char name[MAX_LEN_CITY];
} City;

// Estrutura para o nó da árvore quaternária
typedef struct Quad_tree {
    int x_min, x_max, y_min, y_max;
    struct Quad_tree *children[4];
    City *city;
} Quad_tree;

//Estrutura contém apenas as informações da cidade, sem a referência ao nó => Consertar problema de segurança
typedef struct CityInfo {
    int x, y;
    char name[MAX_LEN_CITY];
} CityInfo;


// Funções de inicialização e liberação
Quad_tree *initialize_tree(int x_min, int x_max, int y_min, int y_max);
void initialize_city(Quad_tree *node, int x, int y, char city_name[MAX_LEN_CITY]);
void free_quad_tree(Quad_tree *node);

// Funções de verificação de nós
int is_no_interno(Quad_tree *node);
int is_no_vazio(Quad_tree *node);
int which_quadrant(int x, int y, int mid_x, int mid_y);

// Operações de cidade
void insert_city(Quad_tree *node, int x, int y, char *p_city_name);
CityInfo *search_city(Quad_tree *node, int x, int y);
void remove_city(Quad_tree *node, int x, int y);
void search_region(Quad_tree *node, int x, int y, int r);

// Função de impressão da árvore
void print_tree(Quad_tree *node, int depth);

#endif
