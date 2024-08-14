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
        printf("%d eh capicua", n);
    }
    else{
        printf("%d nao eh capicua", n);
    }
}

int main() {
    //Função principal
    int n;
    scanf("%d",&n);

    int digitos = read_number_digits(n);
    
    int numero_inverso = build_inverse_number(n,digitos);
    
    is_capicua(n, numero_inverso);
    return 0;
}