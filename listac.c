#include <stdio.h>
#include "listac.h"

// Definicao do noh da lista encadeada simples
struct Noh {
    tipo elemento;
    struct Noh* proximo;
};

// Definicao do TAD: Lista CIRCULAR de elementos
struct Lista {
    struct Noh* cauda;
};

struct Lista* cria(void) {
    struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
    l->cauda = NULL;
    return l;
}

void destroi(struct Lista* l) {
    if (!underflow(l)) {
        struct Noh* cauda = l->cauda;
        while (l->cauda->proximo != cauda) {
            struct Noh* p = l->cauda;
            l->cauda = p->proximo;
            free(p);
        }
        free (l->cauda);
    }
    free(l);
}

bool underflow(const struct Lista* l) {
    return l->cauda == NULL;
}

void imprime(const struct Lista* l) {
    printf("(Inicio)->");
    if (!underflow(l)) {
        struct Noh* p = l->cauda;
        do {
            p = p->proximo;
            printf("%u->", p->elemento);
        } while (p != l->cauda);
    }
    printf("(Fim)\n");
}

tipo* busca(const struct Lista* l, tipo val) {
    if (underflow(l)) {
        return NULL;
    }
    struct Noh* p = l->cauda;
    do {
        if (p->elemento == val) {
            return &p->elemento;
        }
        p = p->proximo;
    } while (p != l->cauda);
    return NULL;
}

bool inserirInicio(struct Lista* l, tipo val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    if (l->cauda == NULL) {
        l->cauda = p->proximo = p;
    }
    else {
        p->proximo = l->cauda->proximo;
        l->cauda->proximo = p;
    }
    return true;
}

bool inserirFim(struct Lista* l, tipo val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    if (l->cauda == NULL) {
        p->proximo = p;
    }
    else {
        p->proximo = l->cauda->proximo;
        l->cauda->proximo = p;
    }
    l->cauda = p;
    return true;
}

bool inserirPosicao(struct Lista* l, tipo val, size_t pos) {
    if (underflow(l)) {
        return false;
    }
    size_t n;
    struct Noh* q = l->cauda->proximo;
    struct Noh* a = NULL;

    for (n=1; n<pos; ++n) {
        if (a == l->cauda) {
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
    if (a == NULL) {
        a = l->cauda;
    }
    a->proximo = p;
    if (q == l->cauda->proximo) {
        l->cauda = p;
    }
    return true;
}

bool inserirOrdem(struct Lista* l, tipo val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    if (underflow(l)) {
        p = p->proximo;
        l->cauda = p;
        return true;
    }
    struct Noh* q = l->cauda->proximo;
    struct Noh* a = l->cauda;
    while (q->elemento < val) {
        a = q;
        q = q->proximo;
        if (q == l->cauda->proximo) {
            break;
        }
    }
    a->proximo = p;
    p->proximo = q;
    if (q == l->cauda->proximo) {
        l->cauda = p;
    }
    return true;
}

bool removerInicio(struct Lista* l, tipo* pval) {
    if (underflow(l)) {
        return false;
    }
    struct Noh* cabeca = l->cauda->proximo;
    *pval = cabeca->elemento;
    l->cauda->proximo = cabeca->proximo;
    if (cabeca == l->cauda) {
        l->cauda = NULL;
    }
    free(cabeca);
    return true;
}

bool removerFim(struct Lista* l, tipo* pval) {
    if (underflow(l)) {
        return false;
    }
    struct Noh* cauda = l->cauda;
    *pval = cauda->elemento;
    if (cauda == l->cauda->proximo) {
        l->cauda = NULL;
    }
    else {
        struct Noh* q = cauda->proximo;
        while (q->proximo != cauda) {
            q = q->proximo;
        }
        q->proximo = cauda->proximo;
        l->cauda = q;
    }
    free(cauda);
    return true;
}

bool removerPosicao(struct Lista* l, tipo* pval, size_t pos) {
    if (underflow(l)) {
        return false;
    }
    size_t n;
    struct Noh* p = l->cauda->proximo;
    struct Noh* a = NULL;

    for (n=1; n<pos; ++n) {
        if (a == l->cauda) {
            // Posicao pretendida estah alem do fim da lista
            return false;
        }
        a = p;
        p = p->proximo;
    }
    *pval = p->elemento;
    if (a == NULL) {
        a = l->cauda;
    }
    a->proximo = p->proximo;
    if (p == l->cauda) {
        if (p = p->proximo) {
            l->cauda = NULL;
        }
        else {
            l->cauda = a;
        }
    }
    free(p);
    return true;
}

bool removerValor(struct Lista* l, tipo val, size_t* ppos) {
    if (underflow(l)) {
        return false;
    }
    size_t n;
    struct Noh* p = l->cauda->proximo;
    struct Noh* a = NULL;

    while (p->elemento != val) {
        a = p;
        p = p->proximo;
        if (p == l->cauda->proximo) {
            // Nao existe o valor na lista
            return false;
        }
    }
    *ppos = n;
    if (a == NULL) {
        a = l->cauda;
    }
    a->proximo = p->proximo;
    if (p == l->cauda) {
        if (p = p->proximo) {
            l->cauda = NULL;
        }
        else {
            l->cauda = a;
        }
    }
    free(p);
    return true;
}

void circula(const struct Lista* l, unsigned voltas) {
    printf("(Inicio)->");
    if (!underflow(l)) {
        unsigned v = 0;
        struct Noh* p = l->cauda;
        do {
            p = p->proximo;
            printf("%u->", p->elemento);
            if (p == l->cauda) {
                if (++v == voltas) {
                    break;
                }
            }
        } while (true); // Loop infinito!
    }
    printf("(Fim)\n");
}

