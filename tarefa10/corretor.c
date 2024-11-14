#include <stdio.h>
#include "interface_tad.h"

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    Node *hashtable[MAX_SIZE_HASH_TABLE];
    initialize_HashTable(hashtable);

    // Lê e insere palavras na tabela hash
    for (int x = 0; x < m; x++) {
        char word[MAX_SIZE_WORD];
        scanf("%s", word);
        insert_Node_HashTable(hashtable, word);
    }
    
    // Lê cada termo e determina seu status (VERDE, AMARELO, ou VERMELHO)
    for (int x = 0; x < n; x++) {
        char term[MAX_SIZE_WORD];
        scanf("%s", term);
        
        int is_hashtable = search_Node_HashTable(hashtable, term);
        if (is_hashtable) {
            printf("%s: verde\n", term);  // Palavra exata encontrada (VERDE)
            continue;
        }

        // Gera variações da palavra e verifica na tabela hash
        VariationsHashes variations_hashes = generate_variations_with_hashes(term);
        search_within_hash_range(hashtable, term, variations_hashes.min_hash, variations_hashes.max_hash);
    }

    // Libera a memória alocada para a tabela hash
    free_HashTable(hashtable);

    return 0;
}
