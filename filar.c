#include <stdlib.h>
#include "filar.h"

struct Noh {
    R elemento;
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Fila {
    Noh* inicio;
    Noh* fim;
};

Fila* cria(void) {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

void destroi(Fila* f) {
    if (f == NULL) {
        return;
    }
    while (!underflow(f)) {
        dequeue(f);
    }
    free(f);
}

bool underflow(const Fila* f) {
    return f == NULL || f->inicio == NULL;
}

void enqueue(Fila* f, R r) {
    if (f == NULL) {
        return;
    }
    Noh* n = (Noh*) malloc(sizeof(Noh));
    memcpy(&n->elemento, &r, sizeof(R));
    n->proximo = NULL;
    if (f->fim != NULL) {
        f->fim->proximo = n;
    } else {
        f->inicio = n;
    }
    f->fim = n;
}

R dequeue(Fila* f) {
    if (underflow(f)) {
        R inv = { -1 };
        return inv;
    }
    Noh* x = f->inicio;
    f->inicio = x->proximo;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    R r;
    memcpy(&r, &x->elemento, sizeof(R));
    free(x);
    return r;
}
