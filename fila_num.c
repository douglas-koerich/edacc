#include <stdlib.h>
#include <stdio.h>
#include "fila_num.h"

struct Fila_num {
    unsigned* vetor;    // a ser alocado dinamicamente
    int inicio, fim;
};

Fila_num* cria(void) {
    Fila_num* f = (Fila_num*) malloc(sizeof(Fila_num));
    f->vetor = (unsigned*) malloc(MAX_ELEMENTOS * sizeof(unsigned));
    f->inicio = f->fim = MAX_ELEMENTOS - 1;
    return f;
}

void destroi(Fila_num* f) {
    free(f->vetor); // se inverte essas linhas entre si, perde o ponteiro para o vetor!
    free(f);
}

bool underflow(const Fila_num* f) {
    return f->inicio == f->fim;
}

bool overflow(const Fila_num* f) {
    if (f->inicio == 0) {
        return f->fim == MAX_ELEMENTOS - 1;
    }
    else {
        return f->fim == f->inicio - 1;
    }
}

void enqueue(Fila_num* f, unsigned n) {
    if (f->fim == MAX_ELEMENTOS - 1) {
        f->fim = 0;
    }
    else {
        ++f->fim;
    }
    f->vetor[f->fim] = n;
}

unsigned dequeue(Fila_num* f) {
    if (f->inicio == MAX_ELEMENTOS - 1) {
        f->inicio = 0;
    }
    else {
        ++f->inicio;
    }
    return f->vetor[f->inicio];
}

// Bonus: impressao da fila
void imprime(const Fila_num* f) {
    int i = f->inicio;
    while (i != f->fim) {
        i = (i == MAX_ELEMENTOS - 1)? 0: i+1;
        printf("%u ", f->vetor[i]);
    }
    putchar('\n');
}
