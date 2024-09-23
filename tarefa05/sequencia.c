#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char base;
  struct Node *prox;
  struct Node *ant;
} Node;

int TAMANHO_DNA;

Node *create_new_node(char base) {
  /*Esta função inicializa um nó da lista encadeada*/

  Node *p_novo_no =
      (Node *)malloc(sizeof(Node)); // Alocar o ponteiro para o novo nó
  p_novo_no->base = base;
  p_novo_no->prox = NULL; // No início ele aponta para nulo
  p_novo_no->ant = NULL;
  return p_novo_no; // Retornará o ponteiro do novo nó alocado
}

void imprimir_debug(Node *p_DNA) {
  Node *atual = p_DNA;
  printf("sequencia \n");
  int i = 0;
  while (atual != NULL) {
    if (atual->ant != NULL) {
      printf("%c ", atual->ant->base);
    } else {
      printf("X ");
    }
    printf("%c ", atual->base);

    if (atual->prox != NULL) {
      printf("%c ", atual->prox->base);
    } else {
      printf("X ");
    }
    printf("\n");
    atual = atual->prox;
    if (i == TAMANHO_DNA + 3) {
      break;
    }
    i++;
  }
  printf("\n");
}

void imprimir(Node *p_DNA) {
  /*Esta função imprime a sequencia de DNA da lista encadeada*/
  Node *atual = p_DNA;
  printf("sequencia ");
  int i = 0;
  while (atual != NULL) {
    if (i == TAMANHO_DNA - 1) {
      printf("%c\n", atual->base);
      break;
    } else {
      printf("%c ", atual->base);
    }
    atual = atual->prox;
    i++;
  }

  atual = p_DNA;
  printf("sequencia ");
  i = 0;
  while (atual != NULL) {
    if (i == TAMANHO_DNA - 1) {
      printf("%d\n", i);
      break;
    } else {
      printf("%d ", i);
    }
    i++;
  }
}

void inverter(Node *p_DNA, int tamanho, int modo) {
  /*Esta função inverte a ordem das "tamanho" primeiras letras do DNA*/
  /*A variável "modo" indica se a função será do modo prefixo 1 ou do modo
   * sufixo 2*/

  // Inverte uma trecho do DNA, tanto do sufixo quanto do prefixo
  // Modo = 1; Inverte o prefixo
  // Modo = 2; Inverte o sufixo
  Node *p_inicio = p_DNA;
  Node *p_fim = p_DNA;
  if (modo == 2) {
    // Leva o ponteiro do início e do fim para as posições adequadas na lista

    for (int i = 0; i < TAMANHO_DNA - tamanho; i++) {
      p_inicio = p_inicio->prox;
    }
    p_fim = p_inicio;
    while (p_fim->prox != NULL) {
      p_fim = p_fim->prox;
    }
  } else if (modo == 1) {
    // Leva apenas o ponteiro do fim, já que o do início já está na posição
    for (int i = 0; i < tamanho - 1; i++) {
      p_fim = p_fim->prox;
    }
  }
  if (modo == 1)
    printf("prefixo ");
  else if (modo == 2)
    printf("sufixo ");

  Node *it = p_inicio;
  Node *start = p_inicio;
  for (int i = 0; i < tamanho - 1; i++) {
    printf("%c ", it->base);
    it = it->prox;
  }
  printf("%c -> ", it->base);

  char aux;
  for (int i = 0; i < tamanho / 2; i++) {
    // Troca os valores das posições
    aux = p_inicio->base;
    p_inicio->base = p_fim->base;
    p_fim->base = aux;

    // Volta no ponteiro final, e avança no ponteiro inicial
    p_fim = p_fim->ant;
    p_inicio = p_inicio->prox;
  }

  for (int i = 0; i < tamanho - 1; i++) {
    printf("%c ", start->base);
    start = start->prox;
  }
  printf("%c\n", start->base);
}

void inserir(Node **pp_DNA, Node *p_novo_no, int pos) {
  /*Esta função insere o novo nó na posição "pos"*/

  // Inserir no início da  lista
  if (pos == 0) {
    if (*pp_DNA != NULL) {
      (*pp_DNA)->ant = p_novo_no;
    }
    p_novo_no->prox = *pp_DNA;
    *pp_DNA = p_novo_no;
    p_novo_no->ant = NULL;
  } else {
    Node *p_atual =
        *pp_DNA; // Ponteiro auxiliar usado para percorrer a lista ligada
    // Iteração percorerá desde o primeiro nó até a posição  anterior a correta
    // para inserir o novo nó
    for (int i = 0; i < pos - 1 && p_atual != NULL; i++) {
      p_atual = p_atual->prox;
    }
    // Não se pode inserir um nó
    if (p_atual == NULL) {
      return;
    }

    p_novo_no->prox = p_atual->prox;
    p_atual->prox = p_novo_no;
    p_novo_no->ant = p_atual;
    if (p_novo_no->prox != NULL) {
      p_novo_no->prox->ant = p_novo_no;
    }
  }

  TAMANHO_DNA++;
  printf("%c inserido de %d\n", p_novo_no->base, pos);
}

void remover(Node **pp_DNA, int pos) {
  /*Esta função remove um respectivo nó na posição "pos"*/

  Node *p_atual = *pp_DNA; // Para modificar o p_DNA, preciso guardar o endereço
                           // de memória dele
  Node *p_no_removido = NULL;
  // Remover no início da lista
  if (pos == 0) {
    *pp_DNA = p_atual->prox;
    printf("%c removido de %d\n", p_no_removido->base, pos);
  }

  else {
    for (int i = 0; i < pos - 1 && p_atual != NULL; i++) {
      p_atual = p_atual->prox;
    }
    if (p_atual == NULL) {
      return;
    }

    p_no_removido = p_atual->prox;

    // Remover nó da lista
    p_atual->prox = p_no_removido->prox;
    p_no_removido->prox->ant = p_atual;

    printf("%c removido de %d\n", p_no_removido->base, pos);

    // Liberando espaço do nó removido
    free(p_no_removido);
  }
  TAMANHO_DNA--;
}

void transpor(int p, int q, int r, Node **pp_DNA) {
  /*Esta função transporta uma subsequência do DNA desde uma posição "p" até uma
   * posição "q" em "r" posições*/
  Node *p_inicio = *pp_DNA;
  Node *p_fim = *pp_DNA;

  for (int i = 0; i < p && p_inicio != NULL; i++) {
    p_inicio = p_inicio->prox;
  }
  for (int i = 0; i < q && p_inicio != NULL; i++) {
    p_fim = p_fim->prox;
  }

  Node *p_aux = p_inicio;
  printf("subsequencia ");
  for (int i = 0; i <= q - p; i++) {
    printf("%c ", p_aux->base);
    p_aux = p_aux->prox;
  }

  if (r >= 0) {
    printf(">> %d\n", r);
  } else {
    printf("<< %d\n", -r);
  }

  Node *p_novo_inicio = p_inicio;
  Node *p_novo_fim = p_fim;

  if (r > 0) {
    for (int i = 0; i < r; i++) {
      p_novo_fim = p_novo_fim->prox;
      p_novo_inicio = p_novo_inicio->prox;
    }

    if (p_inicio == NULL || p_fim == NULL || p_novo_inicio == NULL ||
        p_novo_fim == NULL) {
      return;
    }

    Node *p1 = p_inicio->ant;
    Node *p2 = p_fim->prox;
    Node *p3 = p_novo_inicio->prox;

    p1->prox = p2;
    p2->ant = p1;

    p3->prox = p_inicio;
    p_inicio->ant = p3;

    p_fim->prox = p_novo_inicio;
    p_novo_fim->ant = p_fim;

    // p_inicio->ant->prox = p_fim->prox;
    // p_fim->prox->ant = p_inicio->ant;

    // p_novo_inicio->prox = p_inicio;
    // p_inicio->ant = p_novo_inicio;

    // p_novo_fim->ant = p_fim;
    // p_fim->prox = p_novo_fim;

  }

  else {
    for (int i = 0; i < -r; i++) {
      p_novo_fim = p_novo_fim->ant;
      p_novo_inicio = p_novo_inicio->ant;
    }
    if (p_inicio == NULL || p_fim == NULL || p_novo_inicio == NULL ||
        p_novo_fim == NULL) {
      return;
    }

    p_novo_inicio->ant = p_inicio;
  }
}

int main() {
  char command[20];
  Node *p_DNA =
      NULL; // Ponteiro que apontará para o início da lista encadeado (DNA)
  int tamanho;
  while (1) {
    if (scanf("%s", &command[0]) != 1) {
      return 6;
    }

    if (strcmp(command, "inserir") == 0) {
      char base;
      int pos; // Posição que será inserido
      if (scanf(" %c %d", &base, &pos) != 2) {
        return 1;
      };

      // Criar um novo nó e alocando-o
      Node *p_novo_no = create_new_node(base);

      // Inserir novo nó no espaço desejado
      inserir(&p_DNA, p_novo_no, pos);

    } else if (strcmp(command, "remover") == 0) {
      int pos; // posição a ser removido
      if (scanf("%d", &pos) != 1) {
        return 2;
      }

      remover(&p_DNA, pos);
    } else if (strcmp(command, "inverter-prefixo") == 0) {
      if (scanf("%d", &tamanho) != 1) {
        return 3;
      }
      inverter(p_DNA, tamanho, 1);

    } else if (strcmp(command, "inverter-sufixo") == 0) {
      if (scanf("%d", &tamanho) != 1) {
        return 4;
      };
      inverter(p_DNA, tamanho, 2);

    } else if (strcmp(command, "transpor") == 0) {
      int p, q, r;
      if (scanf("%d %d %d", &p, &q, &r) != 3) {
        return 5;
      }
      transpor(p, q, r, &p_DNA);
    } else if (strcmp(command, "imprimir") == 0) {
      imprimir(p_DNA);
    } else if (strcmp(command, "imprimir_debug") == 0) {
      imprimir_debug(p_DNA);
    } else if (strcmp(command, "sair") == 0) {
      break;
    }
  }

  return 0;
}