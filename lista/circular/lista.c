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
    struct Noh* cauda;
};

struct Lista* cria(void) {
    struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
    l->cauda = NULL;
    return l;
}

void destroi(struct Lista* l) {
    while (!underflow(l)) {
        removeInicio(l);
    }
    free(l);
}

bool underflow(const struct Lista* l) {
    return l->cauda == NULL;
}

void insereInicio(struct Lista* l, const Reg* novo) {
    struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
    n->elemento = *novo;
    if (underflow(l)) {
        n->proximo = l->cauda = n;
        return;
    }
    n->proximo = l->cauda->proximo;
    l->cauda->proximo = n;
}

void insereFim(struct Lista* l, const Reg* novo) {
    struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
    n->elemento = *novo;
    if (underflow(l)) {
        n->proximo = l->cauda = n;
        return;
    }
    struct Noh* p = l->cauda;
    n->proximo = l->cauda->proximo;
    l->cauda->proximo = n;
    l->cauda = n;
}

void insereOrdem(struct Lista* l, const Reg* novo) {
    struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
    n->elemento = *novo;
    if (underflow(l)) {
        n->proximo = l->cauda = n;
        return;
    }
    struct Noh* p = l->cauda;
    struct Noh* ant;
    do {
        ant = p;
        p = p->proximo;
        if (p->elemento.chave >= n->elemento.chave) {
            break;
        }
    } while (p != l->cauda);
    if (p->elemento.chave >= n->elemento.chave) {
        n->proximo = ant->proximo;
        ant->proximo = n;
    }
    else {
        n->proximo = l->cauda->proximo;
        l->cauda->proximo = n;
        l->cauda = n;
    }
}

Reg removeInicio(struct Lista* l) {
    if (underflow(l)) {
        return REG_INVALIDO;
    }
    struct Noh* x = l->cauda->proximo;
    if (x == l->cauda) {
        l->cauda = NULL;
    }
    else {
        l->cauda->proximo = x->proximo;
    }
    Reg r = x->elemento;
    free(x);
    return r;
}

Reg removeFim(struct Lista* l) {
    if (underflow(l)) {
        return REG_INVALIDO;
    }
    struct Noh* x = l->cauda;
    struct Noh* ant;
    do {
        ant = x;
        x = x->proximo;
    } while (x != l->cauda);
    if (ant == x) {
        l->cauda = NULL;
    }
    else {
        l->cauda = ant;
        l->cauda->proximo = x->proximo;
    }
    Reg r = x->elemento;
    free(x);
    return r;
}

Reg removeRegistro(struct Lista* l, int chave_busca) {
    if (underflow(l)) {
        return REG_INVALIDO;
    }
    struct Noh* x = l->cauda;
    struct Noh* ant;
    do {
        ant = x;
        x = x->proximo;
        if (x->elemento.chave == chave_busca) {
            break;
        }
    } while (x != l->cauda);
    if (x->elemento.chave != chave_busca) {
        return REG_INVALIDO;
    }
    if (ant == x) {
        l->cauda = NULL;
    }
    else {
        ant->proximo = x->proximo;
        if (x == l->cauda) {
            l->cauda = ant;
        }
    }
    Reg r = x->elemento;
    free(x);
    return r;
}

const Reg* busca(struct Lista* l, int chave_busca) {
    if (underflow(l)) {
        return NULL;
    }
    struct Noh* p = l->cauda;
    do {
        p = p->proximo;
        if (p->elemento.chave == chave_busca) {
            return &p->elemento;
        }
    } while (p != l->cauda);
    return NULL;
}

void imprime(struct Lista* l) {
    if (underflow(l)) {
        printf("(vazia)");
        return;
    }
    printf("(Cabeca)-->");
    struct Noh* p = l->cauda;
    do {
        p = p->proximo;
        printf("{%d,%d}@%p-->", p->elemento.chave, p->elemento.valor, p);
    } while (p != l->cauda);
    printf("(Cauda)");
}

bool compara(const struct Lista* l1, const struct Lista* l2) {
    if (underflow(l1)) {
        return underflow(l2);
    }
    else {
        if (underflow(l2)) return false;
        else {
            struct Noh* p1 = l1->cauda;
            struct Noh* p2 = l2->cauda;
            do {
                p1 = p1->proximo;
                p2 = p2->proximo;
                if (memcmp(&p1->elemento, &p2->elemento, sizeof(Reg)) != 0) {
                    return false;
                }
            } while (p1 != l1->cauda && p2 != l2->cauda);
            if (p1 == l1->cauda) {
                return p2 == l2->cauda;
            }
            else {
                return false;
            }
        }
    }
}

