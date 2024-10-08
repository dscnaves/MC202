#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cobra.h"

void alocar_no(No **p_no, int x, int y) {
    *p_no = malloc(sizeof(No));
    (*p_no)->prox = NULL;
    (*p_no)->ant = NULL;
    (*p_no)->x = x;
    (*p_no)->y = y;
}

char **alocar_matriz(int m, int n) {
    char **pp_matriz = malloc(m * sizeof(char *));
    for (int i = 0; i < m; i++) {
        pp_matriz[i] = malloc(n * sizeof(char));
    }
    return pp_matriz;
}

void inicializar_matriz(int m, int n, char **p_matriz) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            p_matriz[i][j] = '_';
        }
    }
}

void imprimir(int m, int n, char **matriz) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void movimenta_cobra(char **matriz, No *cabeca, No *cauda, Posicao *prox_pos) {
    No *p_atual = cauda;

    // Atualiza todas as posições da cobra
    while (p_atual->prox != NULL) {
        p_atual->x = p_atual->prox->x;
        p_atual->y = p_atual->prox->y;
        p_atual = p_atual->prox;
    }

    // Atualiza a posição da cabeça
    cabeca->x = prox_pos->x;
    cabeca->y = prox_pos->y;

    // Atualizando a matriz após a movimentação
    matriz[cauda->x][cauda->y] = '_';  // Remove a cauda antiga
    matriz[cabeca->x][cabeca->y] = '#';  // Coloca a nova cabeça
}

int verificar_colisao(char **matriz, int x, int y) {
    if (matriz[x][y] == '#') {
        printf("GAME OVER\n");
        return 1;
    }
    return 0;
}

void liberar_jogo(char **matriz, No *cauda, int m) {
    for (int i = 0; i < m; i++) {
        free(matriz[i]);
    }
    free(matriz);

    No *p_atual = cauda;
    while (p_atual != NULL) {
        No *prox = p_atual->prox;
        free(p_atual);
        p_atual = prox;
    }
}

int main() {
    int m, n;  // Dimensões da matriz
    char command[7];
    scanf("%s", command);
    scanf("%d %d", &m, &n);

    // Alocando a matriz
    char **matriz = alocar_matriz(m, n);

    // Atribuindo '_' a cada posição
    inicializar_matriz(m, n, matriz);

    Posicao inicial_pos;
    scanf("%s", command);
    scanf("%d %d", &inicial_pos.x, &inicial_pos.y);

    // Inicializando a cobra
    No *cabeca;
    alocar_no(&cabeca, inicial_pos.x, inicial_pos.y);
    // No início pos cauda == cabeca
    No *cauda;
    alocar_no(&cauda, cabeca->x, cabeca->y);
    cauda->prox = cabeca;
    cabeca->ant = cauda;

    // Atualizar matriz
    matriz[inicial_pos.x][inicial_pos.y] = '#';

    // Variáveis de controle
    int total_posicoes = m * n;
    int tamanho_cobra = 1;

    // Jogo
    while (1) {
        // Lendo comando
        scanf("%6s", command);

        // Se o comando for fruta
        if (strcmp(command, "FRUTA") == 0) {
            Posicao fruta;
            scanf("%d %d", &fruta.x, &fruta.y);
            matriz[fruta.x][fruta.y] = '*';  // Inserir fruta
            imprimir(m, n, matriz);
        }

        // Se o comando for um movimento
        else {
            Posicao prox_pos;
            prox_pos.x = cabeca->x;
            prox_pos.y = cabeca->y;

            // Para cima
            if (strcmp(command, "w") == 0) {
                prox_pos.x = (cabeca->x - 1 + m) % m;
            }
            // Para baixo
            else if (strcmp(command, "s") == 0) {
                prox_pos.x = (cabeca->x + 1) % m;
            }
            // Para direita
            else if (strcmp(command, "d") == 0) {
                prox_pos.y = (cabeca->y + 1) % n;
            }
            // Para esquerda
            else if (strcmp(command, "a") == 0) {
                prox_pos.y = (cabeca->y - 1 + n) % n;
            }

            // Verificar colisão com o próprio corpo
            int colide = verificar_colisao(matriz, prox_pos.x, prox_pos.y);
            if (colide == 1) {
                liberar_jogo(matriz, cauda, m);
                break;
            }

            // Se a cobra encontrar uma fruta
            if (matriz[prox_pos.x][prox_pos.y] == '*') {
                No *p_novo_no;
                alocar_no(&p_novo_no, prox_pos.x, prox_pos.y);

                p_novo_no->ant = cabeca;
                cabeca->prox = p_novo_no;
                cabeca = p_novo_no;

                // Atualizar matriz
                matriz[prox_pos.x][prox_pos.y] = '#';
                tamanho_cobra++;

                if (tamanho_cobra == total_posicoes) {
                    imprimir(m, n, matriz);
                    printf("YOU WIN\n");
                    liberar_jogo(matriz, cauda, m);
                    break;
                }
            }

            // Se a cobra encontrar um espaço '_'
            else {
                movimenta_cobra(matriz, cabeca, cauda, &prox_pos);
            }
            imprimir(m, n, matriz);
        }
    }

    return 0;
}
