#include <stdlib.h>
#include <stdio.h>

/* Comecando pela extremidade final do vetor (maiores):
void selecao(int* v, size_t n) {
    int i;
    for (i = n-1; i > 0; --i) {
        int m = i; // m guarda o indice do maior elemento
        int j;
        for (j = i-1; j >= 0; --j) {
            if (v[j] > v[m]) {
                m = j; // atualiza o indice do maior
            }
        }
        int x = v[i];
        v[i] = v[m];
        v[m] = x;
        // EXTRA: imprime o vetor para acompanhar o algoritmo
        printf("%zdo. passo:\n", n-i);
        for (j = 0; j < n; ++j) {
            printf("%d ", v[j]);
        }
        putchar('\n');
    }
}
*/

/* Comecando pela extremidade inicial do vetor (menores): */
void selecao(int* v, size_t n) {
    int i;
    for (i = 0; i < n-1; ++i) {
        int m = i; // m guarda o indice do menor elemento
        int j;
        for (j = i+1; j < n; ++j) {
            if (v[j] < v[m]) {
                m = j; // atualiza o indice do menor
            }
        }
        int x = v[i];
        v[i] = v[m];
        v[m] = x;
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
