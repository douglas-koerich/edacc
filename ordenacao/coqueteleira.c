#include "ordenacao.h"

void ordena(R vetor[], size_t n) {
    int j;
    for (j = 1; j <= n; ++j) { // deve passar pelo vetor o numero de vezes
                               // igual ao seu tamanho para garantir o pior caso
        int i;
        if (j % 2) { // passada impar
            for (i = n-1; i > 0; --i) {
                if (vetor[i].chave < vetor[i-1].chave) { // igual ah bolha
                    TROCA(vetor+i, vetor+i-1);
                }
            }
        } else { // passada par
            for (i = 0; i < n-1; ++i) {
                if (vetor[i].chave > vetor[i+1].chave) { // note a inversao
                    TROCA(vetor+i, vetor+i+1);
                }
            }
        }
    }
}

