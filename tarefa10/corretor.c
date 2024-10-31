#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_WORD 26
#define MAX_SIZE_HASH_TABLE 100

typedef struct HashTableNode{
    char word[MAX_SIZE_WORD];
    struct HashTableNode * p_next;
} Node;

void initialize_HashTable(Node * hashtable[]){
    for (int i = 0; i<MAX_SIZE_HASH_TABLE; i++){
        hashtable[i] = NULL;
    }
}

Node * create_Node_HashTable(char word[]){
    //Alocando espaço para o nó
    Node * New_HashNode = malloc(sizeof(Node));

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

void insert_Node_HashTable(Node * hashtable[], Node * new_HashNode, unsigned int index){
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

int main(){
    int m, n; //o número de palavras no dicionário e o número de palavras do texto
    scanf("%d %d", &m, &n);

    //Inicializando Tabela de Dispersão
    Node * hashtable[MAX_SIZE_HASH_TABLE];
    initialize_HashTable(hashtable);

    //Construindo a Tabela de Dispersão
    for (int i = 0; i<m; i++){
        char word[MAX_SIZE_WORD];
        scanf("%s", word);

        Node * new_HashNode = create_Node_HashTable(word);

        unsigned int index = hash(word);
        insert_Node_HashTable(hashtable, new_HashNode, index);
    }


    return 0;
}