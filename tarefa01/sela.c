#include <stdio.h>

void modifica_matriz_sela(int matriz_sela[100][100], int l, int c){
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            scanf("%d", &matriz_sela[i][j]);
        }
    }
}

int is_min_line(int x, int y, int l, int c, int matriz_sela[100][100]){
    for(int j = 0; j < c; j++){
        if(matriz_sela[x][y] > matriz_sela[x][j]){
            return 0;
            break;
        }
    }
    return 1;
}

int is_max_column(int x, int y, int l, int c, int matriz_sela[100][100]){
    for(int i = 0; i < l; i++){
        if(matriz_sela[x][y] < matriz_sela[i][y]){
            return 0;
            break;
        }
    }
    return 1;
}

int main(){
    int ponto_sela_found = 0;

    int x_ponto_sela;
    int y_ponto_sela;

    int l; //Número de linhas
    int c; //Número de colunas
    scanf("%d %d",&l,&c);

    //Criando a matriz:
    int matriz_sela[100][100];

    //Inicializando a matrizcom -1:
    for(int i = 0; i<100; i++){
        for(int j = 0; j<100; j++){
            matriz_sela[i][j] = -1;
        }
    }

    //Modificar a matriz para o problema proposto:
    modifica_matriz_sela(matriz_sela, l, c);


    //Achar o ponto de sela:
    for(int x = 0; x<l; x++){ //Para da elemento da matriz
        for(int y = 0; y<c; y++){
            // Verificar se é mínimo na linha:
            if (is_min_line(x,y,l,c,matriz_sela) == 1){
                //Verificar se é máximo na coluna:
                if (is_max_column(x,y,l,c,matriz_sela) == 1){
                    ponto_sela_found++;
                    x_ponto_sela = x;
                    y_ponto_sela = y;
                    
                }
            }
        }
    }

    //Se não acharmos o ponto de sela ou acharmos mais de um ponto min linha e max coluna:
    if (ponto_sela_found != 1){
        printf("nao existe ponto de sela");
    }
    else{
        printf("(%d, %d) eh ponto de sela com valor %d", x_ponto_sela,y_ponto_sela,matriz_sela[x_ponto_sela][y_ponto_sela]);
    }

    return 0;
}