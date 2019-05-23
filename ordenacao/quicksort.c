#include "ordenacao_r.h"

void ordena(R vetor[], int inf, int sup) {
    if (inf >= sup) {
        return;
    }
    unsigned chave_pivo = vetor[(inf+sup)/2].chave;
    int esq = inf, dir = sup;
    while (esq <= dir) {
        while (vetor[esq].chave < chave_pivo) ++esq;
        while (vetor[dir].chave > chave_pivo) --dir;
        if (esq <= dir) {
            TROCA(vetor+esq, vetor+dir);
            ++esq, --dir;
        }
    }
    ordena(vetor, inf, dir);
    ordena(vetor, esq, sup);
}

