#include <stdio.h>
#include <string.h>

void is_quase_palindromo(int inicio, int fim, char palavra[], int *num_erros){
    
    if (inicio>=fim){
        return ;
    }

    if (palavra[inicio] != palavra[fim]) {
        (*num_erros)++;
    }

    inicio++;
    fim--;

    is_quase_palindromo(inicio,fim, palavra, num_erros);

}
    

int main(){
    char palavra[401]; //400 caracteres + /0
    int n; //Número de letras erradas permitidas

    scanf("%d", &n);
    scanf("%s", palavra);

    int num_erros = 0;
    int inicio = 0;
    int fim = strlen(palavra)-1;

    is_quase_palindromo( inicio, fim, palavra, &num_erros);

    if (2*num_erros > n) {
        printf("nao\n");
    }

    else{
        printf("sim\n");
    }

    return 0;

}