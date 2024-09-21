#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char base;
    struct Node *prox;
} Node;

Node* create_new_nodo(char base){
    Node * p_novo_no = (Node*)malloc(sizeof(Node)); //Alocar o ponteiro para o novo nó
    p_novo_no->base = base;
    p_novo_no->prox = NULL; //No início ele aponta para nulo
    return p_novo_no; //Retornará o ponteiro do novo nó alocado
}


void inserir(Node* p_DNA, Node * p_novo_no, int pos){
    //Inserir no início da  lista
    if (pos == 0){
        p_novo_no->prox = p_DNA;
        p_DNA = p_novo_no;
    }
    else {
        Node * p_atual = p_DNA; //Ponteiro auxiliar usado para percorrer a lista ligada
        //Iteração percorerá desde o primeiro nó até a posição  anterior a correta para inserir o novo nó
        for (int i = 0; i<pos - 1 && p_atual != NULL; i++){
            p_atual = p_atual->prox;
        }
        //Não se pode inserir um nó
        if (p_atual != NULL){
            p_novo_no->prox = p_atual->prox;
            p_atual->prox = p_novo_no;
        }        
    }
    prinft("%c removido de %d", p_novo_no->base, pos);

}

int main(){
    char command[20];
    scanf("%s", &command);

    Node* p_DNA; //Ponteiro que apontará para o início da lista encadeado (DNA)

    if (strcmp(command,"inserir") == 1){
        char base;
        int pos; //Posição que será inserido
        scanf("%c %d",&base,&pos);

        //Criar um novo nó e alocando-o
        Node * novo_no = create_new_nodo(base);

        //Inserir novo nó no espaço desejado

    }
    else if (strcmp(command,"remover") == 1){
        /* code */
    }
    else if (strcmp(command,"inverter-prefixo") == 1){
        /* code */
    }
    else if (strcmp(command,"inverter-sufixo") == 1){
        /* code */
    }
    else if (strcmp(command,"transpor") == 1){
        /* code */
    }
    else if (strcmp(command,"imprimir") == 1){

    }
    else if (strcmp(command,"sair") == 1){

    }
    
    
    

    return 0;
}