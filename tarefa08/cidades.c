#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_CITY 11

typedef struct City {
    int x,y;
    char name[MAX_LEN_CITY];
} City;

typedef struct Quad_tree{
    int x_min, x_max, y_min, y_max;
    struct Quad_tree * children[4];
    City * city;
} Quad_tree;

Quad_tree * initialize_tree(int x_min, int x_max, int y_min, int y_max){
    Quad_tree * p_node = malloc(sizeof(Quad_tree));
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

void initialize_city(Quad_tree * node, int x, int y, char city_name[MAX_LEN_CITY]){
    //node será o nó da árvore onde será inserido a cidade
    node->city = malloc(sizeof(City));
    if (node->city == NULL) {
        printf("Erro ao alocar memória para a cidade.\n");
        exit(1);
    }
    node->city->x = x;
    node->city->y = y;
    strncpy(node->city->name, city_name, MAX_LEN_CITY); //Para evitar erros como estouro de buffer
}

int is_no_interno(Quad_tree * node){
    //Se um nó é interno então ele possui pelo menos 1 filho
    if (node->children[0] != NULL || node->children[1] != NULL || node->children[2] != NULL || node->children[3] != NULL) return 1;
    return 0;
}

int is_no_vazio (Quad_tree * node){
    //Se um nó é vazio: ele é folha (todos os filhos são NULL) e ele não contém uma cidade nele
    if (node->city == NULL && node->children[0] == NULL && node->children[1] == NULL &&
        node->children[2] == NULL && node->children[3] == NULL) return 1;
    return 0;
}

int which_quadrant(int x, int y, int mid_x, int mid_y){
    if (x < mid_x && y >= mid_y) return 0; // NO
    if (x >= mid_x && y >= mid_y) return 1; // NE
    if (x < mid_x && y < mid_y) return 2; // SO
    return 3; // SE
}

void insert_city(Quad_tree * node, int x, int y, char * p_city_name) {
    if (is_no_vazio(node)){
        initialize_city(node, x,y, p_city_name);
        printf("Cidade %s inserida no ponto (%d,%d).\n", p_city_name, x, y);
    }

    //Se no nó for ocupado (Já contém uma cidade) ou interno (Possui filhos)
    else{
        //Determinando qual quadrante a cidade deve ser inserida
        int mid_x = (node->x_min + node->x_max) / 2; //Dividir o espaço atual em quatro quadrantes que serão os quadrantes da subárvore que iremos criar se for uma folha ocupada
        int mid_y = (node->y_min + node->y_max) / 2;
        int quadrant = which_quadrant(x,y,mid_x, mid_y); //Analisar em qual quadrante da subárvore a cidade a ser inserida pertence

        //Se não existe ainda o quadrante para inserir a árvore OU SEJA chegamos a uma folha ocupada => Expandimos a árvore na direção do quadrante que iremos adicionar a árvore
        if (node->children[quadrant] == NULL){            
            if (quadrant == 0) node->children[quadrant] = initialize_tree(node->x_min, mid_x, mid_y, node->y_max);
            else if (quadrant == 1) node->children[quadrant] = initialize_tree(mid_x, node->x_max, mid_y, node->y_max);
            else if (quadrant == 2) node->children[quadrant] = initialize_tree(node->x_min, mid_x, node->y_min, mid_y);
            else node->children[quadrant] = initialize_tree(mid_x, node->x_max, node->y_min, mid_y);
        }

        //Se o nó for interno => Continue percorrendo a árvore na direção do quadrante que devemos inserir
        insert_city(node->children[quadrant], x, y, p_city_name);
    }
}

City * search_city(Quad_tree * node, int x ,int y){
    //Caso base: Encontrou a cidade (coordenadas bateiram) => retorna o endereço da cidade
    if (node->city != NULL && node->city->x == x && node->city->y == y){
        return node->city;
    }

    //Se não encontrou procure no próximo quadrande onde a cidade pode estar
    int mid_x = (node->x_min + node->x_max) / 2;
    int mid_y = (node->y_min + node->y_max) / 2;
    int quadrant = which_quadrant(x, y, mid_x, mid_y);

    if (node->children[quadrant] != NULL){//Se o quadrante existe, procure dentro dele
        return search_city(node->children[quadrant], x, y);
    }

    return NULL; //Fomos até o final da árvore e não foi encontrado
}



void print_tree(Quad_tree *node, int depth){
    if (node == NULL) return;  // Caso base: nó é nulo

    //Caso de parada: Se o nó contém uma cidade, imprime a cidade
    if (node->city != NULL) {
        printf("  %*sCidade %s (%d,%d)\n", depth * 2, "", node->city->name, node->city->x, node->city->y);
    }

    //Se o nó for um nó interno 
    else if (is_no_interno(node) == 1) {
        printf("  %*sI\n", depth * 2, "");

        for (int i = 0; i < 4; i++) {
            if (node->children[i] != NULL) {
                print_tree(node->children[i], depth + 1);
            }
        }
    } 
    
    else {
        printf("  %*sV\n", depth * 2, "");
    }
}

int main(){
    int size; //lado quadrado que representa o mapa
    scanf("%d",&size);

    //Inicializando a árvore
    Quad_tree * root = initialize_tree(0,size,0,size);

    char command[1];
    while (1) {
        scanf("%s", command);

        //Inserção
        if (strcmp(command, "i") == 0){
            int x, y;
            char city_name[MAX_LEN_CITY];
            scanf("%d %d %s", &x, &y, city_name);

            insert_city(root,x,y,city_name);
        }

        //Busca por ponto
        else if (strcmp(command, "b") == 0){
            /* code */
        }

        //Busca por região
        else if (strcmp(command, "o") == 0){
            /* code */
        }

        //Remoção
        else if (strcmp(command, "r") == 0){
            /* code */
        }

        //Impressão
        else if (strcmp(command, "p") == 0) {
            printf("Árvore:\n");
            int depth = 1;
            print_tree(root, depth);
        }
        //Sair
        else if (strcmp(command, "s") == 0){
            printf("Sistema encerrado.\n");
            break;
        } 
    }
    return 0;
}