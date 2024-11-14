#ifndef interface_tad
#define interface_tad

#include <stdbool.h>

// Definindo tamanhos máximos
#define MAX_SIZE_WORD 26           // Tamanho máximo para uma palavra
#define MAX_SIZE_HASH_TABLE 100     // Tamanho máximo para a tabela hash
#define MAX_SIZE_COLOR 9            // Tamanho máximo para a string de cor (ex. "VERMELHO")

// Estrutura de nó para armazenar uma palavra na tabela hash e uma referência para o próximo nó na lista encadeada
typedef struct HashTableNode {
    char word[MAX_SIZE_WORD];        // Armazena a palavra
    struct HashTableNode *p_next;    // Ponteiro para o próximo nó na lista encadeada (em caso de colisão)
} Node;

// Estrutura para armazenar variações de palavras e seus hashes correspondentes
typedef struct {
    char variations[MAX_SIZE_WORD * 26][MAX_SIZE_WORD]; // Armazena todas as variações possíveis da palavra
    int variation_count;                               // Conta o número de variações geradas
    unsigned int min_hash;                             // Menor hash gerado para as variações
    unsigned int max_hash;                             // Maior hash gerado para as variações
} VariationsHashes;

// Enumeração para cores de status
typedef enum {
    VERMELHO,
    AMARELO,
    VERDE
} Color;

// Funções do TAD

// Inicializa a tabela hash, definindo todos os elementos para NULL
void initialize_HashTable(Node *hashtable[]);

// Cria um novo nó para a tabela hash, inicializando com uma palavra
Node *create_Node_HashTable(char word[]);

// Calcula o hash de uma palavra, que será o índice na tabela hash
unsigned int hash(const char *p_word);

// Insere uma palavra na tabela hash
void insert_Node_HashTable(Node *hashtable[], char word[]);

// Procura uma palavra na tabela hash e retorna 1 se encontrada, 0 caso contrário
int search_Node_HashTable(Node *hashtable[], char *word);

// Verifica se uma palavra está a uma edição de distância (cor AMARELO) ou mais (cor VERMELHO)
int red_or_yellow(const char *term, const char *word);

// Busca por palavras dentro de uma faixa de hashes e imprime seu status (amarelo ou vermelho)
void search_within_hash_range(Node *hashtable[], const char *term, unsigned int min_hash, unsigned int max_hash);

// Gera variações de uma palavra e calcula o intervalo de hashes para as variações
VariationsHashes generate_variations_with_hashes(const char *term);

// Libera a memória alocada para todos os nós na tabela hash
void free_HashTable(Node *hashtable[]);

#endif