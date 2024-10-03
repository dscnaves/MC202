#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_VETOR 8 // Tamanho mínimo do vetor

typedef struct {
    int *dados;
    int alocado;
    int utilizados;
} Vector;

typedef Vector *p_vector;

// Função que inicializa a bat-memória
void inicializa_bat_memoria(p_vector v) {
    v->dados = malloc(MIN_VETOR * sizeof(int));
    v->alocado = MIN_VETOR;
    v->utilizados = 0;
    for (int i = 0; i < v->alocado; i++) {
        v->dados[i] = 0;
    }
}

// Função para zerar o vetor (inicializar todos os dados com zero)
void zera_vetor(p_vector v) {
    for (int i = 0; i < v->alocado; i++) {
        v->dados[i] = 0;
    }
}

// Função que verifica se é possível alocar sem dobrar a memória
int alocar_sem_dobrar_eh_possivel(p_vector v, int N, int *idx_alocado) {
    int idx = 0;
    int vazio_tamanho = 0;

    while (idx < v->alocado) {
        if (v->dados[idx] != 0) { // Encontrou um bloco ocupado
            idx += v->dados[idx] + 1; // Pula o tamanho do bloco ocupado
            vazio_tamanho = 0; // Reseta o contador de espaço vazio
        } else {
            if (vazio_tamanho == 0) {
                *idx_alocado = idx;
            }
            vazio_tamanho++;
            
            if (vazio_tamanho == N + 1) {
                v->dados[*idx_alocado] = N; // Marca o tamanho no primeiro espaço vazio

                for (int i = 0; i < N; i++) {
                    scanf("%d", &v->dados[i + (*idx_alocado + 1)]);
                }

                return 1; // Alocação bem-sucedida
            }
            idx++;
        }
    }

    return 0; // Não foi possível alocar
}

// Função que dobra a memória
void dobra_memoria(p_vector v) {
    int *p_aux = v->dados;
    int novo_tamanho = 2 * v->alocado;

    v->dados = malloc(novo_tamanho * sizeof(int));

    // Copia os dados antigos
    for (int i = 0; i < v->alocado; i++) {
        v->dados[i] = p_aux[i];
    }

    // Inicializa novas posições com zero
    for (int i = v->alocado; i < novo_tamanho; i++) {
        v->dados[i] = 0;
    }

    v->alocado = novo_tamanho;
    free(p_aux);
}

// Função para alocar memória na bat-memória
void bat_alloc(int N, p_vector v, int *idx_alocado) {
    // Verifica se consegue alocar sem dobrar a memória
    if (alocar_sem_dobrar_eh_possivel(v, N, idx_alocado)) {
        printf("%d\n", *idx_alocado);
    } else {
        // Dobra a memória e tenta alocar novamente
        dobra_memoria(v);
        alocar_sem_dobrar_eh_possivel(v, N, idx_alocado);
        printf("%d\n", *idx_alocado);
    }

    // Atualiza a quantidade de memória utilizada
    v->utilizados += N + 1;
}

// Função para liberar memória na bat-memória
void bat_free(int endereco, p_vector v) {
    int tamanho = v->dados[endereco];
    for (int i = 0; i <= tamanho; i++) {
        v->dados[endereco + i] = 0;
    }

    // Atualiza a quantidade de memória utilizada
    v->utilizados -= tamanho + 1;

    int ocupacao_quarto_final = 0;
    do {
        // Verifica se pode reduzir o tamanho da memória
        ocupacao_quarto_final = 0;
        for (int i = v->alocado / 4; i < v->alocado; i++) {
            if (v->dados[i] != 0) {
                ocupacao_quarto_final++;
            }
        }

        if (v->alocado > MIN_VETOR && ocupacao_quarto_final == 0) {
            int *p_aux = v->dados;
            int novo_tamanho = v->alocado / 2;

            if (novo_tamanho < MIN_VETOR) novo_tamanho = MIN_VETOR;

            v->dados = malloc(novo_tamanho * sizeof(int));
            // Copia os dados antigos
            for (int i = 0; i < novo_tamanho; i++) {
                v->dados[i] = p_aux[i];
            }

            v->alocado = novo_tamanho;
            free(p_aux);
        }

    } while (ocupacao_quarto_final == 0);
}

// Função para imprimir a memória
void bat_print(int endereco, p_vector v) {
    int tamanho = v->dados[endereco];
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", v->dados[endereco + 1 + i]);
    }
    printf("\n");
}

// Função para verificar o uso da memória
void bat_uso(p_vector v) {
    printf("%d de %d\n", v->utilizados, v->alocado);
}

// Função principal que executa as operações
void executa_comandos(int n, p_vector v) {
    for (int x = 0; x < n; x++) {
        char command[10];
        scanf("%s", command);

        if (strcmp(command, "bat-alloc") == 0) {
            int N;
            scanf("%d", &N);
            int idx_alocado = 0;
            bat_alloc(N, v, &idx_alocado);
        } else if (strcmp(command, "bat-free") == 0) {
            int endereco;
            scanf("%d", &endereco);
            bat_free(endereco, v);
        } else if (strcmp(command, "bat-print") == 0) {
            int endereco;
            scanf("%d", &endereco);
            bat_print(endereco, v);
        } else if (strcmp(command, "bat-uso") == 0) {
            bat_uso(v);
        }
    }
}

int main() {
    int n; // Número de operações a serem realizadas
    scanf("%d", &n);

    // Inicializando a bat-memória
    p_vector v = malloc(sizeof(Vector));
    inicializa_bat_memoria(v);

    // Executando comandos
    executa_comandos(n, v);

    // Liberando a memória no final
    free(v->dados);
    free(v);

    return 0;
}
