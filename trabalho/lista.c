#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct Noh {
    const Item* item;
    struct Noh* proximo;
    struct Noh* anterior;
};

struct Lista {
    struct Noh* cabeca;
    struct Noh* cauda;
    size_t itens;
};

struct Lista* cria(void) {
    struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
    l->cabeca = l->cauda = NULL;
    l->itens = 0;
    return l;
}

void destroi(struct Lista* l) {
    if (l == NULL) {
        return;
    }
    while (!underflow(l)) {
        removeInicio(l);
    }
    free(l);
}

bool underflow(const struct Lista* l) {
    if (l == NULL) {
        return true;
    }
    return l->itens == 0;
}

void insereInicio(struct Lista* l, const Item* novo) {
    if (l == NULL) {
        return;
    }
    struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
    n->item = novo;
    n->proximo = l->cabeca;
    l->cabeca = n;
    n->anterior = NULL;
    if (n->proximo != NULL) {
        n->proximo->anterior = n;
    }
    if (l->cauda == NULL) {
        l->cauda = n;
    }
    ++l->itens;
}

void insereFim(struct Lista* l, const Item* novo) {
    if (l == NULL) {
        return;
    }
    struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
    n->item = novo;
    n->proximo = NULL;
    if (underflow(l)) {
        n->anterior = NULL;
        l->cabeca = n;
    }
    else {
        n->anterior = l->cauda;
        l->cauda->proximo = n;
    }
    l->cauda = n;
    ++l->itens;
}

void insereOrdem(struct Lista* l, const Item* novo) {
    if (l == NULL) {
        return;
    }
    struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
    n->item = novo;
    struct Noh* p = l->cabeca;
    struct Noh* ant = NULL;
    while (p != NULL && strcmp(p->item->nome, n->item->nome) < 0) {
        ant = p;
        p = p->proximo;
    }
    if (ant == NULL) {
        n->proximo = l->cabeca;
        l->cabeca = n;
    }
    else {
        n->proximo = ant->proximo;
        ant->proximo = n;
    }
    n->anterior = ant;
    if (n->proximo != NULL) {
        n->proximo->anterior = n;
    }
    if (l->cauda == ant) {
        l->cauda = n;
    }
    ++l->itens;
}

const Item* removeInicio(struct Lista* l) {
    if (l == NULL || underflow(l)) {
        return NULL;
    }
    struct Noh* x = l->cabeca;
    l->cabeca = x->proximo;
    if (l->cabeca != NULL) {
        l->cabeca->anterior = NULL;
    }
    else {
        l->cauda = NULL;
    }
    --l->itens;
    const Item* i = x->item;
    free(x);
    return i;
}

const Item* removeFim(struct Lista* l) {
    if (l == NULL || underflow(l)) {
        return NULL;
    }
    struct Noh* x = l->cauda;
    l->cauda = l->cauda->anterior;
    if (l->cauda == NULL) {
        l->cabeca = NULL;
    }
    else {
        l->cauda->proximo = NULL;
    }
    --l->itens;
    const Item* i = x->item;
    free(x);
    return i;
}

const Item* removeRegistro(struct Lista* l, const char* chave_busca) {
    if (l == NULL || underflow(l)) {
        return NULL;
    }
    struct Noh* x = l->cabeca;
    while (x != NULL && strcmp(x->item->nome, chave_busca)) {
        x = x->proximo;
    }
    if (x == NULL) {
        return NULL;
    }
    if (x->anterior != NULL) {
        x->anterior->proximo = x->proximo;
        if (x->anterior->proximo == NULL) {
            l->cauda = x->anterior;
        }
    }
    else {
        l->cabeca = x->proximo;
        if (l->cabeca == NULL) {
            l->cauda = NULL;
        }
    }
    if (x->proximo != NULL) {
        x->proximo->anterior = x->anterior;
    }
    --l->itens;
    const Item* i = x->item;
    free(x);
    return i;
}

const Item* busca(struct Lista* l, const char* chave_busca) {
    if (underflow(l)) {
        return NULL;
    }
    struct Noh* p = l->cabeca;
    while (p != NULL) {
        if (strcmp(p->item->nome, chave_busca) == 0) {
            return p->item;
        }
        p = p->proximo;
    }
    return NULL;
}
