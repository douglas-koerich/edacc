unsigned conta_ocorrencias(const Reg vetor[], int inf, int sup, unsigned chave) {
    if (inf > sup) {
        return 0; // nenhuma ocorrencia
    }
    int meio = (inf + sup) / 2;
    if (vetor[meio].chave == chave) {
        unsigned contador = 1;
        int i;
        // Executa um laco percorrendo o vetor a partir do meio para
        // tras contando aquelas posicoes que tambem tem essa mesma chave
        for (i = meio-1; i >= inf && vetor[i].chave == chave; --i) {
            ++contador;
        }
        // Faz o mesmo para frente...
        for (i = meio+1; i <= sup && vetor[i].chave == chave; ++i) {
            ++contador;
        }
        return contador;
    }
    if (chave < vetor[meio].chave) {
        // Continua busca de forma recursiva pela metade inferior
        return binaria(vetor, inf, meio-1, chave); // nao inclui 'meio'
    } else {
        return binaria(vetor, meio+1, sup, chave); // na metade superior...
    }
}

