#include <stdlib.h>
#include "filai.h"

struct Noh {
    int valor;
    struct Noh* proximo;
};

struct FilaI {
    struct Noh* inicio;
    struct Noh* fim;
};

struct FilaI* cria(void) {
    struct FilaI* f = (struct FilaI*) malloc(sizeof(struct FilaI));
    f->inicio = f->fim = NULL;
    return f;
}

void destroi(struct FilaI* f) {
    while (!underflow(f)) {
        dequeue(f);
    }
}

bool underflow(const struct FilaI* f) {
    return f->inicio == NULL;
}

void enqueue(struct FilaI* f, int num) {
    struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
    n->valor = num;
    n->proximo = NULL;
    if (f->fim == NULL) {
        f->inicio = n;
    }
    else {
        f->fim->proximo = n;
    }
    f->fim = n;
}

int dequeue(struct FilaI* f) {
    int num = f->inicio->valor;
    struct Noh* x = f->inicio;
    f->inicio = f->inicio->proximo;
    if (f->inicio  == NULL) {
        f->fim = NULL;
    }
    free(x);
    return num;
}

