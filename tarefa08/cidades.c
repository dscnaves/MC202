#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

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

CityInfo * search_city(Quad_tree *node, int x, int y) {
    // Aloca um espaço temporário para armazenar o resultado da busca
    static CityInfo found_city;  // Usando static para persistir o valor entre chamadas

    // Caso base: Encontrou a cidade com as coordenadas exatas
    if (node->city != NULL && node->city->x == x && node->city->y == y) {
        found_city.x = node->city->x;
        found_city.y = node->city->y;
        strncpy(found_city.name, node->city->name, MAX_LEN_CITY);
        return &found_city;
    }

    // Caso recursivo: Busca no quadrante apropriado
    int mid_x = (node->x_min + node->x_max) / 2;
    int mid_y = (node->y_min + node->y_max) / 2;
    int quadrant = which_quadrant(x, y, mid_x, mid_y);

    if (node->children[quadrant] != NULL) {
        return search_city(node->children[quadrant], x, y);
    }

    return NULL;  // Cidade não encontrada
}


void remove_city(Quad_tree *node, int x, int y){
    //Caso base: Chegamos a um nó folha ocupada e removemos a cidade
    if (node->city != NULL && node->city->x == x && node->city->y){
        printf("Cidade %s removida do ponto (%d,%d).\n", node->city->name,x,y);
        free(node->city);
        node->city = NULL;
    }

    //Se for um nó interno => Procuramos dentro do próximo quadrante o qual a cidade pode esta de acordo com seu valores de x,y
    int mid_x = (node->x_min + node->x_max) / 2;
    int mid_y = (node->y_min + node->y_max) / 2;
    int quadrant = which_quadrant(x, y, mid_x, mid_y); 

    if (node->children[quadrant] != NULL){
        remove_city(node->children[quadrant],x,y);
    }    
}

void search_region(Quad_tree *node, int x, int y, int r){
    if (node == NULL) return;

    //Nó folha ocupada
    // Se o nó contém uma cidade, verifica se está dentro da região
    if (node->city != NULL) {
        int dx = node->city->x - x;
        int dy = node->city->y - y;

        int distance_sq = dx * dx + dy * dy;

        if (distance_sq <= r * r) {
            printf("%s ", node->city->name);
        }
    }

    // Nó interno
    // Verificação dos quadrantes
    for (int i = 0; i < 4; i++) {
        //determinar se um quadrante (filho) da árvore quaternária pode potencialmente conter uma cidade dentro da região de busca

        //Calcular a distância mínima entre o círculo e um quadrante => Se o quadrante não pertence ao círculo => Descartar
        if (node->children[i] != NULL) {

            // Determina o ponto mais próximo ao centro da região de busca dentro do quadrante
            int closest_x = (x < node->children[i]->x_min) ? node->children[i]->x_min : ((x > node->children[i]->x_max) ? node->children[i]->x_max : x);
                        
            int closest_y = (y < node->children[i]->y_min) ? node->children[i]->y_min :
                            (y > node->children[i]->y_max) ? node->children[i]->y_max : y;

            // Calcula a distância do ponto mais próximo ao centro do círculo
            int dx = closest_x - x;
            int dy = closest_y - y;

            int distance_sq = dx * dx + dy * dy;
            
            //Se essa distância for menor ou igual ao raio do círculo => o ponto mais próximo está dentro do círculo => o quadrante pode conter cidades dentro da região de busca
            if (distance_sq <= r * r) {
                search_region(node->children[i], x, y, r);
            }
        }
    }
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

void free_quad_tree(Quad_tree * node){
    //Se for uma folha vazia
    if (node == NULL) return;  // Se o nó for NULL, não há nada para liberar

    //Se o nó for interno
    // Percorre todos os filhos (quadrantes) e libera recursivamente
    for (int i = 0; i < 4; i++) {
        if (node->children[i] != NULL) {
            free_quad_tree(node->children[i]);  // Libera o sub-nó do quadrante
        }
    }

    //Se for uma folha ocupada
    // Se há uma cidade neste nó, libere a memória da cidade
    if (node->city != NULL) {
        free(node->city);
    }

    // Finalmente, libera o próprio nó
    free(node);
}

int main() {
    int size;
    scanf("%d", &size);

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
            }
            else {
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