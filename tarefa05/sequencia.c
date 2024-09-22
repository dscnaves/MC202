#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char base;
    struct Node *prox;
} Node;

Node* create_new_node(char base){
    Node * p_novo_no = (Node*)malloc(sizeof(Node)); //Alocar o ponteiro para o novo nó
    p_novo_no->base = base;
    p_novo_no->prox = NULL; //No início ele aponta para nulo
    return p_novo_no; //Retornará o ponteiro do novo nó alocado
}


void inserir(Node** p_DNA, Node * p_novo_no, int pos){
    //Inserir no início da  lista
    if (pos == 0){
        p_novo_no->prox = *p_DNA;
        *p_DNA = p_novo_no;
    }
    else {
        Node * p_atual = *p_DNA; //Ponteiro auxiliar usado para percorrer a lista ligada
        //Iteração percorerá desde o primeiro nó até a posição  anterior a correta para inserir o novo nó
        for (int i = 0; i < pos - 1 && p_atual != NULL; i++){
            p_atual = p_atual->prox;
        }
        //Não se pode inserir um nó
        if (p_atual != NULL){
            p_novo_no->prox = p_atual->prox;
            p_atual->prox = p_novo_no;
        }        
    }
    printf("%c inserido de %d\n", p_novo_no->base, pos);

}

void remover(Node** pp_DNA, int pos){
    Node * p_atual = *pp_DNA; //Para modificar o p_DNA, preciso guardar o endereço de memória dele
    Node * p_no_removido = NULL;
    //Remover no início da lista
    if (pos == 0){
        *pp_DNA = p_atual->prox;
        printf("%c removido de %d\n", p_atual->prox->base, pos);
    }

    else{
        for (int i = 0; i < pos - 1 && p_atual != NULL; i++){
            p_atual = p_atual->prox;
        }
        p_no_removido = p_atual->prox;

        if (p_atual != NULL){
            //Remover nó da lista
            p_atual->prox = p_atual->prox->prox;

            printf("%c removido de %d\n", p_atual->prox->base, pos);

            //Liberando espaço do nó removido
            free(p_no_removido);
        }
    }
}

void imprimir(Node * p_DNA){
    Node * atual = p_DNA;
    printf("sequencia ");
    while (atual != NULL){
        printf("%c",atual->base);
        atual = atual->prox;
    }
    printf("\n");
}

int main(){
    char command[20];
    Node* p_DNA = NULL; //Ponteiro que apontará para o início da lista encadeado (DNA)

    while(1){
        scanf("%s", &command[0]);

        if (strcmp(command,"inserir") == 0){
            char base;
            int pos; //Posição que será inserido
            scanf(" %c %d",&base,&pos);
            
            //Criar um novo nó e alocando-o
            Node * p_novo_no = create_new_node(base);

            //Inserir novo nó no espaço desejado
            inserir(&p_DNA,p_novo_no,pos);

        }
        else if (strcmp(command,"remover") == 0){
            int pos; //posição a ser removido
            scanf("%d", &pos);

            remover(&p_DNA, pos);
        }
        else if (strcmp(command,"inverter-prefixo") == 0){
            /* code */
        }
        else if (strcmp(command,"inverter-sufixo") == 0){
            /* code */
        }
        else if (strcmp(command,"transpor") == 0){
            /* code */
        }
        else if (strcmp(command,"imprimir") == 0){
            imprimir(p_DNA);
        }
        else if (strcmp(command,"sair") == 0){
            break;
        }
            
    }
    

    return 0;
}