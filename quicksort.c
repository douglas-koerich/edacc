#include <stdio.h>

void quick(int* v, int p, int u) {
    if (p >= u) {
        return;
    }
    int pivo = v[(p + u) / 2]; // escolhe como pivo o elemento do meio
    int j = p, k = u;
    while (j <= k) {
        while (v[j] < pivo) ++j;
        while (v[k] > pivo) --k;
        if (j <= k) {
            int x = v[j];
            v[j++] = v[k];
            v[k--] = x;
        }
    }
    /*
    // EXTRA: Imprime o pivo e a situacao do vetor ateh entao
    int i;
    for (i = p; i <= u; ++i) {
        printf("%d ", v[i]);
    }
    putchar('\n');
    */
    quick(v, p, k);
    quick(v, j, u);
}