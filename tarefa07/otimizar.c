#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPRESSION 1000

// Definição da estrutura de nó da árvore
typedef struct Node {
    char valor;
    struct Node *left, *right;
} Node;

// Função para criar um nó da árvore
Node* create_node(char valor, Node* left, Node* right) {
    Node* new_node = malloc(sizeof(Node));
    new_node->left = left;
    new_node->right = right;
    new_node->valor = valor;
    return new_node;
}

// Função para verificar se um caractere é uma variável (letra minúscula)
int is_lower(char c) {
    return (c >= 'a' && c <= 'z');
}

// Função para construir a árvore a partir da expressão
Node* build_tree() {
    char c;
    scanf("%c", &c);

    if (c == 'T' || c == 'F' || is_lower(c)) {
        return create_node(c, NULL, NULL);
    } else if (c == '!') {
        return create_node(c, build_tree(), NULL);
    } else if (c == '(') {
        Node* left = build_tree();
        char operator;
        scanf("%c", &operator);
        
        Node* right = build_tree();
        char parenteses;
        scanf("%c", &parenteses);
        
        return create_node(operator, left, right);
    }
    return NULL;
}

// Função para simplificar negações aplicando as leis de De Morgan e eliminando dupla negação
Node* simplificar_negacao(Node* raiz) {
    if (raiz == NULL) return NULL;

    if (raiz->valor == '!') {
        Node* son = raiz->left;

        if (son->valor == '|') {
            Node* not_left = create_node('!', simplificar_negacao(son->left), NULL);
            Node* not_right = create_node('!', simplificar_negacao(son->right), NULL);
            raiz = create_node('&', not_left, not_right);
        } else if (son->valor == '&') {
            Node* not_left = create_node('!', simplificar_negacao(son->left), NULL);
            Node* not_right = create_node('!', simplificar_negacao(son->right), NULL);
            raiz = create_node('|', not_left, not_right);
        } else if (son->valor == '!') {
            raiz = simplificar_negacao(son->left);
        }
    }

    raiz->left = simplificar_negacao(raiz->left);
    raiz->right = simplificar_negacao(raiz->right);

    return raiz;
}

// Função para verificar se o nó é uma variável ou constante
int is_variavel(Node* exp) {
    return is_lower(exp->valor) || exp->valor == 'T' || exp->valor == 'F';
}

// Função para verificar se duas expressões são equivalentes
int is_equivalente(Node* exp1, Node* exp2) {
    if (is_variavel(exp1) && is_variavel(exp2)) {
        return exp1->valor == exp2->valor;
    }
    if (exp1->valor == '!' && exp2->valor == '!') {
        return is_equivalente(exp1->left, exp2->left);
    }
    if (exp1->valor == exp2->valor) {
        if ((is_equivalente(exp1->left, exp2->left) && is_equivalente(exp1->right, exp2->right)) ||
            (is_equivalente(exp1->left, exp2->right) && is_equivalente(exp1->right, exp2->left))) {
            return 1;
        }
    }
    return 0;
}

// Função para simplificar a árvore
Node* simplificar(Node* raiz) {
    if (raiz == NULL) return NULL;

    // Simplificar os filhos primeiro
    raiz->left = simplificar(raiz->left);
    raiz->right = simplificar(raiz->right);

    if (raiz->valor == '&') {
        if (raiz->left->valor == 'T') return raiz->right;
        if (raiz->right->valor == 'T') return raiz->left;
        if (raiz->left->valor == 'F' || raiz->right->valor == 'F') {
            free(raiz);
            return create_node('F', NULL, NULL);
        }
        if (is_equivalente(raiz->left, raiz->right)) {
            free(raiz->right);
            return raiz->left;
        }
    } else if (raiz->valor == '|') {
        if (raiz->left->valor == 'F') return raiz->right;
        if (raiz->right->valor == 'F') return raiz->left;
        if (raiz->left->valor == 'T' || raiz->right->valor == 'T') {
            free(raiz);
            return create_node('T', NULL, NULL);
        }
        if (is_equivalente(raiz->left, raiz->right)) {
            free(raiz->right);
            return raiz->left;
        }
    } else if (raiz->valor == '!') {
        if (raiz->left->valor == 'T') {
            free(raiz);
            return create_node('F', NULL, NULL);
        }
        if (raiz->left->valor == 'F') {
            free(raiz);
            return create_node('T', NULL, NULL);
        }
    }

    return raiz;
}

// Função para imprimir a expressão a partir da árvore
void imprimir(Node* raiz) {
    if (raiz == NULL) return;

    if (raiz->valor == 'T' || raiz->valor == 'F' || is_lower(raiz->valor)) {
        printf("%c", raiz->valor);
    } else if (raiz->valor == '!') {
        printf("%c", raiz->valor);
        imprimir(raiz->left);
    } else {
        printf("(");
        imprimir(raiz->left);
        printf("%c", raiz->valor);
        imprimir(raiz->right);
        printf(")");
    }
}

// Função principal
int main() {
    // Construir a árvore da expressão
    
    Node* raiz = build_tree();

    // Imprimir a expressão original
    imprimir(raiz);
    printf("\n");

    // Aplicar a simplificação de negação (De Morgan e dupla negação)
    Node* padronizada = simplificar_negacao(raiz);

    // Imprimir a expressão após a padronização
    imprimir(padronizada);
    printf("\n");

    // Simplificar a expressão
    Node* simplificada = simplificar(padronizada);

    // Imprimir a expressão simplificada
    imprimir(simplificada);
    printf("\n");

    // Liberar memória
    free(raiz);

    return 0;
}
