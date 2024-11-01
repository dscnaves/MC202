#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE_WORD 26
#define MAX_SIZE_HASH_TABLE 100
#define MAX_SIZE_COLOR 9

typedef struct HashTableNode {
    char word[MAX_SIZE_WORD];
    struct HashTableNode *p_next;
} Node;

typedef struct {
    char variations[MAX_SIZE_WORD * 26][MAX_SIZE_WORD];
    int variation_count;
    unsigned int min_hash;
    unsigned int max_hash;
} VariationsHashes;

// Definindo o enum para as cores
typedef enum {
    VERMELHO,
    AMARELO,
    VERDE
} Color;

void initialize_HashTable(Node *hashtable[]) {
    for (int i = 0; i < MAX_SIZE_HASH_TABLE; i++) {
        hashtable[i] = NULL;
    }
}

Node *create_Node_HashTable(char word[]) {
    Node *New_HashNode = malloc(sizeof(Node));
    if (New_HashNode == NULL) {
        printf("Erro ao alocar memória no nó.\n");
        exit(1);
    }
    strncpy(New_HashNode->word, word, MAX_SIZE_WORD);
    New_HashNode->word[MAX_SIZE_WORD - 1] = '\0'; // Garantir o terminador nulo
    New_HashNode->p_next = NULL;
    return New_HashNode;
}

unsigned int hash(const char *p_word) {
    unsigned int hash = 0;
    while (*p_word) {
        hash = (hash * 31 + (*p_word)) % MAX_SIZE_HASH_TABLE;
        p_word++;
    }
    return hash;
}

void insert_Node_HashTable(Node *hashtable[], char word[]) {
    Node *new_HashNode = create_Node_HashTable(word);
    unsigned int index = hash(word);
    if (hashtable[index] == NULL) {
        hashtable[index] = new_HashNode;
        return;
    }
    new_HashNode->p_next = hashtable[index];
    hashtable[index] = new_HashNode;
    return;
}

int search_Node_HashTable(Node *hashtable[], char *word) {
    unsigned int index = hash(word);
    Node *p_current = hashtable[index];
    while (p_current != NULL) {
        if (strcmp(p_current->word, word) == 0) {
            return 1;
        }
        p_current = p_current->p_next;
    }
    return 0;
}

int red_or_yellow(const char *term, const char *word) {
    int term_len = strlen(term), word_len = strlen(word);
    if (abs(term_len - word_len) > 1) return VERMELHO;
    int edits = 0;
    int i = 0, j = 0;
    while (i < term_len && j < word_len) {
        if (term[i] == word[j]) {
            i++;
            j++;
        } else {
            if (++edits > 1) return VERMELHO;
            if (term_len > word_len) i++;
            else if (term_len < word_len) j++;
            else {
                i++;
                j++;
            }
        }
    }
    return AMARELO;
}

void search_within_hash_range(Node *hashtable[], const char *term, unsigned int min_hash, unsigned int max_hash) {
    for (unsigned int i = min_hash; i <= max_hash; i++) {
        Node *p_current = hashtable[i];
        while (p_current != NULL) {
            if (red_or_yellow(term, p_current->word) == AMARELO) {
                printf("%s: amarelo\n", term);
                return;
            }
            p_current = p_current->p_next;
        }
    }
    printf("%s: vermelho\n", term);
}

VariationsHashes generate_variations_with_hashes(const char *term) {
    VariationsHashes result;
    int term_len = strlen(term);

    result.variation_count = 0;
    result.min_hash = MAX_SIZE_HASH_TABLE - 1;
    result.max_hash = 0;

    for (int i = 0; i <= term_len; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            char new_word[MAX_SIZE_WORD] = {0};
            strncpy(new_word, term, i);
            new_word[i] = c;
            strncpy(new_word + i + 1, term + i, term_len - i);
            new_word[MAX_SIZE_WORD - 1] = '\0'; // Garantir o terminador nulo
            strncpy(result.variations[result.variation_count], new_word, MAX_SIZE_WORD);
            result.variations[result.variation_count][MAX_SIZE_WORD - 1] = '\0'; // Garantir o terminador nulo

            unsigned int current_hash = hash(new_word);

            if (current_hash < result.min_hash) result.min_hash = current_hash;
            if (current_hash > result.max_hash) result.max_hash = current_hash;

            result.variation_count++;
        }
    }

    for (int i = 0; i < term_len; i++) {
        char new_word[MAX_SIZE_WORD] = {0};
        strncpy(new_word, term, i);
        strncpy(new_word + i, term + i + 1, term_len - i - 1);
        new_word[MAX_SIZE_WORD - 1] = '\0'; // Garantir o terminador nulo
        strncpy(result.variations[result.variation_count], new_word, MAX_SIZE_WORD);
        result.variations[result.variation_count][MAX_SIZE_WORD - 1] = '\0'; // Garantir o terminador nulo

        unsigned int current_hash = hash(new_word);

        if (current_hash < result.min_hash) result.min_hash = current_hash;
        if (current_hash > result.max_hash) result.max_hash = current_hash;
        
        result.variation_count++;
    }
    return result;
}


int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    Node *hashtable[MAX_SIZE_HASH_TABLE];
    initialize_HashTable(hashtable);

    for (int x = 0; x < m; x++) {
        char word[MAX_SIZE_WORD];
        scanf("%s", word);
        insert_Node_HashTable(hashtable, word);
    }
    
    for (int x = 0; x < n; x++) {
        char term[MAX_SIZE_WORD];
        scanf("%s", term);
        
        int is_hashtable = search_Node_HashTable(hashtable, term);
        if (is_hashtable) {
            printf("%s: verde\n", term);
            continue; //Faz com que o loop pule o restante das instruções na sua iteração atual e comece imediatamente a próxima iteração
        }

        VariationsHashes variations_hashes = generate_variations_with_hashes(term);
        search_within_hash_range(hashtable, term, variations_hashes.min_hash, variations_hashes.max_hash);
    }
    return 0;
}