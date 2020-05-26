#include <stdlib.h>
#include "registro.h"

void selecao(R vetor[], size_t n) {
    int i = 0;
    while (i < n) {
        int indice_menor = i, j;
        for (j = i+1; j < n; ++j) {
            if (vetor[j].chave < vetor[indice_menor].chave) {
                indice_menor = j;
            }
        }
        TROCA(vetor+i, vetor+indice_menor);
        ++i;
    }
}

