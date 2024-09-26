#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Posicao{
    int x;
    int y;
} Posicao;

typedef struct No{
    int x;
    int y;
    struct No * prox;
    struct No * ant;
} No;

void alocar_no(No ** p_no, int x, int y){
    *p_no = malloc(sizeof(No));
    (*p_no)->prox = NULL;
    (*p_no)->ant = NULL;
    (*p_no)->x = x;
    (*p_no)->y = y;
}

char ** alocar_matriz(int m, int n){
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

void movimenta_cobra(char ** matriz, No * cabeca, No * cauda, Posicao * prox_pos){

    No * p_atual = cauda;

    // Atualiza todas as posições da cobra          
    while (p_atual->prox != NULL){
        p_atual->x = p_atual->prox->x;
        p_atual->y = p_atual->prox->y;
        p_atual = p_atual->prox;             
    }

    // Atualiza a posição da cabeça
    cabeca->x = prox_pos->x;
    cabeca->y = prox_pos->y;

    //Atualizando a matriz após a movimentação
    matriz[cauda->x][cauda->y] = '_'; // Remove a cauda antiga
    matriz[cabeca->x][cabeca->y] = '#'; // Coloca a nova cabeça
}

int main(){
    int m, n; //Dimensões da matriz
    scanf("MATRIZ %d %d", &m, &n);
    
    //Alocando a matriz
    char ** matriz = alocar_matriz(m,n);

    //Atribuindo '_' a cada posição
    inicializar_matriz(m,n,matriz);
    imprimir(m,n,matriz);

    Posicao inicial_pos;
    scanf("COBRA %d %d", &inicial_pos.x, &inicial_pos.y);

    //Inicializando a cobra
    No  * cabeca;
    alocar_no(&cabeca,inicial_pos.x,inicial_pos.y);  
    No * cauda;
    
    
    //Atualizar matriz
    matriz[inicial_pos.x][inicial_pos.y] = '#';

    // Variáveis de controle
    int total_posicoes = m * n;
    int tamanho_cobra = 1;

    //Jogo    
    while(1){
        //Lendo comando
        char command[7];
        scanf("%s", command);

        //Se o comando for fruta
        if (strcmp(command,"FRUTA") == 0) {
            Posicao * fruta;
            scanf("%d %d", &fruta->x, &fruta->y);
            matriz[fruta->x][fruta->y] = '*'; //Inserir fruta
            imprimir(m,n,matriz);
        }

        //Se o comando for um movimento
        else {
            Posicao prox_pos;
            prox_pos.x = cabeca->x;
            prox_pos.y = cabeca->y;

            //Para cima
            if (command =='w') {
                if (prox_pos->y == n){ //Se a cobra ultrapassar as extremidades
                    prox_pos->y = 0;
                }
                else {
                    prox_pos->y = cabeca->y + 1;
                }


                if (matriz[prox_pos->x][prox_pos->y] == '_'){
                    movimenta_cobra(matriz, cabeca, cauda, prox_pos);
                }
                else if (matriz[prox_pos->x][prox_pos->y] == '*'){
                    //Alocando dinamicamente novo nó
                    No * p_novo_no = malloc(sizeof(Posicao));
                    alocar_no(&p_novo_no,prox_pos->x,prox_pos->y);

                    p_novo_no->ant = cabeca;
                    p_novo_no->prox = NULL;
                    cabeca->prox = p_novo_no;
                    
                    cabeca = p_novo_no;
                }
            }
            //Para baixo
            else if (command == 's'){
            }

            //Para direita
            else if (command == 'd'){
            }

            //Para esquerda
            else if (command == 'a'){
            }

        imprimir(m,n,matriz);
        }
    }

    return 0;
}