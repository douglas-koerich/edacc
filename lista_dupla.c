#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

struct Noh {
    generico* elemento;
    struct Noh* proximo;
    struct Noh* anterior;
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

void destroi(Lista* l) {
    while (!underflow(l)) {
        generico* descarte = exclui(l, INICIO);
        free(descarte);
    }
    free(l);
}

bool underflow(const Lista* l) {
    return l->cabeca == NULL;
}

void insere(Lista* l, Extremidade e, const generico* g) {
    Noh* n = malloc(sizeof(Noh));
    n->elemento = malloc(sizeof(generico));
    memcpy(n->elemento, g, sizeof(generico));
    if (e == INICIO || l->cabeca == NULL) {
        n->proximo = l->cabeca;
        n->anterior = NULL;
        l->cabeca = n;
    } else { // FIM
        n->proximo = NULL;
        Noh* u = l->cabeca;
        while (u->proximo != NULL) {
            u = u->proximo;
        }
        u->proximo = n;
        n->anterior = u;
    }
}

void insere_ordem(Lista* l, const generico* g) {
    // (...)
}

void insere_posicao(Lista* l, unsigned p, const generico* g) {
    if (p == 0) {
        return;
    }
    Noh* n = malloc(sizeof(Noh));
    n->elemento = malloc(sizeof(generico));
    memcpy(n->elemento, g, sizeof(generico));
    if (underflow(l) || p == 1) {
        n->anterior = NULL;
        n->proximo = l->cabeca;
        l->cabeca = n;
        return;
    }
    Noh* q = l->cabeca;
    unsigned contador;
    for (contador = 1; contador < p-1; ++contador) {
        if (q->proximo == NULL) {
            break;
        }
        q = q->proximo;
    }
    n->anterior = q;
    n->proximo = q->proximo;
    q->proximo = n;
}

generico* exclui(Lista* l, Extremidade e) {
    if (underflow(l)) {
        return NULL;
    }
    generico* g = malloc(sizeof(generico));
    if (e == INICIO) {
        memcpy(g, l->cabeca->elemento, sizeof(generico));
        Noh* primeiro = l->cabeca;
        l->cabeca = l->cabeca->proximo; // aponta para o segundo (se houver)
        free(primeiro->elemento);       // apaga o conteudo do primeiro
        free(primeiro);                 // libera a memoria do primeiro noh
        if (l->cabeca) {    // existe um novo primeiro (antigo segundo)?
            l->cabeca->anterior = NULL; // segundo passa a ser o primeiro (sem anterior)
        }
    } else { // FIM
        Noh* u = l->cabeca;
        while (u->proximo != NULL) {
            u = u->proximo;
        }
        memcpy(g, u->elemento, sizeof(generico));
        if (u->anterior == NULL) {
            l->cabeca = NULL;   // vai remover o unico
        } else {
            u->anterior->proximo = NULL;    // o proximo do penultimo nao existira mais
        }
        free(u->elemento);  // libera o conteudo do ultimo
        free(u);            // libera o ultimo da memoria
    }
    return g;
}

generico* exclui_posicao(Lista* l, unsigned p) {
    // (...)
    return NULL;
}

generico* exclui_valor(Lista* l, const generico* g) {
    // (...)
    return NULL;
}

generico* busca(const Lista* l, const generico* g) {
    if (underflow(l)) {
        return NULL;
    }
    Noh* n = l->cabeca;
    while (n != NULL) {
        if (n->elemento->compara(n->elemento->coisa, g->coisa) == 0) {
            return n->elemento;
        }
        n = n->proximo;
    }
    return NULL;
}

void imprime(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ||--");
    Noh* n = l->cabeca;
    while (n != NULL) {
        putchar('>');
        n->elemento->imprime(n->elemento->coisa);
        if (n->proximo != NULL) {
            printf("<--");
        }
        n = n->proximo;
    }
    printf("<--|| (CAUDA)");
}
