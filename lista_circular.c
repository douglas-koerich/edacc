#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

struct Noh {
    generico* elemento;
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Lista {
    Noh* cauda;
};

Lista* cria(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cauda = NULL;
    return l;
}

void destroi(Lista* l) {
    while (!underflow(l)) {
        generico* descarte = exclui(l, FIM);
        free(descarte);
    }
    free(l);
}

bool underflow(const Lista* l) {
    return l->cauda == NULL;
}

void insere(Lista* l, Extremidade e, const generico* g) {
    Noh* n = malloc(sizeof(Noh));
    n->elemento = malloc(sizeof(generico));
    memcpy(n->elemento, g, sizeof(generico));
    if (underflow(l)) {
        l->cauda = n->proximo = n;  // unico noh da lista circular
        return;
    }
    if (e == FIM) {
        n->proximo = l->cauda->proximo; // aponta para o primeiro
        l->cauda->proximo = n;  // o que vai ser penultimo aponta para novo ultimo
        l->cauda = n;
    } else { // INICIO
        n->proximo = l->cauda->proximo; // aponta para o que vai ser o segundo
        l->cauda->proximo = n;  // o que eh ultimo aponta para novo primeiro
    }
    /* Codigo alternativo (e mais enigmatico, i.e., precisaria de reflexao):
    n->proximo = l->cauda->proximo;
    l->cauda->proximo = n;
    if (e == FIM) {
        l->cauda = n;
    }
    */
}

void insere_ordem(Lista* l, const generico* g) {
    // (...)
}

void insere_posicao(Lista* l, unsigned p, const generico* g) {
    // (...)
}

generico* exclui(Lista* l, Extremidade e) {
    if (underflow(l)) {
        return NULL;
    }
    generico* g = malloc(sizeof(generico));
    if (l->cauda->proximo == l->cauda) {    // unico noh que aponta pra si mesmo?
        memcpy(g, l->cauda->elemento, sizeof(generico));
        free(l->cauda->elemento);           // livra-se do conteudo do ultimo
        free(l->cauda);                     // livra-se do ultimo
        l->cauda = NULL;                    // lista fica vazia de novo
        return g;
    }
    if (e == FIM) {
        memcpy(g, l->cauda->elemento, sizeof(generico));
        Noh* aux = l->cauda;
        while (aux->proximo != l->cauda) {  // procura o penultimo na lista
            aux = aux->proximo;
        }
        aux->proximo = l->cauda->proximo;   // penultimo aponta para o primeiro
        free(l->cauda->elemento);           // livra-se do conteudo do ultimo
        free(l->cauda);                     // livra-se do ultimo
        l->cauda = aux;                     // atualiza a referencia (externa) para o ultimo
    } else { // INICIO
        Noh* aux = l->cauda->proximo;       // salva a referencia para o primeiro
        l->cauda->proximo = aux->proximo;   // faz o ultimo apontar para o segundo
        memcpy(g, aux->elemento, sizeof(generico));
        free(aux->elemento);
        free(aux);
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
    Noh* n = l->cauda;
    do {
        n = n->proximo;
        if (n->elemento->compara(n->elemento->coisa, g->coisa) == 0) {
            return n->elemento; // retorna o elemento encontrado
        }
    } while (n != l->cauda);
    return NULL;    // chegou ao fim da lista sem sucesso na busca
}

void imprime(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    Noh* n = l->cauda;
    do {
        n = n->proximo;
        n->elemento->imprime(n->elemento->coisa);
        printf("-->");
    } while (n != l->cauda);
    printf(" (CAUDA)");
}
