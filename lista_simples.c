#include <stdlib.h>
#include <stdio.h>

struct Noh {
    char elemento; // valor armazenado na lista (lista de caracteres)
    struct Noh* proximo; // endereco do noh sucessor (seguinte) na lista
};
typedef struct Noh Noh;

struct Lista {
    Noh* cabeca; // endereco do primeiro noh da lista
};

Lista* criar(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cabeca = NULL;
    return l;
}

void destruir(Lista* l) {
    if (l == NULL) { // protecao contra parametro invalido
        return;
    }
    // Eh importante (seria um ERRO nao faze-lo) liberar todos os
    // nohs da memoria antes de perder os enderecos de referencia a eles
    while (!underflow(l)) {
        remover(l, NULL, INICIO, 0); // NULL e 0 serao ignorados
    }
    free(l); // somente apos remover da cabeca em diante...
}

bool underflow(const Lista* l) {
    if (l == NULL) {
        return false;
    }
    return l->cabeca == NULL;
}


