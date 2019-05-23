#include "ordenacao.h"

void ordena(R vetor[], size_t n) {
    int j;
    for (j = 1; j <= n; ++j) { // deve passar pelo vetor o numero de vezes
                               // igual ao seu tamanho para garantir o pior caso
        int i;
        for (i = n-1; i > 0; --i) {
            if (vetor[i].chave < vetor[i-1].chave) { // fora de ordem numa
                                                     // classificacao CRESCENTE
                TROCA(vetor+i, vetor+i-1);
            }
        }
    }
}

