#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPRESSION 100

typedef struct Node {
    char valor; //Variável para armazenar tanto variáveis quanto operadores matemáticos
    struct Node * left, *right;
} Node;

Node * create_node(char valor, Node * left, Node * right){
    /*Função para inicializar um nó da árvore binária*/
    Node * new_node = malloc(sizeof(Node));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->valor = valor;
    return new_node;
}

Node * build_tree(char expression, int * aux_pointer){
    char c = expression[*aux_pointer];
}

Node * simplificar_negacao(Node * raiz){

}


int main(){
    //Leitura da entrada
    char expression[MAX_EXPRESSION];
    int aux_pointer = 0; //Ponteiro auxiliar usado para percorrear os caracteres da expressão matemática
    scanf("%s", expression);


    return 0;
}