#include <stdio.h>

// Função para modificar a matriz com valores fornecidos pelo usuário
void modifica_matriz_sela(int matriz_sela[100][100], int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &matriz_sela[i][j]);
        }
    }
}

// Função para verificar se o elemento é o menor na linha
int is_min_line(int x, int y, int l, int c, int matriz_sela[100][100]) {
    for (int j = 0; j < c; j++) {
        if (matriz_sela[x][y] > matriz_sela[x][j]) {
            return 0; // Não é o mínimo
        }
    }
    return 1; // É o mínimo
}

// Função para verificar se o elemento é o maior na coluna
int is_max_column(int x, int y, int l, int c, int matriz_sela[100][100]) {
    for (int i = 0; i < l; i++) {
        if (matriz_sela[x][y] < matriz_sela[i][y]) {
            return 0; // Não é o máximo
        }
    }
    return 1; // É o máximo
}

int main() {
    int ponto_sela_found = 0;

    int l; // Número de linhas
    int c; // Número de colunas
    scanf("%d %d", &l, &c);

    // Criando a matriz
    int matriz_sela[100][100];
    
    // Inicializando a matriz com -1
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            matriz_sela[i][j] = -1;
        }
    }

    // Modificar a matriz com os valores fornecidos
    modifica_matriz_sela(matriz_sela, l, c);

    // Encontrar o ponto de sela
    for (int x = 0; x < l; x++) { // Para cada elemento da matriz
        for (int y = 0; y < c; y++) {
            // Verificar se é mínimo na linha
            if (is_min_line(x, y, l, c, matriz_sela) == 1) {
                // Verificar se é máximo na coluna
                if (is_max_column(x, y, l, c, matriz_sela) == 1) {
                    ponto_sela_found = 1;
                    printf("(%d,%d) eh ponto de sela com valor %d\n", x, y, matriz_sela[x][y]);
                }
            }
        }
    }

    // Se não encontrarmos o ponto de sela
    if (ponto_sela_found == 0) {
        printf("nao existe ponto de sela\n");
    }

    // Printar a matriz para verificar funções
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", matriz_sela[i][j]);
        }
        printf("\n");
    }

    return 0;
}