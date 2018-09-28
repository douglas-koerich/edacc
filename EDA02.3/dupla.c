#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

struct Noh {
    char* string;
    struct Noh* anterior;
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

bool underflow(const Lista* l) {
    return l->cabeca == NULL;
}

bool overflow(const Lista* l) {
    Noh* f = malloc(sizeof(Noh));
    if (f == NULL) {
        return true;
    }
    free(f);
    return false;
}

void inserir(Lista* l, const char* s, Posicao p) {
    Noh* n = malloc(sizeof(Noh));
    n->string = strdup(s); // malloc da string com copia da original
    switch (p) {
        case FIM:
            n->proximo = NULL;
            if (!underflow(l)) {
                Noh* u = l->cabeca;
                while (u->proximo != NULL) {
                    u = u->proximo;
                }
                u->proximo = n;
                n->anterior = u;
                break;
            }

        case INICIO:
            n->anterior = NULL;
            n->proximo = l->cabeca;
            l->cabeca = n;
            break;

        case ORDEM:
            break;

        default:
            puts("POSICAO DE INSERCAO INVALIDA!");
    }
}

void remover(Lista* l, const char* s, Posicao p) {
    Noh* n = l->cabeca;
    switch (p) {
        case FIM:
            if (n->proximo != NULL) {
                while (n->proximo != NULL) {
                    n = n->proximo;
                }
                n->anterior->proximo = NULL;
                free(n->string); // tem que liberar a memoria da copia feita na inserir()
                free(n);
                break;
            }

        case INICIO:
            l->cabeca = n->proximo;
            if (n->proximo != NULL) {
                n->proximo->anterior = NULL;
            }
            free(n->string); // (v. acima)
            free(n);
            break;

        case VALOR:
            break;

        default:
            puts("POSICAO/VALOR DE REMOCAO INVALIDA!");
    }
}

void destroi(Lista* l) {
    while (!underflow(l)) {
        Noh* n = l->cabeca;
        l->cabeca = n->proximo; 
        free(n->string); // (v. comentario na funcao remover)
        free(n);
    }
    free(l);
}


void imprime(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) NULL<-");
    Noh* n = l->cabeca;
    while (n != NULL) {
        printf("\"%s\"", n->string);
        if (n->proximo != NULL) {
            putchar('<');
        }
        printf("->");
        n = n->proximo;
    }
    printf("NULL (CAUDA)\n");
}

bool busca(const Lista* l, const char* s) {
    Noh* n = l->cabeca;
    while (n != NULL) {
        if (strcmp(n->string, s) == 0) {
            return true;
        }
        n = n->proximo;
    }
    return false;
}

/**
 * NOVA OPERACAO SOLICITADA PELO EXERCICIO 3 DA LISTA
 */
void bubblesort_decrescente(Lista* l) {
    // Pesquise em casa usando a nossa bibliografia sobre o funcionamento
    // do algoritmo de ordenacao por bolha (bubblesort)
    Noh* v = l->cabeca;
    while (v != NULL) {
        Noh* i = l->cabeca;
        Noh* j = i->proximo;
        while (j != NULL) {
            if (strcmp(i->string, j->string) < 0) { // se a string de 'i' for menor
                                                    // que a string de 'j'...
                // Estao fora de ordem, troca (os ponteiros entre si)!
                char* temp = i->string;
                i->string = j->string;
                j->string = temp;
            }
            // Avanca os ponteiros para nohs a fim de comparar o proximo par
            j = j->proximo;
            i = i->proximo;
        }
        v = v->proximo;
    }
}

