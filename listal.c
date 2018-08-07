#include <stdio.h>
#include "listal.h"

// Definicao do noh da lista encadeada simples
struct Noh {
    tipo elemento;
    struct Noh* proximo;
};

// Definicao do TAD: Lista encadeada de elementos
struct Lista {
    struct Noh* cabeca;
};

struct Lista* cria(void) {
    // Alocacao da estrutura do TAD na memoria
    struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));

    // Inicializa cabeca de uma lista vazia
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
    p->proximo = l->cabeca; // se estava vazia, o primeiro serah o ultimo; senao,
                            // o primeiro torna-se o segundo (proximo do novo noh)
    l->cabeca = p;
    return true;
}

bool inserirFim(struct Lista* l, tipo val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    p->proximo = NULL;  // se vai ser o novo ultimo, entao seu proximo sera nulo, certo?
    if (l->cabeca == NULL) {
        l->cabeca = p;
    }
    else {
        struct Noh* q = l->cabeca;
        while (q->proximo != NULL) {    // enquanto nao acha o ultimo atual
            q = q->proximo;
        }
        q->proximo = p; // ultimo atual (que apontava pra NULL) deixa de se-lo (apontando pra p)
    }
    return true;
}

bool inserirPosicao(struct Lista* l, tipo val, size_t pos) {
    // Contador de nohs 
    size_t n;

    // Ponteiro-cursor de posicao: comeca o percurso pela cabeca da lista
    struct Noh* q = l->cabeca;

    // (Preciso de um ponteiro auxiliar para lembrar o endereco do noh anterior)
    struct Noh* a = NULL;

    for (n=1; n<pos; ++n) {
        if (q == NULL) {
            // Posicao pretendida estah alem do fim da lista
            return false;
        }
        a = q;
        q = q->proximo;
    }
    // Agora que tem certeza que pode inserir, cria o novo noh (se fizesse antes, teria que
    // liberar da memoria com free(), "confere, producao?")
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;

    // "Desloca" o resto da lista, inserindo o novo noh entre o anterior e o atual
    p->proximo = q;
    if (a != NULL) {
        a->proximo = p;
    }
    else {
        l->cabeca = p;
    }
    return true;
}

bool inserirOrdem(struct Lista* l, tipo val) {
    struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;

    // Ponteiro-cursor de posicao: comeca o percurso pela cabeca da lista
    // (aqui tambem precisamos do auxiliar para o endereco do anterior)
    struct Noh* q = l->cabeca, *a = NULL;

    // Fazer ateh o fim da lista ou ateh encontrar um elemento maior que o novo
    while (q != NULL && q->elemento < val) {
        a = q;
        q = q->proximo;
    }
    p->proximo = q;
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
        l->cabeca = NULL;
    }
    else {
        a->proximo = NULL;
    }
    *pval = p->elemento;
    free(p);
    return true;
}

bool removerPosicao(struct Lista* l, tipo* pval, size_t pos) {
    if (underflow(l)) {
        return false;
    }
    // Contador de nohs 
    size_t n;

    // Ponteiro-cursor de posicao: comeca o percurso pela cabeca da lista
    struct Noh* p = l->cabeca;

    // (Preciso de um ponteiro auxiliar para lembrar o endereco do noh anterior)
    struct Noh* a = NULL;

    for (n=1; n<pos; ++n) {
        if (p == NULL) {
            // Posicao pretendida estah alem do fim da lista
            return false;
        }
        a = p;
        p = p->proximo;
    }
    // Devolve o valor que estah sendo removido desta posicao
    *pval = p->elemento;

    // "Destaca" este noh da lista, fazendo o seu anterior apontar para o seu proximo
    if (a == NULL) {
        l->cabeca = p->proximo;
    }
    else {
        a->proximo = p->proximo;
    }
    free(p);
    return true;
}

bool removerValor(struct Lista* l, tipo val, size_t* ppos) {
    if (underflow(l)) {
        return false;
    }
    // Contador de nohs 
    size_t n;

    // Ponteiro-cursor de posicao: comeca o percurso pela cabeca da lista
    struct Noh* p = l->cabeca;

    // (Preciso de um ponteiro auxiliar para lembrar o endereco do noh anterior)
    struct Noh* a = NULL;

    while (p->elemento != val) {
        a = p;
        p = p->proximo;
        if (p == NULL) {
            // Nao existe o valor na lista
            return false;
        }
    }
    // Devolve a posicao onde encontrou o valor
    *ppos = n;

    // "Destaca" este noh da lista, fazendo o seu anterior apontar para o seu proximo
    if (a == NULL) {
        l->cabeca = p->proximo;
    }
    else {
        a->proximo = p->proximo;
    }
    free(p);
    return true;
}

