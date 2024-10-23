#include <stdio.h>
#include <stdlib.h>

// Função para alocar e inicializar a estrutura de próximos acessos
int* next_access_initialize(int num_objects, int length) {
    //O array chamado next_access é usado para para armazenar quando cada objeto será acessado novamente

    int *next_access = malloc(num_objects * sizeof(int *));
    
    for (int i = 0; i < num_objects; i++) {
        next_access[i] = length; // Inicializa como não acessado mais => lenght é um marcador cujo acesso inváido ao vetor é usado para revelar que um objeto não será mais acessado 
    }
    return next_access;
}

// Função para alocar e inicializar os acessos futuros
int** future_access_initialize(int num_objects, int length) {
    //A matriz chamada future_access é aquela onde cada linha corresponde a um objeto, e cada linha armazena as posições na sequência em que esse objeto será acessado no futuro

    int **future_access = malloc(num_objects * sizeof(int **));
    
    for (int i = 0; i < num_objects; i++) {
        future_access[i] = malloc(length * sizeof(int *));
    }
    return future_access;
}

// Função para liberar a memória de acessos futuros com as posições futuras dos objetos na sequência
void future_access_free(int **future_access, int num_objects) {
    for (int i = 0; i < num_objects; i++) {
        free(future_access[i]);
    }
    free(future_access);
}

//Essa função preenche a matriz future_acess
void calcular_proximos_acessos(int sequence[], int length, int **future_access, int *contador_acessos, int num_objects) {
    

    //Percorrer a lista de acesso de trás para frente para garantirmos que a matriz seja preenchida  com as posições mais próximas no futuro para cada objeto
    for (int i = length - 1; i >= 0; i--) {
        int obj = sequence[i];
        
        future_access[obj][contador_acessos[obj]] = i;
        //Atualizando a variável que quanta a quantidade de acessos que um objeto teve
        contador_acessos[obj]++;
    }
}

//Fila de prioridade: Essa função tem o objetivo de determinar qual objeto dentro do cache deve ser removido quando o cache estiver cheio e for necessário inserir um novo objeto
int encontrar_objeto_para_remover(int cache[], int cache_count, int next_access[]) {
    //Prioridade: o objeto que será acessado mais tarde no futuro (ou que não será mais acessado) deve ser removido
    
    int objeto_a_ser_removido = -1;
    int maior_distancia = -1;

    for (int j = 0; j < cache_count; j++) {
        if (next_access[cache[j]] > maior_distancia) {
            maior_distancia = next_access[cache[j]];
            objeto_a_ser_removido = j;
        }
    }
    return objeto_a_ser_removido;
}


//Função gerencia quais objetos serão mantidos no cache e quando será necessário remover um objeto para liberar espaço para um novo
int cache(int cache_size, int num_objects, int sequence[], int length) {
    //Quantas vezes um objeto que não estava no cache teve que ser adicionado
    int insercoes = 0;

    int *cache = (int *)malloc(cache_size * sizeof(int));
    //Este array contém os objetos que estão atualmente armazenados no cache

    int cache_count = 0;
    //O número de objetos presentes no cache no momento, ou seja, menor ou igual ao tamanho máximo do cache

    int *next_access = next_access_initialize(num_objects, length);
    //Esse array contém o próximo acesso de cada objeto

    int **future_access = future_access_initialize(num_objects, length);
    //Aloca e inicializa uma matriz acessos_futuros para armazenar todas as posições futuras onde cada objeto será acessado

    int *contador_acessos = (int *)calloc(num_objects, sizeof(int));
    //Quantas vezes já encontramos um objeto ao processar a sequência de trás para frente => determinar o próximo acesso futuro de cada objeto

    calcular_proximos_acessos(sequence, length, future_access, contador_acessos, num_objects);


    //Fazer Cache
    for (int i = 0; i < length; i++) {
        int current_object = sequence[i];

        // Atualiza o próximo acesso
        if (contador_acessos[current_object] > 0) {
            contador_acessos[current_object]--;
        }


        if (contador_acessos[current_object] == 0) {
            next_access[current_object] = length; // Se não houver mais acessos futuros, define como fora do intervalo.
        }       
        else {
            next_access[current_object] = future_access[current_object][contador_acessos[current_object] - 1]; // Se o contador de acessos futuros for maior que 0, isso significa que ainda existem acessos futuros para esse objeto => acessa o próximo acesso futuro
        }

        //Verifica se o current_object já está no cache
        int found_in_cache = 0;
        for (int j = 0; j < cache_count; j++) { // Ele percorre o array cache até encontrar o objeto
            if (cache[j] == current_object) {
                found_in_cache = 1;
                break;
            }
        }

        //Se o objeto não estiver no cache => Inseri-lo
        if (!found_in_cache) {
                if (cache_count >= cache_size) { //Se o cache estiver cheio
                    //Decidir qual objeto remover
                    int objeto_para_remover = encontrar_objeto_para_remover(cache, cache_count, next_access);
                    
                    //Objeto escolhido é removido => todos os objetos são movidos para preencher o espaço vazio
                    for (int j = objeto_para_remover; j < cache_count - 1; j++) {
                        cache[j] = cache[j + 1];
                    }
                    cache_count--;
                }
                //O objeto current_object é inserido no cache
                cache[cache_count++] = current_object;
                insercoes++;
            }
        }

        free(cache);
        free(next_access);
        future_access_free(future_access, num_objects);
        free(contador_acessos);

        return insercoes;
    
}

int main() {
    int cache_size, num_objects, sequence_length;

    scanf("%d %d %d", &cache_size, &num_objects, &sequence_length);

    int *sequence = (int *)malloc(sequence_length * sizeof(int));

    for (int i = 0; i < sequence_length; i++) {
        scanf("%d", &sequence[i]);
    }

    int result = cache(cache_size, num_objects, sequence, sequence_length);
    printf("%d\n", result);

    free(sequence);

    return 0;
}
