#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

static const size_t MAX_FILA = 100;
struct Fila {
    Registro* vetor;
    int inicio, fim;
};

Fila* cria(void) {
    Fila* nova = malloc(sizeof(Fila));
    nova->vetor = malloc(sizeof(Registro) * MAX_FILA);
    nova->inicio = nova->fim = MAX_FILA-1;
    return nova;
}

void destroi(Fila* fila) {
    free(fila->vetor);
    free(fila);
}


bool underflow(const Fila* fila) {
    return fila->inicio == fila->fim;
}

bool overflow(const Fila* fila) {
    if (fila->inicio == 0) {
        return fila->fim == MAX_FILA-1;
    }
    return fila->fim == fila->inicio-1;
}

void enqueue(Fila* fila, const Registro* reg) {
    if (fila->fim == MAX_FILA-1) {
        fila->fim = -1;
    }
    fila->vetor[++fila->fim] = *reg; // poderia ser memcpy
}

const Registro* dequeue(Fila* fila) {
    if (fila->inicio == MAX_FILA-1) {
        fila->inicio = -1;
    }
    return &fila->vetor[++fila->inicio];
}

