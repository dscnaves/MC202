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

#include <stdio.h>

int read_number_digits(int n) {
    int num_aux = n;  // Número auxiliar
    int digits = 0;   // Contador de dígitos

    // Se n for zero, o número de dígitos é 1
    if (n == 0) {
        return 1;
    }

    // Conta o número de dígitos
    while (num_aux != 0) {
        num_aux = num_aux / 10;
        digits++;
    }

    return digits;
}

int build_inverse_number(int n,int digitos){
    // Essa função construi com os algarismos invertidos em relação ao original
    int num_aux = n;
    int num_inverse = 0;

    for(int i = 0; i < digitos; i++){ //Iteração de "quantidade de digitos" vezes
        int resto = num_aux % 10;
        num_inverse = num_inverse*10 + resto;

        num_aux = num_aux/10;
    }
    return num_inverse;
}

void is_capicua(int n, int num_inverse){
    //Função que verificará se um número é capicua e imprimerá o resultado a depender da verificação
    if(num_inverse==n){
        printf("%d eh capicua\n", n);
    }
    else{
        printf("%d nao eh capicua\n", n);
    }
}

int main() {
    //Função principal
    int casos_teste;
    scanf("%d", &casos_teste);

    for(int x = 0; x< casos_teste; x++){
        int n;
        scanf("%d",&n);

        int digitos = read_number_digits(n);
        
        int numero_inverso = build_inverse_number(n,digitos);
        
        is_capicua(n, numero_inverso);
    }

    return 0;
}