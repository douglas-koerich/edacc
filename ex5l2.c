#include <stdio.h>
#include "ex5l2.h"

struct noh {
    int valor;
    struct noh* proximo;
};
typedef struct noh Noh;

struct lista {
    Noh* cabeca;
};

Lista* create(void) {
    Lista* nova = calloc(1, sizeof(Lista));
    return nova;
}

void destroy(Lista* a_lista) {
    while (!underflow(a_lista)) {
        extract(a_lista);
    }
    free(a_lista);
}

bool underflow(const Lista* a_lista) {
    return a_lista->cabeca == NULL;
}

void print(const Lista* a_lista) {
    Noh* noh = a_lista->cabeca;
    printf("(INICIO) ");
    while (noh != NULL) {
        printf("%d ", noh->valor);
        noh = noh->proximo;
    }
    printf("(FIM)");
}

void insert(Lista* a_lista, int valor) {
    Noh* novo_noh = malloc(sizeof(Noh));
    novo_noh->valor = valor;

    novo_noh->proximo = a_lista->cabeca;
    a_lista->cabeca = novo_noh;
}

int extract(Lista* a_lista) {
    if (underflow(a_lista)) {
        puts("ERRO: lista vazia!");
        destroy(a_lista);
        exit(EXIT_FAILURE);
    }
    Noh* noh = a_lista->cabeca;
    a_lista->cabeca = noh->proximo;
    int valor = noh->valor;
    free(noh);
    return valor;
}

void delete_range(Lista* a_lista, int inf, int sup) {
    Noh* anterior = NULL;
    Noh* noh = a_lista->cabeca;
    while (noh != NULL) {
        if (noh->valor >= inf && noh->valor <= sup) {
            // Noh deve ser removido
            Noh* proximo = noh->proximo;
            if (anterior == NULL) {
                a_lista->cabeca = proximo;
            } else {
                anterior->proximo = proximo;
            }
            free(noh);
            noh = proximo;

            // Mantem o ponteiro 'anterior' no mesmo noh que
            // estava antes
        } else {
            anterior = noh;
            noh = noh->proximo;
        }
    }
}
