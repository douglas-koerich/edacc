#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int maior_numero(const int*, size_t);
int maior_numero_v2(const int*, int, int);

#define TAM 15

int main(void) {
    int vetor[TAM];
    srand((unsigned) time(NULL));
    
    int i;
    for (i=0; i<TAM; ++i) {
        vetor[i] = rand() % 100;
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    int m = maior_numero(vetor, TAM);
    printf("O maior numero no vetor eh %d.\n", m);

    m = maior_numero_v2(vetor, 0, TAM-1);
    printf("Confirmando: o maior numero no vetor eh %d.\n", m);

    return EXIT_SUCCESS;
}

int maior_numero(const int* v, size_t t) {
    if (t == 1) {
        return *v;
    }
    size_t meio = t / 2;
    int maior_esq = maior_numero(v, meio);
    int maior_dir = maior_numero(v+meio, t-meio);
    return maior_esq > maior_dir? maior_esq: maior_dir;
}

int maior_numero_v2(const int* v, int e, int d) {
    if (e == d) {
        return *(v + e); // valor de v[e]
    }
    size_t meio = (e + d) / 2;
    int maior_esq = maior_numero_v2(v, e, meio);
    int maior_dir = maior_numero_v2(v, meio+1, d);
    return maior_esq > maior_dir? maior_esq: maior_dir;
}

