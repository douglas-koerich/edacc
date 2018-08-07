#include <stdio.h>
#include "listah.h"

// Definicao do noh da lista encadeada simples
struct Noh {
    tipo elemento;
    struct Noh* proximo;
};

// Definicao do TAD: Lista encadeada COM CABECALHO
struct Lista {
    struct Noh* cabeca;
    struct Noh* cauda;
    size_t num_elementos;
    unsigned checksum;
};

static unsigned checksumNoh(const struct Noh* p) {
    unsigned sum = 0;
    unsigned char* pbyte = (unsigned char*) &p->elemento;
    size_t b, tamanho = sizeof(p->elemento);
    for (b=0; b<tamanho; ++b) {
        sum += *pbyte++;
    }
    return sum;
}

struct Lista* cria(void) {
    struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
    l->cabeca = l->cauda = NULL;
    l->num_elementos = 0;
    l->checksum = 0;
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
    return l->num_elementos == 0;
}

void imprime(const struct Lista* l) {
    printf("Tamanho: %u, Checksum: %#x, Cabeca: %u, Cauda: %u\n",
           tamanho(l), l->checksum, l->cabeca->elemento, l->cauda->elemento);
    printf("(Inicio)->");
    struct Noh* p = l->cabeca;
    while (p != NULL) {
        printf("%u->", p->elemento);
        p = p->proximo;
    }
    printf("(Fim) %s\n", valida(l)? "ok": "NOK!");
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
    p->proximo = l->cabeca; // se estava vazia, o primeiro serah o ultimo; senao,
                            // o primeiro torna-se o segundo (proximo do novo noh)
    ++l->num_elementos;
    l->checksum += checksumNoh(p);
    l->cabeca = p;
    if (l->cauda == NULL) { // se estava vazia, a cabeca e a cauda serao o mesmo noh
        l->cauda = p;
    }
    return true;
}

bool inserirFim(struct Lista* l, tipo val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    p->proximo = NULL;  // se vai ser o novo ultimo, entao seu proximo sera nulo, certo?
    ++l->num_elementos;
    l->checksum += checksumNoh(p);
    if (l->cabeca == NULL) {
        l->cabeca = l->cauda = p;
    }
    else {
        l->cauda->proximo = p;
        l->cauda = p;
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

    ++l->num_elementos;
    l->checksum += checksumNoh(p);

    if (q == NULL) {
        l->cauda = p;
    }
    if (a == NULL) {
        l->cabeca = p;
    }
    else {
        a->proximo = p;
    }
    return true;
}

bool inserirOrdem(struct Lista* l, tipo val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;

    ++l->num_elementos;
    l->checksum += checksumNoh(p);

    struct Noh* q = l->cabeca, *a = NULL;
    while (q != NULL && q->elemento < val) {
        a = q;
        q = q->proximo;
    }
    p->proximo = q;
    if (q == NULL) {
        l->cauda = p;
    }
    if (a == NULL) {
        l->cabeca = p;
    }
    else {
        a->proximo = p;
    }
    return true;
}

bool removerInicio(struct Lista* l, tipo* pval) {
    if (underflow(l)) {
        return false;
    }
    struct Noh* p = l->cabeca;
    l->cabeca = p->proximo;
    if (l->cabeca == NULL) {
        l->cauda = NULL;
    }
    --l->num_elementos;
    l->checksum -= checksumNoh(p);
    *pval = p->elemento;
    free(p);
    return true;
}

bool removerFim(struct Lista* l, tipo* pval) {
    if (underflow(l)) {
        return false;
    }
    struct Noh* p = l->cabeca, *a = NULL;
    while (p->proximo != NULL) {
        a = p;
        p = p->proximo;
    }
    if (a == NULL) {
        l->cabeca = l->cauda = NULL;
    }
    else {
        a->proximo = NULL;
        l->cauda = a;
    }
    --l->num_elementos;
    l->checksum -= checksumNoh(p);
    *pval = p->elemento;
    free(p);
    return true;
}

bool removerPosicao(struct Lista* l, tipo* pval, size_t pos) {
    if (pos > l->num_elementos) {
        // Posicao pretendida estah alem do fim da lista
        return false;
    }
    if (underflow(l)) {
        return false;
    }
    size_t n;
    struct Noh* p = l->cabeca;
    struct Noh* a = NULL;

    for (n=1; n<pos; ++n) {
        a = p;
        p = p->proximo;
    }
    *pval = p->elemento;
    if (a == NULL) {
        l->cabeca = p->proximo;
        if (l->cabeca == NULL) {
            l->cauda = NULL;
        }
    }
    else {
        a->proximo = p->proximo;
        if (a->proximo == NULL) {
            l->cauda = a;
        }
    }
    --l->num_elementos;
    l->checksum -= checksumNoh(p);
    free(p);
    return true;
}

bool removerValor(struct Lista* l, tipo val, size_t* ppos) {
    if (underflow(l)) {
        return false;
    }
    size_t n;
    struct Noh* p = l->cabeca;
    struct Noh* a = NULL;

    while (p->elemento != val) {
        a = p;
        p = p->proximo;
        if (p == NULL) {
            // Nao existe o valor na lista
            return false;
        }
    }
    *ppos = n;
    if (a == NULL) {
        l->cabeca = p->proximo;
        if (l->cabeca == NULL) {
            l->cauda = NULL;
        }
    }
    else {
        a->proximo = p->proximo;
        if (a->proximo == NULL) {
            l->cauda = a;
        }
    }
    --l->num_elementos;
    l->checksum -= checksumNoh(p);
    free(p);
    return true;
}

size_t tamanho(const struct Lista* l) {
    return l->num_elementos;
}

bool valida(const struct Lista* l) {
    unsigned teste = 0;
    struct Noh* p = l->cabeca;
    while (p != NULL) {
        teste += checksumNoh(p);
        p = p->proximo;
    }
    return teste == l->checksum;
}

