#include <stdlib.h>
#include "fila.h"

struct Noh {
    const char* elemento;
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Fila {
    Noh* inicio;
    Noh* fim;
};

Fila* cria_fila(void) {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

void destroi_fila(Fila* f) {
    if (f == NULL) {
        return;
    }
    while (!fila_vazia(f)) {
        dequeue(f);
    }
    free(f);
}

bool fila_vazia(const Fila* f) {
    return f == NULL || f->inicio == NULL;
}

void enqueue(Fila* f, const char* s) {
    if (f == NULL) {
        return;
    }
    Noh* n = (Noh*) malloc(sizeof(Noh));
    n->elemento = s;
    n->proximo = NULL;
    if (f->fim != NULL) {
        f->fim->proximo = n;
    } else {
        f->inicio = n;
    }
    f->fim = n;
}

const char* dequeue(Fila* f) {
    if (fila_vazia(f)) {
        return NULL;
    }
    Noh* x = f->inicio;
    f->inicio = x->proximo;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    const char* s = x->elemento;
    free(x);
    return s;
}
