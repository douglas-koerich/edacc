void insercao(Reg vetor[], size_t n) {
    imprime_chaves(vetor, n);
    int posicao;
    // Comeca na segunda posicao do vetor pois a primeira nao
    // tem com quem ser comparada
    for (posicao = 1; posicao < n; ++posicao) {
        Reg* aux = malloc(sizeof(Reg));

        // Salva o registro original que vai ser reposicionado,
        // pois ele pode ser sobrescrito pelo deslocamento dos
        // outros
        memcpy(aux, vetor+posicao, sizeof(Reg));

        int posicao_anterior = posicao - 1;
        while (posicao_anterior >= 0 && // nao chegou no inicio E...
               vetor[posicao_anterior].chave > aux->chave) { // ... o anterior eh maior?
            memcpy(vetor+posicao_anterior+1, vetor+posicao_anterior,
                   sizeof(Reg)); // "empurra" o maior pra frente
            --posicao_anterior;
        }
        // Poe o elemento que estava sendo comparado na sua
        // posicao final
        memcpy(vetor+posicao_anterior+1, aux, sizeof(Reg));

        free(aux);
        imprime_chaves(vetor, n);
    }
}

