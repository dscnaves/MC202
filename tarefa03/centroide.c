#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float *original_vector;
    float *max_min_normal_vector;
    float *euclides_normal_vector;
} Vector;

typedef struct {
    int d; // Dimensão dos vetores
    int n; // Número de vetores
    Vector *vetores; // Array dinâmico de vetores
} Matrix;

Matrix * create_matrix(int n, int d){
    Matrix *m = (Matrix*) malloc(sizeof(Matrix));
    if (m == NULL){
        printf("Erro de alocação de memória da matriz!\n");
        exit(1);
    }
    
    m->n = n;
    m->d = d;
    m->vetores = (Vector*) malloc(n * sizeof(Vector)); 
    if (m->vetores == NULL){
        printf("Erro de alocação da memória dos vetores!\n");
        free(m);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        m->vetores[i].original_vector = (float*) malloc(d * sizeof(float));
        m->vetores[i].max_min_normal_vector = (float*) malloc(d * sizeof(float));
        m->vetores[i].euclides_normal_vector = (float*) malloc(d * sizeof(float));
    }
    
    return m;
}

void free_matrix(Matrix * m){
    for (int i = 0; i< m->n; i++){
        free(m->vetores[i].original_vector);
        free(m->vetores[i].max_min_normal_vector);
        free(m->vetores[i].euclides_normal_vector);
    }
    free(m->vetores);
    free(m);
}

float modulus(Vector * v, int d){
    float soma_quadrados = 0;
    for (int i = 0; i < d; i++){
        soma_quadrados += pow(v->original_vector[i], 2);
    }
    return sqrt(soma_quadrados);
}

void max_min_normalize(Matrix * m, int idx, int d){
    float x_min = m->vetores[idx].original_vector[0];
    float x_max = m->vetores[idx].original_vector[0];

    for (int j = 1; j < d; j++){
        if (x_min > m->vetores[idx].original_vector[j]){
            x_min = m->vetores[idx].original_vector[j];
        }
        if (x_max < m->vetores[idx].original_vector[j]){
            x_max = m->vetores[idx].original_vector[j];
        }
    }

    for (int j = 0; j < d; j++) {
        if (x_max != x_min) {
            m->vetores[idx].max_min_normal_vector[j] = 2 * ((m->vetores[idx].original_vector[j] - x_min) / (x_max - x_min)) - 1;
        } else {
            m->vetores[idx].max_min_normal_vector[j] = 0;
        }
    }
}

void euclidean_normalize(Matrix *m, int idx, int d) {
    float mod = modulus(&m->vetores[idx], d);
    for (int j = 0; j < d; j++) {
        if (mod != 0) {
            m->vetores[idx].euclides_normal_vector[j] = m->vetores[idx].original_vector[j] / mod;
        } else {
            m->vetores[idx].euclides_normal_vector[j] = 0;
        }
    }
}

void calculate_centroid_none(Matrix *m, int d, int n) {
    printf("nenhum: ");
    for (int j = 0; j < d; j++) {
        float soma = 0;
        for (int i = 0; i < n; i++) {
            soma += m->vetores[i].original_vector[j];
        }
        printf("%.3f ", soma / n); // Ajusta para 3 casas decimais
    }
    printf("\n");
}

void calculate_centroid_max_min(Matrix *m, int d, int n) {
    printf("janela: ");
    for (int j = 0; j < d; j++) {
        float soma = 0;
        for (int i = 0; i < n; i++) {
            soma += m->vetores[i].max_min_normal_vector[j];
        }
        printf("%.3f ", soma / n); // Ajusta para 3 casas decimais
    }
    printf("\n");
}

void calculate_centroid_euclidean(Matrix *m, int d, int n) {
    printf("normal: ");
    for (int j = 0; j < d; j++) {
        float soma = 0;
        for (int i = 0; i < n; i++) {
            soma += m->vetores[i].euclides_normal_vector[j];
        }
        printf("%.3f ", soma / n); // Ajusta para 3 casas decimais
    }
    printf("\n");
}

int main(){
    int d, n;
    Matrix * m;
 
    scanf("%d %d", &d, &n);
    m = create_matrix(n, d);

    // Leitura dos dados
    for (int k = 0; k < n; k++) {
        for (int h = 0; h < d; h++) {
            scanf("%f", &m->vetores[k].original_vector[h]);
        }
    }

    // Cálculo do centroide sem normalização
    calculate_centroid_none(m, d, n);

    // Normalizando os vetores com Min-Max
    for (int k = 0; k < n; k++) {
        max_min_normalize(m, k, d);
    }
    calculate_centroid_max_min(m, d, n);

    // Normalizando os vetores pela norma Euclidiana
    for (int k = 0; k < n; k++) {
        euclidean_normalize(m, k, d);
    }
    calculate_centroid_euclidean(m, d, n);

    free_matrix(m);
    return 0;
}