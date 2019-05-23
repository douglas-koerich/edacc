#include "busca.h"

int busca(R vetor[], int inf, int sup, unsigned chave) {
    if (inf > sup) {
        return INVALIDO;
    }
    int meio = (inf + sup) / 2;
    if (vetor[meio].chave == chave) {
        return meio;
    }
    if (chave < vetor[meio].chave) {
        return busca(vetor, inf, meio-1, chave);
    } else {
        return busca(vetor, meio+1, sup, chave);
    }
}

