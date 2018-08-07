#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila_reg.h"

struct Fila_reg {
    Registro* vetor;
    int inicio, fim;
};

Fila_reg* cria(void) {
    Fila_reg* f = (Fila_reg*) malloc(sizeof(Fila_reg));
    f->vetor = (Registro*) malloc(MAX_ELEMENTOS * sizeof(Registro));
    f->inicio = f->fim = MAX_ELEMENTOS - 1;
    return f;
}

void destroi(Fila_reg* f) {
    free(f->vetor);
    free(f);
}

bool underflow(const Fila_reg* f) {
    return f->inicio == f->fim;
}

bool overflow(const Fila_reg* f) {
    if (f->inicio == 0) {
        return f->fim == MAX_ELEMENTOS - 1;
    }
    else {
        return f->fim == f->inicio - 1;
    }
}

void enqueue(Fila_reg* f, const Registro* r) {
    if (f->fim == MAX_ELEMENTOS - 1) {
        f->fim = 0;
    }
    else {
        ++f->fim;
    }
    memcpy(&f->vetor[f->fim], r, sizeof(Registro));
}

Registro* dequeue(Fila_reg* f) {
    if (f->inicio == MAX_ELEMENTOS - 1) {
        f->inicio = 0;
    }
    else {
        ++f->inicio;
    }
    return &f->vetor[f->inicio];
}
