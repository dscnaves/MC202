#include <stdio.h>

void vetor_menos_um(int * vetor){
    for(int k = 0; k<1000; k++){
        vetor[k] = -1;
    }
}

void modificar_seq_parcial(int * vetor_original, int * vetor_parcial, int n){
    for(int j = 1; j<(n);j++){
        vetor_parcial[j] = vetor_parcial[j-1] + vetor_original[j];
    }
}

void modificar_seq_parcial_inversa(int * vetor_parcial_, int * vetor_inverso_parcial_, int n){
    for(int j = 0; j<n; j ++){
        vetor_inverso_parcial_[j] = vetor_parcial_[n - 1 - j];
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int vetor_original[1000];
    int vetor_parcial[1000];
    int vetor_inverso_parcial[1000];

    vetor_menos_um(vetor_original);
    vetor_menos_um(vetor_parcial);
    vetor_menos_um(vetor_inverso_parcial);

    for(int i = 0; i<n; i++){
        scanf("%d ", &vetor_original[i]);
    }

    vetor_parcial[0] = vetor_original[0];

    modificar_seq_parcial(vetor_original, vetor_parcial, n);

    modificar_seq_parcial_inversa(vetor_parcial, vetor_inverso_parcial, n);
    
    for(int i = 0; i < n; i++) {
        printf("%d ", vetor_inverso_parcial[i]);
    }
    
    return 0;
}