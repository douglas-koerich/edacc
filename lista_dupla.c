#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lista.h"

struct NoInt {
    int valor;
    struct NoInt* proximo;
    struct NoInt* anterior;
};
typedef struct NoInt NoInt;

struct ListaInt {
    NoInt* cabeca;
};

ListaInt* cria(void) {
    ListaInt* l = malloc(sizeof(ListaInt));
    l->cabeca = NULL;
    return l;
}

void destroi(ListaInt* l) {
    while (!underflow(l)) {
        exclui(l, INICIO);
    }
    free(l);
}

bool underflow(const ListaInt* l) {
    return l->cabeca == NULL;
}

void insere(ListaInt* l, Extremo e, int numero) {
    NoInt* noh = malloc(sizeof(NoInt));
    noh->valor = numero;
    if (e == INICIO || underflow(l)) { // se lista ainda estiver vazia,
                                       // nao interessa a extremidade indicada em 'e'
        noh->anterior = NULL;
        noh->proximo = l->cabeca;
        if (!underflow(l)) {
            l->cabeca->anterior = noh;
        }
        l->cabeca = noh;
    } else {
        noh->proximo = NULL;
        NoInt* ult = l->cabeca;
        while (ult->proximo != NULL) {
            ult = ult->proximo;
        }
        ult->proximo = noh;
        noh->anterior = ult;
    }
}

void insere_ordem(ListaInt* l, int numero) {
    NoInt* noh = malloc(sizeof(NoInt));
    noh->valor = numero;
    NoInt* ant = NULL;
    NoInt* cur = l->cabeca;
    while (cur != NULL && cur->valor < numero) {
        ant = cur;
        cur = cur->proximo;
    }
    noh->proximo = cur;
    noh->anterior = ant;
    if (ant == NULL) {
        l->cabeca = noh;
    } else {
        ant->proximo = noh;
    }
    if (cur != NULL) {
        cur->anterior = noh;
    }
}

void insere_posicao(ListaInt* l, int numero, int posicao) {
    if (posicao <= 0) {
        return;
    }
    NoInt* noh = malloc(sizeof(NoInt));
    noh->valor = numero;
    if (underflow(l) || posicao == 1) {
        noh->proximo = l->cabeca;
        noh->anterior = NULL;
        l->cabeca = noh;
    } else {
        NoInt* cur = l->cabeca;
        int pos = 1;
        while (pos < posicao-1) {
            if (cur->proximo == NULL) {
                break; // lista acabou antes da 'posicao'
            }
            cur = cur->proximo, ++pos;
        }
        noh->proximo = cur->proximo;
        noh->anterior = cur;
        cur->proximo = noh;
    }
}

int exclui(ListaInt* l, Extremo e) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    assert(!underflow(l));

    int numero;
    if (e == INICIO) {
        numero = l->cabeca->valor;
        NoInt* prim = l->cabeca;
        l->cabeca = prim->proximo;
        if (!underflow(l)) {
            l->cabeca->anterior = NULL;
        }
        free(prim);
    } else {
        NoInt* ult = l->cabeca;
        while (ult->proximo != NULL) {
            ult = ult->proximo;
        }
        numero = ult->valor;
        if (ult->anterior == NULL) {
            l->cabeca = NULL;
        } else {
            ult->anterior->proximo = NULL;
        }
        free(ult);
    }
    return numero;
}

int exclui_posicao(ListaInt* l, int posicao) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    // ou com uma posicao invalida
    assert(!underflow(l) && posicao > 0);

    NoInt* cur = l->cabeca;
    int pos = 1;
    while (pos < posicao) {
        if (cur->proximo == NULL) {
            break; // lista acaba antes da 'posicao'
        }
        cur = cur->proximo, ++pos;
    }
    int numero = cur->valor;
    if (cur->anterior == NULL) {
        l->cabeca = cur->proximo;
        if (!underflow(l)) {
            l->cabeca->anterior = NULL;
        }
    } else {
        cur->anterior->proximo = cur->proximo;
        if (cur->proximo != NULL) {
            cur->proximo->anterior = cur->anterior;
        }
    }
    free(cur);
    return numero;
}

void exclui_valor(ListaInt* l, int numero) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    assert(!underflow(l));

    NoInt* noh = l->cabeca;

    // Remove TODOS os nohs que tem o mesmo numero
    while (noh != NULL) {
        if (noh->valor == numero) {
            if (noh->anterior == NULL) {
                l->cabeca = noh->proximo;
                if (!underflow(l)) {
                    l->cabeca->anterior = NULL;
                }
            } else {
                noh->anterior->proximo = noh->proximo;
                if (noh->proximo != NULL) {
                    noh->proximo->anterior = noh->anterior;
                }
            }
            NoInt* rem = noh;
            noh = noh->proximo;
            free(rem);
        } else {
            noh = noh->proximo;
        }
    }
}

bool busca(const ListaInt* l, int numero) {
    NoInt* noh = l->cabeca;
    while (noh != NULL) {
        if (noh->valor == numero) {
            return true;
        }
        noh = noh->proximo;
    }
    return false;
}

void imprime(const ListaInt* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    NoInt* noh = l->cabeca;
    while (noh != NULL) {
        if (noh->anterior != NULL) {
           putchar('>');
        } 
        printf("%d", noh->valor);
        if (noh->proximo != NULL) {
            printf("<--");
        }
        noh = noh->proximo;
    }
    printf(" (CAUDA)");
}

