#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h> // para definicao do INT_MIN
#include "lista_int.h"

struct Noh {
    int elemento;
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

void destroi(Lista* l) {
    while (!underflow(l)) {
        exclui(l, INICIO);
    }
    free(l);
}

bool underflow(const Lista* l) {
    return l->cabeca == NULL;
}

void insere(Lista* l, Extremidade e, int i) {
    Noh* n = malloc(sizeof(Noh));
    n->elemento = i;
    if (e == INICIO || l->cabeca == NULL) { // se lista ainda estiver vazia,
                                            // nao interessa a extremidade indicada em 'e'
        n->proximo = l->cabeca;
        l->cabeca = n;
    } else { // FIM
        n->proximo = NULL;  // novo noh serah o novo ultimo
        Noh* u = l->cabeca;
        while (u->proximo != NULL) {
            u = u->proximo;
        }
        u->proximo = n;
    }
}

int exclui(Lista* l, Extremidade e) {
    if (underflow(l)) {
        return INT_MIN;
    }
    int i;
    if (e == INICIO) {
        i = l->cabeca->elemento;
        Noh* aux = l->cabeca;
        l->cabeca = l->cabeca->proximo;
        free(aux);
    } else { // FIM
        Noh* aux = NULL;    // 'aux' terah o endereco do anterior ao 'u'
        Noh* u = l->cabeca;
        while (u->proximo != NULL) {
            aux = u;    // salva o endereco pra lembrar quem era o anterior
            u = u->proximo;
        }
        i = u->elemento;
        if (aux == NULL) {  // o primeiro 'u->proximo' jah era NULL, entao
                            // nem entrou no laco while pra atualizar 'aux'
            l->cabeca = NULL;
        } else {
            aux->proximo = NULL;
        }
        free(u);
    }
    return i;
}

void imprime(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    Noh* n = l->cabeca;
    while (n != NULL) {
        printf("%d", n->elemento);
        if (n->proximo != NULL) {
            printf("-->");
        }
        n = n->proximo;
    }
    printf(" (CAUDA)");
}

static size_t tamanho_r(const Noh* n) {
    if (n == NULL) {
        return 0;
    }
    return 1 + tamanho_r(n->proximo);
}

size_t tamanho(const Lista* l) {
/*
    // Versao iterativa (com laco)
    size_t numero_nos = 0;
    Noh* n = l->cabeca;
    while (n != NULL) {
        ++numero_nos;
        n = n->proximo;
    }
    return numero_nos;
*/
    // Versao recursiva
    return tamanho_r(l->cabeca);
}

