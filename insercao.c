#include <stdlib.h>
#include <stdio.h>

void insercao(int* v, size_t n) {
    int i;
    for (i = 1; i < n; ++i) {
        int r = v[i]; // salva o valor da posicao de partida como referencia
        int j;
        for (j = i-1; j >= 0 && v[j] > r; --j) {
            v[j+1] = v[j]; // "empurra" o valor maior para a posicao seguinte
                           // abrindo espaco para o elemento de referencia
        }
        v[j+1] = r;
        /*
        // EXTRA: imprime o vetor para acompanhar o algoritmo
        printf("%do. passo:\n", i+1);
        for (j = 0; j < n; ++j) {
            printf("%d ", v[j]);
        }
        putchar('\n');
        */
    }
}
