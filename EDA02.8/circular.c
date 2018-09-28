#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "pilha.h"

struct Noh {
    int numero;
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

bool underflow(const Lista* l) {
    return l->cauda == NULL;
}

bool overflow(const Lista* l) {
    Noh* f = malloc(sizeof(Noh));
    if (f == NULL) {
        return true;
    }
    free(f);
    return false;
}

void inserir(Lista* l, int i, Posicao p) {
    Noh* n = malloc(sizeof(Noh));
    n->numero = i;
    switch (p) {
        case INICIO:
        case FIM:
            if (underflow(l)) {
                n->proximo = n;
            } else {
                Noh* u = l->cauda;
                n->proximo = u->proximo;
                u->proximo = n;
            }
            if (underflow(l) || p == FIM) {
                l->cauda = n;
            }
            break;

        case ORDEM:
            break;

        default:
            puts("POSICAO DE INSERCAO INVALIDA!");
    }
}

int remover(Lista* l, int i, Posicao p) {
    int r;
    Noh* n = l->cauda;
    switch (p) {
        case INICIO:
            if (n->proximo != n) {
                Noh* c = n->proximo;
                n->proximo = c->proximo;
                r = c->numero;
                free(c);
                break;
            }

        case FIM:
            if (n->proximo == n) {
                l->cauda = NULL;
            } else {
                Noh* c = n->proximo;
                while (c->proximo != n) {
                    c = c->proximo;
                }
                c->proximo = n->proximo;
                l->cauda = c;
            }
            r = n->numero;
            free(n);
            break;

        case VALOR:
            break;

        default:
            puts("POSICAO/VALOR DE REMOCAO INVALIDA!");
    }
    return r;
}

void destroi(Lista* l) {
    while (!underflow(l)) {
        remover(l, 0, INICIO);
    }
    free(l);
}


void imprime(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    Noh* n = l->cauda->proximo;
    do {
        printf("%d", n->numero);
        printf("-->");
        n = n->proximo;
    } while (n != l->cauda->proximo);
    printf(" (CAUDA)--->(CABECA)\n");
}

bool busca(const Lista* l, int i) {
    if (underflow(l)) {
        return NULL;
    }
    Noh* n = l->cauda;
    do {
        if (n->numero == i) {
            return true;
        }
        n = n->proximo;
    } while (n != l->cauda);
    return false;
}

void inverte(Lista* l) {
    // Usa o TAD pilha (em lista? em vetor? nao importa!) como estrutura
    // de apoio para a inversao
    Pilha* auxiliar = cria_p();

    // Enquanto nao transferir todos os nohs da lista para a pilha...
    while (!underflow(l)) {
        // Retira da lista no sentido cabeca->...->cauda (inicio para o fim)
        push(auxiliar, remover(l, 0, INICIO));
    }

    // Enquanto nao recupera tudo o que estava na pilha...
    while (!underflow_p(auxiliar)) {
        // Poe o proximo noh tirado da pilha na sequencia da lista
        // (sentido cabeca->...->cauda/inicio para o fim)
        inserir(l, pop(auxiliar), FIM);
    }

    // Nao esquecer de remover o TAD da memoria...
    destroi_p(auxiliar);
}

