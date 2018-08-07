#include <stdlib.h>
#include <stdio.h>
#include "exerc5lista2.h"

struct Noh {
    float elemento;
    struct Noh* proximo;
};

struct Lista {
    struct Noh* cabeca;
};

struct Lista* cria(void) {
    struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
    l->cabeca = NULL;
    return l;
}

void destroi(struct Lista* l) {
    while (l->cabeca != NULL) {
        struct Noh* p = l->cabeca;
        l->cabeca = p->proximo;
        free(p);
    }
    free(l);
}

bool underflow(const struct Lista* l) {
    return l->cabeca == NULL;
}

void imprime(const struct Lista* l) {
    printf("(Inicio)->");
    struct Noh* p = l->cabeca;
    while (p != NULL) {
        printf("%.3f->", p->elemento);
        p = p->proximo;
    }
    printf("(Fim)\n");
}

bool inserirInicio(struct Lista* l, float val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    p->proximo = l->cabeca;
    l->cabeca = p;
    return true;
}

/**
 * SOLUCAO DO EXERCICIO
 */

bool removerIntervalo(struct Lista* l, float inf, float sup) {
    if (underflow(l)) {
        return false;
    }
    struct Noh* p = l->cabeca, *a = NULL;
    while (p != NULL) {
        if (p->elemento >= inf && p->elemento <= sup) {
            struct Noh* q = p;  // marca o noh que vai ser removido com um ponteiro
            p = p->proximo;     // avanca para o proximo (para continuar o percurso)
            if (a == NULL) {
                l->cabeca = p;  // inicio da lista deixa de ser o noh que vai ser
                                // removido (passa a ser o proximo, que agora eh p)
            }
            else {
                a->proximo = p; // note que o ponteiro 'a' NAO avanca nesse caso,
                                // pois o anterior do noh que esta sendo removido
                                // agora eh o anterior do noh que esta sendo apontado
                                // por p
            }
            free(q);            // libera o noh
        }
        else {
            a = p;              // aqui eh o percurso usual
            p = p->proximo;
        }
    }
    return true;
}

