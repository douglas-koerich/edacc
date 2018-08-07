#include <stdio.h>
#include "listal.h"

// Definicao do noh da lista DUPLAMENTE encadeada
struct Noh {
    tipo elemento;
    struct Noh* proximo;
    struct Noh* anterior;
};

// Definicao do TAD: Lista encadeada de elementos
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
        printf("%u->", p->elemento);
        p = p->proximo;
    }
    printf("(Fim)\n");
}

tipo* busca(const struct Lista* l, tipo val) {
    if (underflow(l)) {
        return NULL;
    }
    struct Noh* p = l->cabeca;
    while (p != NULL) {
        if (p->elemento == val) {
            return &p->elemento;
        }
        p = p->proximo;
    }
    return NULL;
}

bool inserirInicio(struct Lista* l, tipo val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    p->anterior = NULL;
    p->proximo = l->cabeca;
    if (l->cabeca != NULL) {
        l->cabeca->anterior = p;
    }
    l->cabeca = p;
    return true;
}

bool inserirFim(struct Lista* l, tipo val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    p->proximo = NULL;
    if (l->cabeca == NULL) {
        l->cabeca = p;
        p->anterior = NULL;
    }
    else {
        struct Noh* q = l->cabeca;
        while (q->proximo != NULL) {
            q = q->proximo;
        }
        p->anterior = q;
        q->proximo = p;
    }
    return true;
}

bool inserirPosicao(struct Lista* l, tipo val, size_t pos) {
    size_t n;
    struct Noh* q = l->cabeca;
    struct Noh* a = NULL;

    for (n=1; n<pos; ++n) {
        if (q == NULL) {
            // Posicao pretendida estah alem do fim da lista
            return false;
        }
        a = q;
        q = q->proximo;
    }
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    p->proximo = q;
    p->anterior = a;
    if (p->anterior != NULL) {
        p->anterior->proximo = p;
    }
    else {
        l->cabeca = p;
    }
    if (p->proximo != NULL) {
        p->proximo->anterior = p;
    }
    return true;
}

bool inserirOrdem(struct Lista* l, tipo val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    struct Noh* q = l->cabeca, *a = NULL;
    while (q != NULL && q->elemento < val) {
        a = q;
        q = q->proximo;
    }
    p->proximo = q;
    p->anterior = a;
    if (p->anterior == NULL) {
        l->cabeca = p;
    }
    else {
        p->anterior->proximo = p;
    }
    if (p->proximo != NULL) {
        p->proximo->anterior = p;
    }
    return true;
}

bool removerInicio(struct Lista* l, tipo* pval) {
    if (underflow(l)) {
        return false;
    }
    struct Noh* p = l->cabeca;
    l->cabeca = p->proximo;
    if (l->cabeca != NULL) {
        l->cabeca->anterior = NULL;
    }
    *pval = p->elemento;
    free(p);
    return true;
}

bool removerFim(struct Lista* l, tipo* pval) {
    if (underflow(l)) {
        return false;
    }
    struct Noh* p = l->cabeca;
    while (p->proximo != NULL) {
        p = p->proximo;
    }
    if (p->anterior == NULL) {
        l->cabeca = NULL;
    }
    else {
        p->anterior->proximo = NULL;
    }
    *pval = p->elemento;
    free(p);
    return true;
}

bool removerPosicao(struct Lista* l, tipo* pval, size_t pos) {
    if (underflow(l)) {
        return false;
    }
    size_t n;
    struct Noh* p = l->cabeca;

    for (n=1; n<pos; ++n) {
        if (p == NULL) {
            // Posicao pretendida estah alem do fim da lista
            return false;
        }
        p = p->proximo;
    }
    *pval = p->elemento;
    if (p->anterior == NULL) {
        l->cabeca = p->proximo;
    }
    else {
        p->anterior->proximo = p->proximo;
    }
    if (p->proximo != NULL) {
        p->proximo->anterior = p->anterior;
    }
    free(p);
    return true;
}

bool removerValor(struct Lista* l, tipo val, size_t* ppos) {
    if (underflow(l)) {
        return false;
    }
    size_t n;
    struct Noh* p = l->cabeca;

    while (p->elemento != val) {
        p = p->proximo;
        if (p == NULL) {
            // Nao existe o valor na lista
            return false;
        }
    }
    *ppos = n;
    if (p->anterior == NULL) {
        l->cabeca = p->proximo;
    }
    else {
        p->anterior->proximo = p->proximo;
    }
    if (p->proximo != NULL) {
        p->proximo->anterior = p->anterior;
    }
    free(p);
    return true;
}

void imprime_r(const struct Lista* l) {
    printf("(Fim)->");
    if (!underflow(l)) {
        struct Noh* p = l->cabeca;
        while (p->proximo != NULL) {
            p = p->proximo;
        }
        while (p != NULL) {
            printf("%u->", p->elemento);
            p = p->anterior;
        }
    }
    printf("(Inicio)\n");
}

