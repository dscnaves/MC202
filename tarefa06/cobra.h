#ifndef COBRA_H
#define COBRA_H

typedef struct Posicao {
    int x;
    int y;
} Posicao;

typedef struct No {
    int x;
    int y;
    struct No *prox;
    struct No *ant;
} No;

// Funções relacionadas à cobra
void alocar_no(No **p_no, int x, int y);
char **alocar_matriz(int m, int n);
void inicializar_matriz(int m, int n, char **p_matriz);
void imprimir(int m, int n, char **matriz);
void movimenta_cobra(char **matriz, No *cabeca, No *cauda, Posicao *prox_pos);
int verificar_colisao(char **matriz, int x, int y);
void liberar_jogo(char **matriz, No *cauda, int m);

#endif // COBRA_H
