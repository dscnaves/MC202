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
    City * city;
} Quad_tree;

Quad_tree * initialize_tree(int x_min, int x_max, int y_min, int y_max){
    Quad_tree * p_root = malloc(sizeof(Quad_tree *));
    p_root->x_min = x_min;
    p_root->x_max = x_max;
    p_root->y_min = y_min;
    p_root->y_max = y_max;
    City * p_city = malloc(sizeof(City *));
    return p_root;
}

int is_no_interno(Quad_tree * root){
    //Se um nó é interno então ele possui pelo menos 1 filho
    if (root->children[0] != NULL || root->children[1] != NULL || root->children[2] != NULL || root->children[3] != NULL) return 1;
    return 0;
}

void print_tree(Quad_tree *root, int depth){

    //Caso de parada: Se o nó contém uma cidade, imprime a cidade
    if (root->city != NULL) {
        printf("  %*sCidade %s (%d,%d)\n", depth * 2, "", root->city->name, root->city->x, root->city->y);
    }

    //Se o nó for um nó interno 
    else if (is_no_interno(root) == 1) {
        printf("  %*sI\n", depth * 2, "");

        for (int i = 0; i < 4; i++) {
            if (root->children[i] != NULL) {
                print_tree(root->children[i], depth + 1);
            } else {
                printf("  %*sV\n", (depth + 1) * 2, "");
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
            printf("Árvore:\n");
            
        }     
    }
    return 0;
}