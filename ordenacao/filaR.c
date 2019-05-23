#include <stdio.h>
#include <string.h>
#include "filaR.h"

struct fila {
    R* vetor;
    int inicio, fim;
    size_t tamanho;
};

Fila* cria(size_t tamanho) {
    Fila* f = malloc(sizeof(struct fila));
    ++tamanho;
    f->vetor = malloc(tamanho * sizeof(R));
    f->inicio = f->fim = tamanho-1;
    f->tamanho = tamanho;
    return f;
}

bool underflow(const Fila* f) {
    return f->inicio == f->fim;
}

bool overflow(const Fila* f) {
    if (f->inicio == 0) {
        return f->fim == f->tamanho - 1;
    } else {
        return f->fim == f->inicio - 1;
    }
}

void destroi(Fila* f) {
    free(f->vetor);
    free(f);
}

void enqueue(Fila* f, const R* v) {
    if (overflow(f)) {
        fprintf(stderr, "Fila cheia!\n");
        return;
    }
    if (f->fim == f->tamanho-1) {
        f->fim = 0;
    } else {
        ++f->fim;
    }
    memcpy(&f->vetor[f->fim], v, sizeof(R));
}

void dequeue(Fila* f, R* v) {
    if (underflow(f)) {
        fprintf(stderr, "Fila vazia, IGNORE *v!\n");
        return;
    }
    if (f->inicio == f->tamanho-1) {
        f->inicio = 0;
    } else {
        ++f->inicio;
    }
    memcpy(v, &f->vetor[f->inicio], sizeof(R));
}

