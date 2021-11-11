#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void merge(int* v, int p, int u) {
    // EXTRA: imprime o segmento do vetor antes das chamadas recursivas
    int j;
    for (j = p; j <= u; ++j) {
        printf("%d ", v[j]);
    }
    putchar('\n');
    
    if (p == u) { // vetor de tamanho unitario
        return;   // (primeiro indice = ultimo indice)
    }
    int m = (p + u) / 2;
    merge(v, p, m);     // ordena metade inferior
    merge(v, m+1, u);   // ordena metade superior

    // Eh necessario intercalar as duas metades jah ordenadas
    size_t n = (u - p + 1);
    int* w = malloc(sizeof(int) * n);

    int e = p, d = m+1, i = 0;
    while (e <= m && d <= u) { // enquanto ha dois valores a comparar
        if (v[e] < v[d]) {
            w[i++] = v[e++];
        } else {
            w[i++] = v[d++];
        }
    }
    while (e <= m) { // no caso da metade inferior nao ter sido finalizada
        w[i++] = v[e++];
    }
    while (d <= u) { // no caso da metade superior nao ter sido finalizada
        w[i++] = v[d++];
    }
    memcpy(&v[p], w, sizeof(int) * n);
    free(w);

    // EXTRA: imprime o segmento do vetor depois da intercalacao
    for (j = p; j <= u; ++j) {
        printf("%d ", v[j]);
    }
    putchar('\n');
}