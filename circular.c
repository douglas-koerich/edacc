#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

// Declaracao da variavel global de elemento invalido
const tipo INVALIDO = -1;

// Definicao interna do no de lista, nao visivel para usuario da lista
struct No {
    tipo elemento;
    struct No* proximo;
};
typedef struct No No;

// Definicao pratica da lista encadeada
struct Lista {
    No* cauda;
};

Lista* cria(void) {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->cauda = NULL;
    return l;
}

void destroi(Lista* l) {
    if (l == NULL) {
        return;
    }
    while (!underflow(l)) {
        removeInicio(l);
    }
    free(l);
}

bool underflow(const Lista* l) {
    if (l == NULL) return true;
    return l->cauda == NULL;
}

void insereInicio(Lista* l, tipo novo) {
    if (l == NULL) {
        return;
    }
    No* n = (No*) malloc(sizeof(No));
    n->elemento = novo;
    if (l->cauda == NULL) {
        l->cauda = n;
    }
    else {
        n->proximo = l->cauda->proximo;
    }
    l->cauda->proximo = n;
}

tipo removeInicio(Lista* l) {
    if (l == NULL || underflow(l)) {
        return INVALIDO;
    }
    No* c = l->cauda->proximo;
    l->cauda->proximo = c->proximo;
    if (c == c->proximo) {  // soh existe este noh na lista circular
        l->cauda = NULL;
    }
    tipo t = c->elemento;
    free(c);
    return t;
}

size_t tamanho(const Lista* l) {
    if (l == NULL || underflow(l)) {
        return 0;
    }
    size_t contador = 0;
    No* n = l->cauda;
    do {
        ++contador;
        n = n->proximo;
    } while (n != l->cauda);
    return contador;
}
