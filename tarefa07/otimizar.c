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
    new_node->left = left;
    new_node->right = right;
    new_node->valor = valor;
    return new_node;
}

int is_lower(char c){
    /*Essa função verifica de acordo com a tabela ASCII se uma variável é ou não uma letra minúscula*/
    return (c>= 'a' && c <= 'z');
}

Node * build_tree(char expression[], int * aux_pointer){
    /*Esta funçã constroi e árvore binária chamando a si mesmo de forma recursiva para pegar as subespressões de uma expressão maior*/

    char c = expression[*aux_pointer];
    (*aux_pointer)++;


    //Criando nós a cada chamada
    if (c == 'T' || c == 'F' || is_lower(c)){
        //Se o caractere for um T,F ou minúscula, este se comportará como uma folha, isto é, não terá nós descendentes
        return create_node(c,NULL,NULL);
    }
    else if (c == '!') {
        //Se o caractere for um !, então não haverá árvore à esquerda e a função build_tree será chamad novamente para analisar os próximos caracteres
        return create_node(c, build_tree(expression, aux_pointer), NULL);
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
    return NULL;
}

Node * simplificar_negacao(Node * raiz){
    if (raiz == NULL) return NULL; //Ponto de parada da recursão é quando se chega a um nó que não tem mais filhos, ou seja, uma folha

    if (raiz->valor == '!'){
        //Pega o filho da esquerda (Único filho)
        Node * son = raiz->left;

        //Se a expressão da negação tiver &, | ou !! => Precisa simplificar
        if (son->valor == '|'){
            //!(A | B) => (!A & !B)
            Node * not_left = create_node('!', simplificar_negacao(son->left), NULL); //!A
            Node * not_right = create_node('!', simplificar_negacao(son->right), NULL); //!B            
            
            return create_node('&', not_left, not_right); //!A & !B
        }

        else if (son->valor == '&'){
            //!(A & B) => (!A | !B)
            Node * not_left = create_node('!', simplificar_negacao(son->left), NULL); //!A
            Node * not_right = create_node('!', simplificar_negacao(son->right), NULL); //!B            
            
            return create_node('|', not_left, not_right); //!A & !B
        }
        else if(son->valor == '!'){
            //!!A => A
            return simplificar_negacao(son->left); // Retorna a expressão interna A
        }
    }

    //Percorer toda a árvore procurando !'s
    raiz->left = simplificar_negacao(raiz->left);
    raiz->right = simplificar_negacao(raiz->right);

    // Retorna a raiz atualizada
    return raiz;
}

is_variavel(Node * exp){
    if (is_lower(exp->valor) || exp->valor == 'T' || exp->valor == 'F') return 1;
    else return 0;
}

//Função para verificar se duas expressões são equivalentes
int is_equivalente (Node * exp1, Node * exp2, Node * raiz){
    //Caso base: exp1 ou exp2 forem variáveis
    if (is_variavel(exp1) || is_variavel(exp2)){
        if (exp1->valor == exp2->valor) return 1;
        else return 0;
    }
    //caso geral:
    if (raiz->valor == '&' || raiz->valor == '|'){ //Verificando se o operador é '&' ou '|'
        if (is_equivalente(exp1->left, exp2->left, raiz) && is_equivalente(exp1->right, exp2->right, raiz) 
    || (is_equivalente(exp1->left, exp2->right,raiz) && is_equivalente(exp1->right, exp2->left,raiz))) return 1;
    } 

    else if (exp1->valor == '!' && exp2->valor == '!'){
        if (is_equivalente(exp1->left, exp2->left)) return 1;
    }
}

//Função para liberar dinamicamente memória da árvore
void destruir_arvore(Node * raiz){
    if (raiz->left != NULL || raiz->right != NULL){
        destruir_arvore(raiz->left);
        destruir_arvore(raiz->right);
        free(raiz);
    }    
}

Node * simplificar(Node * raiz){
    if (raiz == NULL) return NULL; //Ponto de parada da recursão é quando se chega a um nó que não tem mais filhos, ou seja, uma folha

    // Simplificação de subárvores
    raiz->left = simplificar(raiz->left);
    raiz->right = simplificar(raiz->right);

    // Regras de simplificação
    if (raiz->valor == '&') {
        if (raiz->left->valor == 'T') return raiz->right; // x&T=x
        if (raiz->right->valor == 'T') return raiz->left; // T&x=x
        if (raiz->left->valor == 'F' || raiz->right->valor == 'F') {
            destruir_arvore(raiz);
            return create_node('F', NULL, NULL); //F&x = F ou x&F = F
        }
        /*
        is_equivalente(raiz->left, raiz->right) = true
            tmp = raiz
            raiz = raiz->left
            destruir_arvore(tmp->right)
            free(tmp)
        */
    }
    else if (raiz->valor == '|') {
        if (raiz->left->valor == 'F') return raiz->right; // x&F=x
        if (raiz->right->valor == 'F') return raiz->left; // F&x=x
        if (raiz->left->valor == 'T' || raiz->right->valor == 'T') return create_node('T', NULL, NULL); //T&x = T ou x&T = T
    }
    else if (raiz->valor == '!') {
        if (raiz->left->valor == 'T') return create_node('F', NULL, NULL); //!T = F
        if (raiz->left->valor == 'F') return create_node('T', NULL, NULL); //!F = T
    }

    // Retorna a raiz após simplificação
    return raiz;
}

void imprimir(Node * raiz) {
    if (raiz == NULL) return;

    if (raiz->valor == 'T' || raiz->valor == 'F' || is_lower(raiz->valor)) {
        printf("%c", raiz->valor);
    } 
    else if (raiz->valor == '!'){
        printf("%c", raiz->valor);
        imprimir(raiz->left);
        imprimir(raiz->right);
    }
    else {
        printf("(");
        imprimir(raiz->left);
        printf("%c", raiz->valor);
        imprimir(raiz->right);
        printf(")");
    }
}

int main(){
    //Leitura da entrada
    char expression[MAX_EXPRESSION];
    int aux_pointer = 0; //Ponteiro auxiliar usado para percorrear os caracteres da expressão matemática
    scanf("%s", expression);

    // Construir a árvore da expressão
    Node* raiz = build_tree(expression, &aux_pointer);

    // Imprimir a expressão original
    
    imprimir(raiz);
    printf("\n");

    
    Node* padronizada = simplificar_negacao(raiz);
    
    imprimir(padronizada);
    printf("\n");

    // Simplificar a expressão
    Node* simplificada = simplificar(padronizada);
    
    imprimir(simplificada);
    printf("\n");


    return 0;
}