#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "listah.h"

struct NoReg {
    Reg registro;
    struct NoReg* proximo;
};
typedef struct NoReg NoReg;

struct ListaReg {
    NoReg* cabeca;
};

ListaReg* l_cria(void) {
    ListaReg* l = malloc(sizeof(ListaReg));
    l->cabeca = NULL;
    return l;
}

void l_destroi(ListaReg* l) {
    while (!l_underflow(l)) {
        l_exclui(l, INICIO);
    }
    free(l);
}

bool l_underflow(const ListaReg* l) {
    return l->cabeca == NULL;
}

void l_insere(ListaReg* l, Extremo e, const Reg* r) {
    NoReg* noh = malloc(sizeof(NoReg));
    noh->registro = *r;
    if (e == INICIO || l_underflow(l)) { // se lista ainda estiver vazia,
                                       // nao interessa a extremidade indicada em 'e'
        noh->proximo = l->cabeca;
        l->cabeca = noh;
    } else {
        noh->proximo = NULL;
        NoReg* ult = l->cabeca;
        while (ult->proximo != NULL) {
            ult = ult->proximo;
        }
        ult->proximo = noh;
    }
}

void l_insere_ordem(ListaReg* l, const Reg* r) {
    NoReg* noh = malloc(sizeof(NoReg));
    noh->registro = *r;
    NoReg* ant = NULL;
    NoReg* cur = l->cabeca;
    while (cur != NULL && strcmp(cur->registro.chave, r->chave) < 0) {
        ant = cur;
        cur = cur->proximo;
    }
    noh->proximo = cur;
    if (ant == NULL) {
        l->cabeca = noh;
    } else {
        ant->proximo = noh;
    }
}

void l_insere_posicao(ListaReg* l, const Reg* r, int posicao) {
    if (posicao <= 0) {
        return;
    }
    NoReg* noh = malloc(sizeof(NoReg));
    noh->registro = *r;
    if (l_underflow(l) || posicao == 1) {
        noh->proximo = l->cabeca;
        l->cabeca = noh;
    } else {
        NoReg* cur = l->cabeca;
        int pos = 1;
        while (pos < posicao-1) {
            if (cur->proximo == NULL) {
                break; // lista acabou antes da 'posicao'
            }
            cur = cur->proximo, ++pos;
        }
        noh->proximo = cur->proximo;
        cur->proximo = noh;
    }
}

Reg l_exclui(ListaReg* l, Extremo e) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    assert(!l_underflow(l));

    Reg r;
    if (e == INICIO) {
        r = l->cabeca->registro;
        NoReg* prim = l->cabeca;
        l->cabeca = prim->proximo;
        free(prim);
    } else {
        NoReg* ant = NULL;
        NoReg* ult = l->cabeca;
        while (ult->proximo != NULL) {
            ant = ult;
            ult = ult->proximo;
        }
        r = ult->registro;
        if (ant == NULL) {
            l->cabeca = NULL;
        } else {
            ant->proximo = NULL;
        }
        free(ult);
    }
    return r;
}

Reg l_exclui_posicao(ListaReg* l, int posicao) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    // ou com uma posicao invalida
    assert(!l_underflow(l) && posicao > 0);

    NoReg* ant = NULL;
    NoReg* cur = l->cabeca;
    int pos = 1;
    while (pos < posicao) {
        if (cur->proximo == NULL) {
            break; // lista acaba antes da 'posicao'
        }
        ant = cur, cur = cur->proximo, ++pos;
    }
    Reg r = cur->registro;
    if (ant == NULL) {
        l->cabeca = cur->proximo;
    } else {
        ant->proximo = cur->proximo;
    }
    free(cur);
    return r;
}

Reg l_exclui_chave(ListaReg* l, const char* x) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    assert(!l_underflow(l));

    NoReg* ant = NULL;
    NoReg* noh = l->cabeca;

    Reg r = {};

    // Remove TODOS os nohs que tem a mesma chave
    while (noh != NULL) {
        if (strcmp(noh->registro.chave, x) == 0) {
            r = noh->registro;
            if (ant == NULL) {
                l->cabeca = noh->proximo;
            } else {
                ant->proximo = noh->proximo;
            }
            NoReg* rem = noh;
            noh = noh->proximo;
            free(rem);
        } else {
            ant = noh;
            noh = noh->proximo;
        }
    }
    return r;
}

const Reg* l_busca(const ListaReg* l, const char* x) {
    NoReg* noh = l->cabeca;
    while (noh != NULL) {
        if (strcmp(noh->registro.chave, x) == 0) {
            return &noh->registro;
        }
        noh = noh->proximo;
    }
    return NULL;
}

void l_imprime(const ListaReg* l) {
    if (l_underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    NoReg* noh = l->cabeca;
    while (noh != NULL) {
        printf("%s", noh->registro.chave);
        if (noh->proximo != NULL) {
            printf("-->");
        }
        noh = noh->proximo;
    }
    printf(" (CAUDA)");
}

