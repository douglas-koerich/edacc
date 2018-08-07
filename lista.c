#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

struct No {
    registro elemento;
    struct No* proximo;
};
typedef struct No No;

struct lista {
    No* cabeca;
};

lista* cria(void) {
    lista* l = (lista*) malloc(sizeof(lista));
    l->cabeca = NULL;
    return l;
}

void destroi(lista* l) {
    if (l == NULL) {
        return;
    }
    while (!underflow(l)) {
        No* c = l->cabeca;
        l->cabeca = c->proximo;
        free(c);
    }
    free(l);
}

bool underflow(const lista* l) {
    if (l == NULL) return true;
    return l->cabeca == NULL;
}

void insere_atualiza(lista* l, const registro* r) {
    if (l == NULL) {
        return;
    }
    No* n = (No*) malloc(sizeof(No));
    memcpy(&n->elemento, r, sizeof(registro));
    n->proximo = NULL;
    if (underflow(l)) {
        l->cabeca = n;
        return;
    }
    No* o = l->cabeca;
    while (o->elemento.chave != r->chave && o->proximo != NULL) {
        o = o->proximo;
    }
    if (o->elemento.chave == r->chave) {
        free(n);
        memcpy(&o->elemento, r, sizeof(registro));
    } else {
        o->proximo = n;
    }
}

registro* busca(const lista* l, unsigned short x) {
    if (l == NULL || underflow(l)) {
        return NULL;
    }
    No* n = l->cabeca;
    while (n != NULL) {
        if (n->elemento.chave == x) {
            return &n->elemento;
        }
        n = n->proximo;
    }
    return NULL;
}

void imprime(const lista* l) {
    if (l == NULL || underflow(l)) {
        printf("(vazia)");
        return;
    }
    No* n = l->cabeca;
    while (n != NULL) {
        printf("-->[%hu]", n->elemento.chave);
        n = n->proximo;
    }
}
