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

void zera_vetor(p_vector v) {
    for (int i = 0; i < v->alocado; i++) {
        v->dados[i] = 0;
    }
}

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

void bat_alloc(int N, p_vector v, int *idx_alocado) {
    // Verifica se consegue alocar sem dobrar a memória
    if (alocar_sem_dobrar_eh_possivel(v, N, idx_alocado)) {
        // Imprime o endereço de início da alocação
        printf("%d\n", *idx_alocado);
    } else {
        // Não temos memória suficiente, então dobramos a memória e tentamos de novo
        dobra_memoria(v);
        alocar_sem_dobrar_eh_possivel(v, N, idx_alocado);
        printf("%d\n", *idx_alocado);
    }

    // Atualiza a quantidade de memória utilizada
    v->utilizados = 0;
    for (int i = 0; i < v->alocado; i++) {
        if (v->dados[i] != 0) {
            v->utilizados++;
        }
    }
}

void bat_free(int endereco, p_vector v) {
    int tamanho = v->dados[endereco];
    for (int i = 0; i <= tamanho; i++) {
        v->dados[endereco + i] = 0;
    }

    // Atualiza a quantidade de memória utilizada
    v->utilizados = 0;
    for (int i = 0; i < v->alocado; i++) {
        if (v->dados[i] != 0) {
            v->utilizados++;
        }
    }

    // Verifica se pode reduzir o tamanho da memória
    int nao_utilizados_final = v->alocado - v->utilizados;
    if (v->alocado > MIN_VETOR && nao_utilizados_final >= 3 * v->alocado / 4) {
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
}

void bat_print(int endereco, p_vector v) {
    int tamanho = v->dados[endereco];
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", v->dados[endereco + 1 + i]);
    }
    printf("\n");
}

void bat_uso(p_vector v) {
    printf("%d de %d\n", v->utilizados, v->alocado);
}

int main() {
    int n; // Número de operações a serem realizadas
    scanf("%d", &n);

    // Inicializando a bat-memória
    p_vector v = malloc(sizeof(Vector));
    v->dados = malloc(MIN_VETOR * sizeof(int));
    v->alocado = MIN_VETOR;
    v->utilizados = 0;
    zera_vetor(v);

    // Realizando comandos
    for (int x = 0; x < n; x++) {
        char command[10];
        scanf("%s", command);

        if (strcmp(command, "bat-alloc") == 0) {
            int N; // Qtde de números a serem alocados
            scanf("%d", &N);
            int idx_alocado = 0; // Onde foi alocado o novo vetor?
            bat_alloc(N, v, &idx_alocado);
        }

        else if (strcmp(command, "bat-free") == 0) {
            int endereco; // Endereço de memória a ser liberado
            scanf("%d", &endereco);
            bat_free(endereco, v);
        }

        else if (strcmp(command, "bat-print") == 0) {
            int endereco; // Endereço de memória a ser impresso
            scanf("%d", &endereco);
            bat_print(endereco, v);
        }

        else if (strcmp(command, "bat-uso") == 0) {
            bat_uso(v);
        }
    }

    // Liberando a memória no final
    free(v->dados);
    free(v);

    return 0;
}
