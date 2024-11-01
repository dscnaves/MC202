#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE_WORD 26
#define MAX_SIZE_HASH_TABLE 100
#define MAX_SIZE_COLOR 9

typedef struct HashTableNode{
    char word[MAX_SIZE_WORD];
    struct HashTableNode * p_next;
} Node;

// Definindo o enum para as cores
typedef enum {
    VERMELHO,
    AMARELO,
    VERDE
} Color;

void initialize_HashTable(Node * hashtable[]){
    for (int i = 0; i<MAX_SIZE_HASH_TABLE; i++){
        hashtable[i] = NULL;
    }
}

Node * create_Node_HashTable(char word[]){
    //Alocando espaço para o nó
    Node * New_HashNode = malloc(sizeof(Node));
    if (New_HashNode == NULL){
        printf("Erro ao alocar memória no nó.\n");
        exit(1);
    }

    //Receber valores inicializando
    strncpy(New_HashNode->word,word,MAX_SIZE_WORD);
    New_HashNode->p_next = NULL;

    return New_HashNode;
}

unsigned int hash(const char * p_word){
    unsigned int hash = 0;
    while (*p_word){ //Condição de parada => Chegar em algum caracter nulo (\0)
        hash = (hash * 31 + (*p_word)) % MAX_SIZE_HASH_TABLE;
        p_word++; //Fazendo o ponteiro apontar para a próxima letra 4 bits depois 
    }
    return hash;
}

void insert_Node_HashTable(Node * hashtable[], char word[]){
    //Alocando o nó a ser inserido
    Node * new_HashNode = create_Node_HashTable(word);
    //Calculando o indice onde o a palavra deve ser inserida
    unsigned int index = hash(word);

    
    //Se não houber colisão
    if (hashtable[index] == NULL){
        hashtable[index] = new_HashNode;
        return;
    }

    //Se houver colisão => Adiciona novo nó ao início da lista
    new_HashNode->p_next = hashtable[index];
    hashtable[index] = new_HashNode;
    return;
}

int search_Node_HashTable(Node * hashtable[], char * word){
    unsigned int index = hash(word);
    Node * p_current = hashtable[index];

    while (p_current != NULL){
        if (strcmp(p_current->word, word) == 0){
            return 1;
        }
        p_current = p_current->p_next;
    }
    return 0;
}

int red_or_yellow(const char *term, const char *word){
    int term_len = strlen(term), word_len = strlen(word);

    if (abs(term_len - word_len) > 1) return VERMELHO;

    int edits = 0;
    int i = 0, j = 0;

    while(i < term_len && j < word_len){
        //Se os caracteres forem igual, continue comparando
        if (term[i] == word[j]) {i++; j++;}      

        //Se forem diferentes
        else if (term[i] != word[j]){
            //Incrementar número de edições
            if (++edits > 1) return VERMELHO; //Se o número de edições superar 1 => VERMELHO

            //Se as palavras tirem uma diferença de tamanho, ajuste para que possamos comparar o próximo caracter
            if (term_len > word_len) i++; //Caso em que inserimos um caracter
            else if (term_len < word_len) j++; ////Caso em que removemos um caracter

            //Se não houber diferença no tamanho, continue comparando => Caso de troca ou combinação de remoções e de inserções
            else {i++; j++;}
        }
    }
    //Palavra passou por todas as comparações e o número de edits não superou 1 => AMARELO
    return AMARELO;
}

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

int main(){
    int m, n; //o número de palavras no dicionário e o número de palavras do texto
    scanf("%d %d", &m, &n);

    //Inicializando Tabela de Dispersão
    Node * hashtable[MAX_SIZE_HASH_TABLE];
    initialize_HashTable(hashtable);

    //Construindo a Tabela de Dispersão
    for (int x = 0; x<m; x++){
        char word[MAX_SIZE_WORD];
        scanf("%s", word);

        insert_Node_HashTable(hashtable, word);
    }

    //Classificação das palavras
    for (int x = 0; x<n; x++){
        //Leitura do termo
        char term[MAX_SIZE_WORD];
        scanf("%s", term);

        //Busca da palavra na hashtable => Classificação VERDE
        int is_hashtable = search_Node_HashTable(hashtable,term);
        if (is_hashtable){
            printf("%s: verde\n", term);
        }
        //Classificação AMARELO ou VERMELHO
        char variations[MAX_SIZE_WORD+1][MAX_SIZE_WORD];
        int variation_count = 0;

        generate_variations(term, variations, &variation_count);

        int found = 0;
        for (int i = 0; i < variation_count; i++) {
            if (search_Node_HashTable(hashtable, variations[i])){
                found = 1;
                printf("%s: amarelo\n", term);
                break;
            }
        }
        if (!found) printf("%s: vermelho\n", term);




        // else {
        //     //Classificação entre VERMELHO E AMARELO
        //     int index_term = hash(term);

        //     Node * p_current = hashtable[index_term];
            
        //     int found = 0;

        //     for (int y = 0; y<MAX_SIZE_HASH_TABLE; y++){
        //         p_current = hashtable[y];
        //         while (p_current != NULL){
        //             if (red_or_yellow(term, p_current->word) == AMARELO){
        //                 printf("%s: amarelo\n", term);
        //                 found = 1;
        //                 break;
        //             }
        //             p_current = p_current->p_next;
        //         }
        //         if (found) break;
        //     }
        //     if (!found) {
        //         printf("%s: vermelho\n", term);
        //     }
        // }
    }
        

    return 0;
}