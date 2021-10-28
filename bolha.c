#include <stdlib.h>
#include <stdio.h>

/* Versao "pedra" do algoritmo:
void ordena(int* v, size_t n) {
    int i;
    for (i = 1; i < n; ++i) {
        int j;
        printf("%da. varredura:\n", i);
        for (j = 0; j < n-i; ++j) {
            if (v[j] > v[j+1]) {
                int x = v[j];
                v[j] = v[j+1];
                v[j+1] = x;
            }
            // EXTRA: imprime o vetor para acompanhar o algoritmo
            int k;
            for (k = 0; k < n; ++k) {
                printf("%d ", v[k]);
            }
            putchar('\n');
        }
    }
}
*/

void ordena(int* v, size_t n) {
    int i;
    for (i = 1; i < n; ++i) {
        int j;
        printf("%da. varredura:\n", i);
        for (j = n-1; j >= i; --j) {
            if (v[j] < v[j-1]) {
                int x = v[j];
                v[j] = v[j-1];
                v[j-1] = x;
            }
            // EXTRA: imprime o vetor para acompanhar o algoritmo
            int k;
            for (k = 0; k < n; ++k) {
                printf("%d ", v[k]);
            }
            putchar('\n');
        }
    }
}
