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
    struct Quad_tree * children[4]; //1: 1° quadrante NE, 2: 2° quadrante NO, 3: 3° quadrante SO, 4: 4° quadrante SE
    City city;
} Quad_tree;

Quad_tree * initialize_tree(int x_min, int x_max, int y_min, int y_max){
    Quad_tree * p_root = malloc(sizeof(Quad_tree *));
    p_root->x_min = x_min;
    p_root->x_max = x_max;
    p_root->y_min = y_min;
    p_root->y_max = y_max;
    City * p_city = malloc(sizeof(City *));
}



int main(){
    int w; //lado quadrado que representa o mapa
    scanf("%d",&w);

    //Inicializando a árvore
    initialize_tree(0,w,0,w);

    char command[1];
    while (1) {
        scanf("%s", command);

        //Inserção
        if (strcmp(command, "i") == 0){
            /* code */
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
            /* code */
        }     
    }
    return 0;
}