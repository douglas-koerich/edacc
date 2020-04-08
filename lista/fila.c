#include <stdlib.h>
#include "lista.h"
#include "fila.h" // definicao externa do TAD

struct Fila {
    Lista* lista;
};

Fila* f_cria(void) {
    Fila* nova = malloc(sizeof(Fila));
    nova->lista = cria();
    return nova;
}

void f_destroi(Fila* fila) {
    destroi(fila->lista);
    free(fila);
}

bool f_underflow(const Fila* fila) {
    return underflow(fila->lista);
}

void f_insere(Fila* fila, int elemento) {
    insere(fila->lista, elemento, CABECA);
}

int f_retira(Fila* fila) {
    return retira(fila->lista, CAUDA, NULL);
}

