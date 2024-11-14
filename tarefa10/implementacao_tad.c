#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface_tad.h"

// Inicializa a tabela hash, colocando todos os elementos como NULL
void initialize_HashTable(Node *hashtable[]) {
    for (int i = 0; i < MAX_SIZE_HASH_TABLE; i++) {
        hashtable[i] = NULL;  // Define cada posição da tabela hash como NULL
    }
}

// Cria um novo nó de tabela hash com uma palavra específica
Node *create_Node_HashTable(char word[]) {
    Node *New_HashNode = malloc(sizeof(Node));  // Aloca memória para o novo nó
    if (New_HashNode == NULL) {  // Verifica se a alocação foi bem-sucedida
        printf("Erro ao alocar memória no nó.\n");
        exit(1);
    }
    strncpy(New_HashNode->word, word, MAX_SIZE_WORD);  // Copia a palavra para o nó
    New_HashNode->word[MAX_SIZE_WORD - 1] = '\0';  // Garante o terminador nulo
    New_HashNode->p_next = NULL;  // Inicializa o ponteiro para o próximo nó como NULL
    return New_HashNode;
}

// Calcula o índice de hash para uma palavra usando uma função de dispersão
unsigned int hash(const char *p_word) {
    unsigned int hash = 0;
    while (*p_word) {
        hash = (hash * 31 + (*p_word)) % MAX_SIZE_HASH_TABLE;  // Calcula o hash acumulando valores dos caracteres
        p_word++;
    }
    return hash;
}

// Insere um novo nó (palavra) na tabela hash na posição calculada pelo hash
void insert_Node_HashTable(Node *hashtable[], char word[]) {
    Node *new_HashNode = create_Node_HashTable(word);  // Cria o novo nó com a palavra
    unsigned int index = hash(word);  // Calcula o índice do hash para a palavra
    new_HashNode->p_next = hashtable[index];  // Insere o novo nó no início da lista encadeada da posição index
    hashtable[index] = new_HashNode;
}

// Procura uma palavra na tabela hash e retorna 1 se encontrada, 0 caso contrário
int search_Node_HashTable(Node *hashtable[], char *word) {
    unsigned int index = hash(word);  // Calcula o índice da tabela para a palavra
    Node *p_current = hashtable[index];  // Aponta para o início da lista encadeada na posição index
    while (p_current != NULL) {  // Percorre a lista encadeada
        if (strcmp(p_current->word, word) == 0) {  // Compara as palavras
            return 1;  // Palavra encontrada
        }
        p_current = p_current->p_next;  // Avança para o próximo nó
    }
    return 0;  // Palavra não encontrada
}

// Verifica se uma palavra está a uma edição de distância da outra (AMARELO) ou mais (VERMELHO)
int red_or_yellow(const char *term, const char *word) {
    int term_len = strlen(term), word_len = strlen(word);
    if (abs(term_len - word_len) > 1) return VERMELHO;  // Se a diferença de tamanho é maior que 1, retorna VERMELHO

    int edits = 0;
    int i = 0, j = 0;
    while (i < term_len && j < word_len) {
        if (term[i] == word[j]) {  // Se os caracteres são iguais, avança
            i++;
            j++;
        } else {
            if (++edits > 1) return VERMELHO;  // Se mais de uma edição é necessária, retorna VERMELHO
            if (term_len > word_len) i++;
            else if (term_len < word_len) j++;
            else {
                i++;
                j++;
            }
        }
    }
    return AMARELO;  // Se a palavra está a uma edição de distância, retorna AMARELO
}

// Busca por palavras similares dentro de uma faixa de hashes e classifica o termo
void search_within_hash_range(Node *hashtable[], const char *term, unsigned int min_hash, unsigned int max_hash) {
    for (unsigned int i = min_hash; i <= max_hash; i++) {  // Percorre a faixa de hashes
        Node *p_current = hashtable[i];
        while (p_current != NULL) {  // Para cada hash, percorre a lista encadeada
            if (red_or_yellow(term, p_current->word) == AMARELO) {  // Verifica a proximidade das palavras
                printf("%s: amarelo\n", term);  // Palavra está a uma edição de distância (AMARELO)
                return;
            }
            p_current = p_current->p_next;
        }
    }
    printf("%s: vermelho\n", term);  // Nenhuma palavra próxima encontrada (VERMELHO)
}

// Gera variações de uma palavra e calcula o intervalo de hashes para essas variações
VariationsHashes generate_variations_with_hashes(const char *term) {
    VariationsHashes result;
    int term_len = strlen(term);

    result.variation_count = 0;
    result.min_hash = MAX_SIZE_HASH_TABLE - 1;
    result.max_hash = 0;

    // Adiciona uma letra em cada posição da palavra
    for (int i = 0; i <= term_len; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            char new_word[MAX_SIZE_WORD] = {0};
            strncpy(new_word, term, i);  // Copia a palavra até a posição i
            new_word[i] = c;  // Insere o caractere c
            strncpy(new_word + i + 1, term + i, term_len - i);  // Completa o restante da palavra
            new_word[MAX_SIZE_WORD - 1] = '\0';

            strncpy(result.variations[result.variation_count], new_word, MAX_SIZE_WORD);
            result.variations[result.variation_count][MAX_SIZE_WORD - 1] = '\0';

            unsigned int current_hash = hash(new_word);
            if (current_hash < result.min_hash) result.min_hash = current_hash;
            if (current_hash > result.max_hash) result.max_hash = current_hash;

            result.variation_count++;
        }
    }

    // Remove uma letra de cada posição
    for (int i = 0; i < term_len; i++) {
        char new_word[MAX_SIZE_WORD] = {0};
        strncpy(new_word, term, i);
        strncpy(new_word + i, term + i + 1, term_len - i - 1);
        new_word[MAX_SIZE_WORD - 1] = '\0';

        strncpy(result.variations[result.variation_count], new_word, MAX_SIZE_WORD);
        result.variations[result.variation_count][MAX_SIZE_WORD - 1] = '\0';

        unsigned int current_hash = hash(new_word);
        if (current_hash < result.min_hash) result.min_hash = current_hash;
        if (current_hash > result.max_hash) result.max_hash = current_hash;

        result.variation_count++;
    }
    return result;
}

// Libera a memória de todos os nós na tabela hash
void free_HashTable(Node *hashtable[]) {
    for (int i = 0; i < MAX_SIZE_HASH_TABLE; i++) {
        Node *p_current = hashtable[i];
        while (p_current != NULL) {
            Node *temp = p_current;
            p_current = p_current->p_next;
            free(temp);  // Libera cada nó individualmente
        }
    }
}
