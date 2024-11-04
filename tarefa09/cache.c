#include "cache.h"
#include <stdio.h>

int main() {
    int cache_size, num_objects, sequence_length;

    scanf("%d %d %d", &cache_size, &num_objects, &sequence_length);

    //Array contendo a sequência de acessos aos objetos
    int *sequence = (int *)malloc(sequence_length * sizeof(int));

    for (int i = 0; i < sequence_length; i++) {
        scanf("%d", &sequence[i]);
    }

    int result = cache(cache_size, num_objects, sequence, sequence_length);
    printf("%d\n", result);

    free(sequence);

    return 0;
}