#include <stdlib.h>
#include <string.h>
#include "registro.h"

void mergesort(R vetor[], int inf, int sup) {
    if (inf >= sup) {
        return;
    }
    int meio = (inf + sup) / 2;
    mergesort(vetor, inf, meio);
    mergesort(vetor, meio+1, sup);
    R* copia = malloc(sizeof(R) * (sup-inf+1));
    int esq = inf, dir = meio+1, cop = 0;
    while (esq <= meio && dir <= sup) {
        if (vetor[esq].chave < vetor[dir].chave) {
            memcpy(copia+cop, vetor+esq, sizeof(R));
            ++esq;
        } else {
            memcpy(copia+cop, vetor+dir, sizeof(R));
            ++dir;
        }
        ++cop;
    }
    while (esq <= meio) {
        memcpy(copia+cop, vetor+esq, sizeof(R));
        ++esq, ++cop;
    }
    while (dir <= sup) {
        memcpy(copia+cop, vetor+dir, sizeof(R));
        ++dir, ++cop;
    }
    memcpy(vetor+inf, copia, sizeof(R) * (sup-inf+1));
    free(copia);
}

