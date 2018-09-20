#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

struct Noh {
    TipoChave chave;
    TipoReg registro;
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Lista {
    Noh* cabeca;
};

Lista* cria(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cabeca = NULL;
    return l;
}

bool underflow(const Lista* l) {
    return l->cabeca == NULL;
}

bool overflow(const Lista* l) {
    Noh* f = malloc(sizeof(Noh));
    if (f == NULL) {
        return true;
    }
    free(f);
    return false;
}

void inserir(Lista* l, TipoChave x, const TipoReg* r, Posicao p) {
    Noh* n = malloc(sizeof(Noh));
    n->chave = x;
    n->registro = *r;
    switch (p) {
        case FIM:
            n->proximo = NULL;
            if (!underflow(l)) {
                Noh* u = l->cabeca;
                while (u->proximo != NULL) {
                    u = u->proximo;
                }
                u->proximo = n;
                break;
            }

        case INICIO:
            n->proximo = l->cabeca;
            l->cabeca = n;
            break;

        case ORDEM:
            break;

        default:
            puts("POSICAO DE INSERCAO INVALIDA!");
    }
}

TipoReg remover(Lista* l, TipoChave x, Posicao p) {
    TipoReg r = {};
    Noh* n = l->cabeca;
    switch (p) {
        case FIM:
            if (n->proximo != NULL) {
                Noh* anterior = NULL;
                while (n->proximo != NULL) {
                    anterior = n;
                    n = n->proximo;
                }
                r = n->registro;
                anterior->proximo = NULL;
                free(n);
                break;
            }

        case INICIO:
            l->cabeca = n->proximo;
            r = n->registro;
            free(n);
            break;

        case VALOR:
            break;

        default:
            puts("POSICAO/VALOR DE REMOCAO INVALIDA!");
    }
    return r;
}

void destroi(Lista* l) {
    while (!underflow(l)) {
        Noh* n = l->cabeca;
        l->cabeca = n->proximo; 
        free(n);
    }
    free(l);
}


void imprime(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    Noh* n = l->cabeca;
    while (n != NULL) {
        imprime_tipo(n->chave, &n->registro);
        printf("-->");
        n = n->proximo;
    }
    printf("NULL (CAUDA)\n");
}

TipoReg* busca(const Lista* l, TipoChave x) {
    Noh* n = l->cabeca;
    while (n != NULL) {
        if (n->chave == x) {
            return &n->registro;
        }
        n = n->proximo;
    }
    return NULL;
}

static size_t tamanho_r(const Noh* n) {
    if (n == NULL) { // condicao terminal da recursividade
        return 0;
    } else {
        return 1 + tamanho_r(n->proximo); // conta este noh MAIS
                                          // o total retornado pela sequencia
                                          // recursiva a partir deste ponto
    }
}

/*
 * NOVA operacao do TAD, conforme solicitado pelo exercicio
 */
size_t tamanho(const Lista* l) {
    // A funcao realmente recursiva eh aquela que recebe um endereco
    // de Noh para ir percorrendo cada elemento da lista
    return tamanho_r(l->cabeca);
}

