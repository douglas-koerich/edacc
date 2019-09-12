#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

struct Noh {
    char elemento;
    struct Noh* proximo; // endereco do noh sucessor (seguinte) na lista
    struct Noh* anterior; // endereco do noh antecessor na lista
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
        remover(l, NULL, CABECA, 0); // NULL e 0 serao ignorados
    }
    free(l); // somente apos remover da cabeca em diante...
}

bool underflow(const Lista* l) {
    if (l == NULL) {
        return false;
    }
    return l->cabeca == NULL;
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
        case CABECA:
            n->anterior = NULL; // novo noh nunca tem um anterior
            n->proximo = l->cabeca; // salva o endereco do antigo primeiro
                                    // noh no novo noh (agora, o primeiro)
            if (l->cabeca != NULL) { // existia um noh inicial?
                l->cabeca->anterior = n; // o anterior dele eh o novo noh
            }
            l->cabeca = n;
            break;

        case CAUDA: {
            n->proximo = NULL; // o novo noh sempre terah NULL como seu proximo
            // Se a lista estah vazia, inserir no FIM eh a mesma operacao que
            // inserir no INICIO
            if (l->cabeca == NULL) {
                n->anterior = NULL; // alem de ultimo, eh o primeiro
                l->cabeca = n;
                break; // interrompe o case
            }
            Noh* u = l->cabeca;
            while (u->proximo != NULL) { // enquanto nao encontra o ULTIMO da lista
                u = u->proximo; // ... vai "caminhando" ao longo da lista
            }
            u->proximo = n; // o proximo do antigo ultimo eh o novo ultimo
            n->anterior = u; // novo noh tem como anterior o antigo ultimo
            break;
        }

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
        case CABECA:
            n = l->cabeca;
            l->cabeca = n->proximo;
            if (l->cabeca != NULL) { // se existia um segundo que se tornou
                                     // primeiro noh...
                l->cabeca->anterior = NULL; // deve marca-lo como tal
            }
            break;

        case CAUDA: {
            n = l->cabeca;
            while (n->proximo != NULL) {
                n = n->proximo;
            }
            // Se de fato existe um anterior a este noh (n) que eh o ultimo...
            if (n->anterior != NULL) {
                n->anterior->proximo = NULL;
            } else { // Se nao existe, entao o ultimo eh o UNICO!
                l->cabeca = NULL; // lista volta a ficar vazia
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
    Noh* n = l->cabeca;
    while (n != NULL) { // enquanto houver noh para inspecionar...
        if (n->elemento == x) { // compara o elemento com a busca
            return true;
        }
        n = n->proximo;
    }
    return false; // percorreu toda a lista sem encontrar o valor
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
    Noh* n = l->cabeca;
    printf("[CABECA] ");
    while (n != NULL) {
        printf("%c@%p<-->", n->elemento, n);
        n = n->proximo;
    }
    puts(" [CAUDA]");
}
#endif
