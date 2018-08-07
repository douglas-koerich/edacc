#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

// Declaracao da variavel global de registro invalido
const Reg REG_INVALIDO = { -1, 0 };

// Definicao interna do no de lista, nao visivel para usuario da lista
struct Noh {
    Reg elemento;
    struct Noh* proximo;
};

// Definicao pratica da lista encadeada
struct Lista {
    struct Noh* cabeca;
    struct Noh* cauda;
    unsigned tamanho;
};

struct Lista* cria(void) {
    struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
    l->cabeca = l->cauda = NULL;
    l->tamanho = 0;
    return l;
}

void destroi(struct Lista* l) {
    while (!underflow(l)) {
        removeInicio(l);
    }
    free(l);
}

bool underflow(const struct Lista* l) {
    return l->tamanho == 0;
}

void insereInicio(struct Lista* l, const Reg* novo) {
    struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
    n->elemento = *novo;
    n->proximo = l->cabeca;
    l->cabeca = n;
    if (l->cauda == NULL) {
        l->cauda = n;
    }
    ++l->tamanho;
}

void insereFim(struct Lista* l, const Reg* novo) {
    struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
    n->elemento = *novo;
    n->proximo = NULL;
    if (underflow(l)) {
        l->cabeca = n;
    }
    else {
        l->cauda->proximo = n;
    }
    l->cauda = n;
    ++l->tamanho;
}

void insereOrdem(struct Lista* l, const Reg* novo) {
    struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
    n->elemento = *novo;
    struct Noh* p = l->cabeca;
    struct Noh* ant = NULL;
    while (p != NULL && p->elemento.chave < n->elemento.chave) {
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
    if (l->cauda == ant) {
        l->cauda = n;
    }
    ++l->tamanho;
}

Reg removeInicio(struct Lista* l) {
    if (underflow(l)) {
        return REG_INVALIDO;
    }
    struct Noh* x = l->cabeca;
    l->cabeca = x->proximo;
    if (l->cabeca == NULL) {
        l->cauda = NULL;
    }
    --l->tamanho;
    Reg r = x->elemento;
    free(x);
    return r;
}

Reg removeFim(struct Lista* l) {
    if (underflow(l)) {
        return REG_INVALIDO;
    }
    struct Noh* x = l->cabeca;
    struct Noh* ant = NULL;
    while (x != l->cauda) {
        ant = x;
        x = x->proximo;
    }
    l->cauda = ant;
    if (l->cauda == NULL) {
        l->cabeca = NULL;
    }
    else {
        l->cauda->proximo = NULL;
    }
    --l->tamanho;
    Reg r = x->elemento;
    free(x);
    return r;
}

Reg removeRegistro(struct Lista* l, int chave_busca) {
    struct Noh* x = l->cabeca;
    struct Noh* ant = NULL;
    while (x != NULL && x->elemento.chave != chave_busca) {
        ant = x;
        x = x->proximo;
    }
    if (x == NULL) {
        return REG_INVALIDO;
    }
    if (ant != NULL) {
        ant->proximo = x->proximo;
        if (ant->proximo == NULL) {
            l->cauda = ant;
        }
    }
    else {
        l->cabeca = x->proximo;
        if (l->cabeca == NULL) {
            l->cauda = NULL;
        }
    }
    --l->tamanho;
    Reg r = x->elemento;
    free(x);
    return r;
}

const Reg* busca(struct Lista* l, int chave_busca) {
    if (underflow(l)) {
        return NULL;
    }
    struct Noh* p = l->cabeca;
    while (p != NULL) {
        if (p->elemento.chave == chave_busca) {
            return &p->elemento;
        }
        p = p->proximo;
    }
    return NULL;
}

void imprime(struct Lista* l) {
    if (underflow(l)) {
        printf("(vazia)");
        return;
    }
    printf("(Cabeca) ");
    struct Noh* p = l->cabeca;
    while (p != NULL) {
        printf("{%d,%d}@%p--", p->elemento.chave, p->elemento.valor, p);
        if (p->proximo != NULL) {
            putchar('>');
        }
        p = p->proximo;
    }
    printf("|| (Cauda)");
}

bool compara(const struct Lista* l1, const struct Lista* l2) {
    if (underflow(l1)) {
        return underflow(l2);
    }
    else {
        if (underflow(l2)) return false;
        else {
            struct Noh* p1 = l1->cabeca;
            struct Noh* p2 = l2->cabeca;
            while (p1 != NULL && p2 != NULL) {
                if (memcmp(&p1->elemento, &p2->elemento, sizeof(Reg)) != 0) {
                    return false;
                }
                p1 = p1->proximo;
                p2 = p2->proximo;
            }
            if (p1 == NULL) {
                return p2 == NULL;
            }
            else {
                return false;
            }
        }
    }
}
