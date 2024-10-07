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
    /*Esta funçã constroi e árvore binária chamando a si mesmo de forma recursiva para pegar as subespressões de uma expressão maior*/

    char c = expression[*aux_pointer];
    (*aux_pointer)++;


    //Criando nós a cada chamada
    if (c == 'T', || c == 'F' || is_lower(c)){
        //Se o caractere for um T,F ou minúscula, este se comportará como uma folha, isto é, não terá nós descendentes
        return create_node(c,NULL,NULL);
    }
    else if (c == '!') {
        //Se o caractere for um !, então não haverá árvore à esquerda e a função build_tree será chamad novamente para analisar os próximos caracteres
        return create_node('c', build_tree(expression, aux_pointer), NULL);
    }
    else if (c == '('){
        //Se o caractere dor '(' significa que há uma sub expressão por vir

        //1° é necessário construir a árvore à esquerda do operador que virá após o (
        Node * left = build_tree(expression, aux_pointer);

        //Ler qual operador é
        char operator = expression[*aux_pointer];
        (*aux_pointer)++;

        //Construir a árvore com a sub expressão à direita do operador
        Node * right = build_tree(expression, aux_pointer);
        (*aux_pointer)++;

        return create_node(operator,left,right);
    }
    
    //Retorna a raiz da árvore que representa toda a expressão
}

int is_lower(char c){
    /*Essa função verifica de acordo com a tabela ASCII se uma variável é ou não uma letra minúscula*/
    return (c>= 'a' && c <= 'z');
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