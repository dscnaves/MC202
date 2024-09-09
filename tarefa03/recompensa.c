#include <stdio.h>

double jogar_dado(int x, int n){

    //Casos base
    if (x < 0){
        return 0;
    }

    else if (x > 0 && n <= 0) {
        return 0;
    }

    else if (x == 0){
        return 1;
    }

    double soma_probabilidades = 0;

    //Casos não base
    soma_probabilidades += (1.0/6.0)*jogar_dado(x-1,n-1);  
    
    soma_probabilidades += (1.0/6.0)*jogar_dado(x-2,n-1);
    
    soma_probabilidades += (1.0/6.0)*jogar_dado(x-3,n-1);
    
    soma_probabilidades += (1.0/6.0)*jogar_dado(x-4,n-1);
    
    soma_probabilidades += (1.0/6.0)*jogar_dado(x-5,n-1);
    
    soma_probabilidades += (1.0/6.0)*jogar_dado(x-6,n-1);    

    return soma_probabilidades;
}

int main(){
    int n;
    int x;
    double soma_probabilidades = 0;

    scanf("%d %d",&n,&x);

    soma_probabilidades = jogar_dado(x,n);

    printf("%.3f", soma_probabilidades);
    return 0;
}