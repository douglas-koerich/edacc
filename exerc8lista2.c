#include <stdlib.h>
#include <stdio.h>
#include "pilhal.h"
#include "exerc8lista2.h"

struct Noh {
    int elemento;
    struct Noh* proximo;
};

struct Lista {
    struct Noh* cauda;
};

struct Lista* cria(void) {
    struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
    l->cauda = NULL;
    return l;
}

void destroi(struct Lista* l) {
    if (!underflow(l)) {
        struct Noh* cauda = l->cauda;
        while (l->cauda->proximo != cauda) {
            struct Noh* p = l->cauda;
            l->cauda = p->proximo;
            free(p);
        }
        free (l->cauda);
    }
    free(l);
}

bool underflow(const struct Lista* l) {
    return l->cauda == NULL;
}

void imprime(const struct Lista* l) {
    printf("(Inicio)->");
    if (!underflow(l)) {
        struct Noh* p = l->cauda;
        do {
            p = p->proximo;
            printf("%d->", p->elemento);
        } while (p != l->cauda);
    }
    printf("(Fim)\n");
}

bool inserirFim(struct Lista* l, int val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    if (l->cauda == NULL) {
        p->proximo = p;
    }
    else {
        struct Noh* cauda = l->cauda;
        struct Noh* cabeca = cauda->proximo;
        p->proximo = cabeca;
        cauda->proximo = p;
    }
    l->cauda = p;
    return true;
}

/**
 * SOLUCAO DO EXERCICIO
 */

void inverte(struct Lista* l) {
    if (underflow(l)) {
        return;
    }
    struct Pilha* aux = p_cria();

    struct Noh* p = l->cauda;
    do {
        p = p->proximo;
        push(aux, p->elemento);
        p_imprime(aux);
    } while (p != l->cauda);
    do {
        p = p->proximo;
        pop(aux, &p->elemento);
        p_imprime(aux);
    } while (p != l->cauda);

    p_destroi(aux);
}

