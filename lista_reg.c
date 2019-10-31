#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista_reg.h"

struct Noh {
    Reg elemento;
    struct Noh* proximo;
    struct Noh* anterior;
};
typedef struct Noh Noh;

struct Lista {
    Noh* cabeca;
};

Lista* criar(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cabeca = NULL;
    return l;
}

void destruir(Lista* l) {
    if (l == NULL) {
        return;
    }
    while (!underflow(l)) {
        remover(l, NULL, CABECA, 0);
    }
    free(l);
}

bool underflow(const Lista* l) {
    if (l == NULL) {
        return false;
    }
    return l->cabeca == NULL;
}

void inserir(Lista* l, const Reg* r, Posicao p, int i) {
    if (l == NULL) {
        return;
    }
    Noh* n = malloc(sizeof(Noh));
    memcpy(&n->elemento, r, sizeof(Reg));
    switch (p) {
        case CABECA:
            n->anterior = NULL;
            n->proximo = l->cabeca;
            if (l->cabeca != NULL) {
                l->cabeca->anterior = n;
            }
            l->cabeca = n;
            break;

        case CAUDA: {
            n->proximo = NULL;
            if (l->cabeca == NULL) {
                n->anterior = NULL;
                l->cabeca = n;
                break;
            }
            Noh* u = l->cabeca;
            while (u->proximo != NULL) {
                u = u->proximo;
            }
            u->proximo = n;
            n->anterior = u;
            break;
        }

        case CRESCENTE:
            break;

        case DECRESCENTE:
            break;

        case FIXA:
            break;

        default:
            puts("Posicao INVALIDA!");
            free(n);
    }
}

bool remover(Lista* l, Reg* pr, Posicao p, int i) {
    if (l == NULL || underflow(l)) {
        return false;
    }
    Noh* n;
    switch (p) {
        case CABECA:
            n = l->cabeca;
            l->cabeca = n->proximo;
            if (l->cabeca != NULL) {
                l->cabeca->anterior = NULL;
            }
            break;

        case CAUDA: {
            n = l->cabeca;
            while (n->proximo != NULL) {
                n = n->proximo;
            }
            if (n->anterior != NULL) {
                n->anterior->proximo = NULL;
            } else {
                l->cabeca = NULL;
            }
            break;
        }

        case FIXA:
            break;

        default:
            puts("Posicao INVALIDA!");
            return false;
    }
    if (pr != NULL) {
        memcpy(pr, &n->elemento, sizeof(Reg));
    }
    free(n);
    return true;
}

Reg* buscar(const Lista* l, unsigned x) {
    if (l == NULL || underflow(l)) {
        return NULL;
    }
    Noh* n = l->cabeca;
    while (n != NULL) {
        if (n->elemento.chave == x) {
            return &n->elemento;
        }
        n = n->proximo;
    }
    return NULL;
}

void imprimir(const Lista* l) {
#ifdef DEBUG
    if (l == NULL) {
        puts("Lista INVALIDA");
        return;
    }
    if (underflow(l)) {
        puts("Lista VAZIA");
        return;
    }
    Noh* n = l->cabeca;
    printf("[CABECA] ");
    while (n != NULL) {
        printf("%u@%p<-->", n->elemento.chave, n);
        n = n->proximo;
    }
    puts(" [CAUDA]");
#endif
}

