#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

struct Noh {
    char elemento;
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Lista {
    Noh* cauda; // endereco do ULTIMO noh da lista (pelo qual se chega
                // facilmente ao primeiro - seu proximo)
};

Lista* criar(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cauda = NULL;
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
    return l->cauda == NULL;
}

void inserir(Lista* l, char c, Posicao p, int i) {
    // Se 'p' nao for igual a FIXA, o parametro 'i' (numero da
    // posicao onde deveria ser inserido) eh ignorado
    if (l == NULL) {
        return;
    }
    Noh* n = malloc(sizeof(Noh));
    n->elemento = c;
    switch (p) {
        // Na lista circular, as operacoes nos extremos sao a mesma operacao
        case INICIO:
        case FIM:
            if (l->cauda == NULL) { // lista originalmente vazia?
                n->proximo = n; // cauda tem como proximo ela mesma
                l->cauda = n;
            } else {
                n->proximo = l->cauda->proximo; // novo noh aponta para cabeca
                l->cauda->proximo = n; // novo noh inserido entre a cauda e a
                                       // cabeca
                if (p == FIM) {
                    l->cauda = n; // soh muda a referencia da cauda se a
                                  // operacao solicitada era insercao no FIM
                }
            }
            break;

        case CRESCENTE:
            break;

        case DECRESCENTE:
            break;

        case FIXA:
            break;

        default:
            puts("Posicao INVALIDA!");
            free(n); // libera o noh alocado!
    }
}

bool remover(Lista* l, char* pc, Posicao p, int i) {
    if (l == NULL || underflow(l)) {
        return false;
    }
    Noh* n;
    switch (p) {
        case INICIO:
            n = l->cauda->proximo;
            if (l->cauda->proximo != n->proximo) { // nao aponta pra si mesmo?
                l->cauda->proximo = n->proximo;
            } else {
                l->cauda = NULL; // removendo o ultimo noh da lista
            }
            break;

        case FIM: {
            Noh* ant; // Eh preciso um ponteiro para o noh anterior...
            n = l->cauda;
            do {
                ant = n;
                n = n->proximo; // na primeira iteracao, vai para a cabeca
            } while (n != l->cauda); // dah a volta na lista, sempre salvando o
                                     // anterior de cada noh...

            // Se de fato existe um anterior a este noh (n) que eh o ultimo...
            if (ant != n) { // nao estah apontando pra si mesmo
                ant->proximo = n->proximo; // nova cauda deve apontar pra cabeca
                l->cauda = ant;
            } else { // Se estiver apontando pra si mesmo...
                l->cauda = NULL; // lista volta a ficar vazia
            }
            break;
        }

        case FIXA:
            break;

        default: // inclui CRESCENTE e DECRESCENTE
            puts("Posicao INVALIDA!");
            return false;
    }
    // Se o ponteiro 'pc' for NULL, quem chamou 'remover' nao estah
    // interessado em obter o elemento que estava no noh removido
    if (pc != NULL) {
        *pc = n->elemento;
    }
    free(n);
    return true;
}

bool buscar(const Lista* l, char x) {
    if (l == NULL || underflow(l)) {
        return false;
    }
    Noh* n = l->cauda;
    do {
        n = n->proximo; // na primeira iteracao, vai para a cabeca da lista
        if (n->elemento == x) { // compara o elemento com a busca
            return true;
        }
    } while (n != l->cauda); // voltou-se ao ponto de partida sem encontrar x
    return false;
}

#ifdef DEBUG
void imprimir(const Lista* l) {
    if (l == NULL) {
        puts("Lista INVALIDA");
        return;
    }
    if (underflow(l)) {
        puts("Lista VAZIA");
        return;
    }
    Noh* n = l->cauda;
    printf("[CABECA] ");
    do {
        n = n->proximo;
        printf("%c@%p-->", n->elemento, n);
    } while (n != l->cauda);
    puts(" [CAUDA]-->[CABECA]");
}
#endif

