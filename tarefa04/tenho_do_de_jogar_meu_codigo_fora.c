void bat_free(int endereco, p_vector v) {
    int tamanho = v->dados[endereco];
    for (int i = 0; i <= tamanho; i++) {
        v->dados[endereco + i] = 0;
    }

    // Atualiza a quantidade de memória utilizada
    int nao_utilizados_final = 0;
    for (int i = 0; i < v->alocado; i--) {
        if (v->dados[i] == 0) {
            nao_utilizados_final++;
        }
    }

    // Verifica se pode reduzir o tamanho da memória
    if (v->alocado > MIN_VETOR && nao_utilizados_final > 3 * v->alocado / 4) {
        int *p_aux = v->dados;
        int novo_tamanho = v->alocado / 2;

        if (novo_tamanho < MIN_VETOR) novo_tamanho = MIN_VETOR;

        v->dados = malloc(novo_tamanho * sizeof(int));

        // Copia os dados antigos
        for (int i = 0; i < novo_tamanho; i++) {
            v->dados[i] = p_aux[i];
        }

        v->alocado = novo_tamanho;
        free(p_aux);
    }
}