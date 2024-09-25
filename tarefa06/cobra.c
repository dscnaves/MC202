#include <stdio.h>
#include <stdlib.h>

#define LINHAS_MATRIZ  100
#define COLUNAS_MATRIZ 100

typedef struct Posicao{
    int x;
    int y;
} Posicao;

char ** alocar(int m, int n){
    char ** pp_matriz = malloc(m*sizeof(char *));
    for (int i = 0; i < m; i++){
        pp_matriz[i] = malloc(n*sizeof(char));
    }
    return pp_matriz;
}

void inicializar_matriz( int m, int n, char ** p_matriz){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            p_matriz[i][j]= '_';
        }
    }
}

void imprimir(int m, int n, char ** matriz){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int m, n; //Dimensões da matriz
    scanf("%d %d", &m, &n);

    //Posicao  * inicial_pos;
    //scanf("%d %d", &inicial_pos->x, &inicial_pos->y);

    char ** matriz = alocar(m,n);

    inicializar_matriz(m,n,matriz);

    imprimir(m,n,matriz);
    
    

    return 0;
}