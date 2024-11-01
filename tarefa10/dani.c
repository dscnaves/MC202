#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_SIZE_VARIATIONS 1000
#define MAX_SIZE_WORD 26

// Função para gerar todas as variações de `term` e armazená-las em `variations`
void generate_variations(const char *term, char variations[][MAX_SIZE_WORD], int *variation_count) {
    int term_len = strlen(term);
    *variation_count = 0;

    // Gerando variações com inserção de caracteres
    for (int i = 0; i <= term_len; i++) { // Posições de inserção
        for (char c = 'a'; c <= 'z'; c++) { // Cada caractere do alfabeto
            char new_word[MAX_SIZE_WORD] = {0};
            strncpy(new_word, term, i); // Copia os primeiros i caracteres de term
            new_word[i] = c; // Insere o novo caractere
            strncpy(new_word + i + 1, term + i, term_len - i); // Copia o restante de term
            strncpy(variations[*variation_count], new_word, MAX_SIZE_WORD);
            (*variation_count)++;
        }
    }

    // Gerando variações com remoção de caracteres
    for (int i = 0; i < term_len; i++) {
        char new_word[MAX_SIZE_WORD] = {0};
        strncpy(new_word, term, i); // Copia os primeiros i caracteres de term
        strncpy(new_word + i, term + i + 1, term_len - i - 1); // Pula o caractere em i e copia o restante
        strncpy(variations[*variation_count], new_word, MAX_SIZE_WORD);
        (*variation_count)++;
    }
}
int main() {
    char term[MAX_SIZE_WORD];
    scanf("%s", term);

    char variations[MAX_SIZE_VARIATIONS][MAX_SIZE_WORD];
    int variation_count = 0;

    generate_variations(term, variations, &variation_count);

    printf("Total de variações geradas: %d\n", variation_count);
    for (int i = 0; i < variation_count; i++) {
        printf("%s\n", variations[i]);
    }

    return 0;
}
