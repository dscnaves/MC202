#include <stdio.h>

int read_number_digits(long long n) {
    long long num_aux = n;  // Número auxiliar
    int digits = 0;         // Contador de dígitos

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

long long build_inverse_number(long long n, int digitos) {
    // Essa função construi com os algarismos invertidos em relação ao original
    long long num_aux = n;
    long long num_inverse = 0;

    for (int i = 0; i < digitos; i++) { // Iteração de "quantidade de dígitos" vezes
        int resto = num_aux % 10;
        num_inverse = num_inverse * 10 + resto;
        num_aux = num_aux / 10;
    }

    return num_inverse;
}

void is_capicua(long long n, long long num_inverse) {
    // Função que verificará se um número é capicua e imprimirá o resultado a depender da verificação
    if (num_inverse == n) {
        printf("%lld eh capicua\n", n);
    } else {
        printf("%lld nao eh capicua\n", n);
    }
}

int main() {
    // Função principal
    int casos_teste;
    scanf("%d", &casos_teste);

    for (int x = 0; x < casos_teste; x++) {
        long long n;
        scanf("%lld", &n);

        int digitos = read_number_digits(n);
        long long numero_inverso = build_inverse_number(n, digitos);
        is_capicua(n, numero_inverso);
    }

    return 0;
}