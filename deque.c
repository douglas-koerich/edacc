#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "deque.h"

struct deque {
    int* vetor;
    size_t tamanho;
    int inicio, fim;
};

deque* d_create(size_t max) {
    deque* nova = malloc(sizeof(deque));
    nova->vetor = malloc((max+1) * sizeof(int));
    nova->tamanho = max;
    nova->fim = nova->inicio = 0;
    return nova;
}

void d_destroy(deque* d) {
    if (d == NULL) {
        return;
    }
    free(d->vetor);
    free(d);
}

static bool overflow(const deque* d) { // teste de deque cheio
    return (d == NULL) ||
           (d->inicio == 0 && d->fim == d->tamanho) ||
           (d->inicio > 0 && d->fim == d->inicio - 1);
}

void d_insert(deque* d, int v, side s) {
    if (overflow(d) == true) {
        return;
    }
    if (s == REAR) {
        d->vetor[d->fim] = v;
        if (d->fim == d->tamanho) { // chegou no ultimo indice do vetor?
            d->fim = 0;
        } else {
            ++d->fim;
        }
    } else {
        if (d->inicio == 0) {
            d->inicio = d->tamanho;
        } else {
            --d->inicio;
        }
        d->vetor[d->inicio] = v;
    }
}

int d_extract(deque* d, side s) {
    if (d_underflow(d)) {
        return INT_MIN;
    }
    int v;
    if (s == FRONT) {
        v = d->vetor[d->inicio];
        if (d->inicio == d->tamanho) {
            d->inicio = 0;
        } else {
            ++d->inicio;
        }
    } else {
        if (d->fim == 0) {
            d->fim = d->tamanho;
        } else {
            --d->fim;
        }
        v = d->vetor[d->fim];
    }
    return v;
}

int d_inspect(const deque* d, side s) {
    if (d_underflow(d)) {
        return INT_MIN;
    }
    if (s == FRONT) {
        return d->vetor[d->inicio];
    } else {
        int f = d->fim == 0? d->tamanho: d->fim - 1;
        return d->vetor[f];
    }
}

size_t d_size(const deque* d) {
    int n = d->fim - d->inicio;
    if (n < 0) {
        n += d->tamanho + 1;
    }
    return n;
}

bool d_underflow(const deque* d) {
    return d == NULL || d->inicio == d->fim;
}

void d_print(const deque* d) {
    if (d == NULL) {
        return;
    }
    if (d_underflow(d)) {
        puts("(VAZIO)");
        return;
    }
    printf("INICIO> ");
    int i = d->inicio;
    while (i != d->fim) {
        printf("%d ", d->vetor[i]);
        if (++i == d->tamanho + 1) {
            i = 0;
        }
    }
    printf("<FIM");
}
