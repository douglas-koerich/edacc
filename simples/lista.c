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
    No* cabeca;
};

Lista* cria(void) {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->cabeca = NULL;
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
    return l->cabeca == NULL;
}

void insereInicio(Lista* l, tipo novo) {
    if (l == NULL) {
        return;
    }
    No* n = (No*) malloc(sizeof(No));
    n->elemento = novo;
    n->proximo = l->cabeca;
    l->cabeca = n;
}

tipo removeInicio(Lista* l) {
    if (l == NULL || underflow(l)) {
        return INVALIDO;
    }
    No* c = l->cabeca;
    l->cabeca = c->proximo;
    tipo t = c->elemento;
    free(c);
    return t;
}

unsigned numOcorrencias(const Lista* l, tipo valor) {
    if (l == NULL || underflow(l)) {
        return 0;
    }
    unsigned contador = 0;
    No* i = l->cabeca;
    while (i != NULL) {
        if (i->elemento == valor) {
            ++contador;
        }
        i = i->proximo;
    }
    return contador;
}
