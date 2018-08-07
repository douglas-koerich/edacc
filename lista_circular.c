#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lista.h"

struct NoInt {
    int valor;
    struct NoInt* proximo;
};
typedef struct NoInt NoInt;

struct ListaInt {
    NoInt* cauda;
};

ListaInt* cria(void) {
    ListaInt* l = malloc(sizeof(ListaInt));
    l->cauda = NULL;
    return l;
}

void destroi(ListaInt* l) {
    while (!underflow(l)) {
        exclui(l, FIM);
    }
    free(l);
}

bool underflow(const ListaInt* l) {
    return l->cauda == NULL;
}

void insere(ListaInt* l, Extremo e, int numero) {
    NoInt* noh = malloc(sizeof(NoInt));
    noh->valor = numero;
    if (underflow(l)) { // se lista ainda estiver vazia,
                        // nao interessa a extremidade indicada em 'e'
        NoInt* unico = noh;
        l->cauda = unico;
        unico->proximo = unico;
    } else {
        NoInt* ult = l->cauda;
        NoInt* prim = ult->proximo;
        noh->proximo = prim;
        ult->proximo = noh;
        if (e == FIM) {
            l->cauda = noh;
        }
    }
}

void insere_ordem(ListaInt* l, int numero) {
    NoInt* noh = malloc(sizeof(NoInt));
    noh->valor = numero;
    if (underflow(l)) {
        NoInt* unico = noh;
        l->cauda = unico;
        unico->proximo = unico;
        return;
    }
    NoInt* ant;
    NoInt* cur = l->cauda;
    do {
        ant = cur;
        cur = cur->proximo;
        if (cur->valor >= noh->valor) {
            noh->proximo = ant->proximo;
            ant->proximo = noh;
            return;
        }
    } while (cur != l->cauda); // enquanto nao completa a volta

    NoInt* ult = l->cauda;
    NoInt* prim = ult->proximo;
    noh->proximo = prim;
    ult->proximo = noh;
    l->cauda = noh;
}

void insere_posicao(ListaInt* l, int numero, int posicao) {
    if (posicao <= 0) {
        return;
    }
    NoInt* noh = malloc(sizeof(NoInt));
    noh->valor = numero;
    if (underflow(l)) {
        noh->proximo = noh;
        l->cauda = noh;
        return;
    }
    NoInt* ult = l->cauda;
    NoInt* prim = ult->proximo;
    if (posicao == 1) {
        noh->proximo = prim;
        ult->proximo = noh;
    } else {
        NoInt* cur = prim;
        int pos = 1;
        while (pos < posicao-1) {
            if (cur == ult) {
                break; // lista acabou antes da 'posicao'
            }
            cur = cur->proximo, ++pos;
        }
        noh->proximo = cur->proximo;
        cur->proximo = noh;
        if (cur == ult) {
            l->cauda = noh;
        }
    }
}

int exclui(ListaInt* l, Extremo e) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    assert(!underflow(l));

    int numero;
    NoInt* ult = l->cauda;
    NoInt* prim = ult->proximo;
    if (e == INICIO) {
        numero = prim->valor;
        if (prim == ult) {
            l->cauda = NULL;
        } else {
            ult->proximo = prim->proximo;
        }
        free(prim);
    } else {
        NoInt* ant;
        NoInt* cur = ult;
        do {
            ant = cur;
            cur = cur->proximo;
        } while (cur != l->cauda);
        if (ant == cur) {
            l->cauda = NULL;
        } else {
            ant->proximo = cur->proximo;
            l->cauda = ant;
        }
        numero = cur->valor;
        free(cur);
    }
    return numero;
}

int exclui_posicao(ListaInt* l, int posicao) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    // ou com uma posicao invalida
    assert(!underflow(l) && posicao > 0);

    NoInt* ant = l->cauda;
    NoInt* cur = ant->proximo;
    int pos = 1;
    while (pos < posicao) {
        if (cur == l->cauda) {
            break; // lista acaba antes da 'posicao'
        }
        ant = cur, cur = cur->proximo, ++pos;
    }
    int numero = cur->valor;
    if (ant == cur) {
        l->cauda = NULL;
    } else {
        ant->proximo = cur->proximo;
        if (cur == l->cauda) {
            l->cauda = cur->proximo;
        }
    }
    free(cur);
    return numero;
}

void exclui_valor(ListaInt* l, int numero) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    assert(!underflow(l));

    NoInt* ant = l->cauda;
    NoInt* noh = ant->proximo;

    // Remove TODOS os nohs que tem o mesmo numero
    do {
        if (noh->valor == numero) {
            NoInt* rem = noh;
            if (ant == noh) {
                l->cauda = NULL;
                free(rem);
                return;
            }
            ant->proximo = noh->proximo;
            noh = ant; // volta ao anterior, pois se pulasse ao
                       // proximo poderia deixar de testar a
                       // cauda por chegar prematuramente ao 
                       // fim da lista
            if (rem == l->cauda) {
                l->cauda = ant;
            }
            free(rem);
        } else {
            ant = noh;
            noh = noh->proximo;
        }
    } while (noh->valor == numero ||    // enquanto estiver num noh com o valor
             noh != l->cauda);          // enquanto nao completa a volta
}

bool busca(const ListaInt* l, int numero) {
    if (underflow(l)) {
        return false;
    }
    NoInt* noh = l->cauda;
    do {
        noh = noh->proximo;
        if (noh->valor == numero) {
            return true;
        }
    } while (noh != l->cauda);
    return false;
}

void imprime(const ListaInt* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    NoInt* noh = l->cauda;
    do {
        noh = noh->proximo;
        printf("%d", noh->valor);
        if (noh != l->cauda) {
            printf("-->");
        }
    } while (noh != l->cauda);
    printf(" (CAUDA)");
}

