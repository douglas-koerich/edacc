#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ORDEM 3

bool busca(size_t N, int A[N][N], int x, int li, int ci, int ls, int cs);

int main(int argc, char* argv[]) {
    int A[][ORDEM] = {
        {   2,   5,  12 },
        {  19,  24,  37 },
        {  50,  73, 118 }
    };
    int n = 0;
    do {
        printf("Digite um valor para busca (0 para finalizar): ");
        scanf("%d", &n);
        bool achou = busca(ORDEM, A, n, 0, 0, ORDEM-1, ORDEM-1);
        printf("Numero %d %sfoi encontrado.\n", n, achou? "": "NAO ");
    } while (0 != n);
    return EXIT_SUCCESS;
}

bool busca(size_t N, int A[N][N], int x, int li, int ci, int ls, int cs) {
    if (li > ls || (li == ls && ci > cs)) {
        return false;
    }
    int mi = N*li + ci,
        ms = N*ls + cs,
        m = (mi + ms)/2;
    int lm = m / N, cm = m % N;
    if (x == A[lm][cm]) {
        return true;
    }
    if (x < A[lm][cm]) {
        if (0 == cm) { cm = N-1, --lm; }
        else --cm;
        return busca(N, A, x, li, ci, lm, cm);
    } else {
        if (N-1 == cm) { cm = 0, ++lm; }
        else ++cm;
        return busca(N, A, x, lm, cm, ls, cs);
    }
}
