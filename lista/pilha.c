#include <stdlib.h>
#include "lista.h"
#include "pilha.h" // definicao externa do TAD

struct Pilha {
    Lista* lista;
};

Pilha* p_cria(void) {
    Pilha* nova = malloc(sizeof(Pilha));
    nova->lista = cria();
    return nova;
}

void p_destroi(Pilha* pilha) {
    destroi(pilha->lista);
    free(pilha);
}

bool p_underflow(const Pilha* pilha) {
    return underflow(pilha->lista);
}

void push(Pilha* pilha, int elemento) {
    insere(pilha->lista, elemento, CABECA);
}

int pop(Pilha* pilha) {
    return retira(pilha->lista, CABECA, NULL);
}

