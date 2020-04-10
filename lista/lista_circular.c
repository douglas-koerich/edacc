#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "lista.h"

// Definicao interna de um tipo que armazena na memoria:
// - O elemento (inteiro, registro, etc.)
// - O "link" pro proximo elemento, isto eh, o ponteiro para o proximo noh
struct Noh {
    int valor;
    struct Noh* proximo;
};
typedef struct Noh Noh;

// Definicao concreta do TAD: Lista
struct Lista {
    Noh* cauda;  // NOVIDADE: ponteiro para o ultimo noh da lista; sabendo
                 // qual eh o noh da cauda da lista, se chega facilmente ao
                 // primeiro noh (cabeca), pois ele eh o proximo do ultimo
};

Lista* cria(void) {
    Lista* nova = malloc(sizeof(Lista)); // alocacao da estrutura contendo
                                         // apenas o ponteiro da cauda
    nova->cauda = NULL; // nao existe ainda um noh na lista
    return nova;
}

void destroi(Lista* lista) {
    while (!underflow(lista)) { // precisa liberar a memoria de cada noh
                                // individualmente
        retira(lista, CABECA, NULL); // operacao de remocao mais simples
    }
    free(lista);
}

bool underflow(const Lista* lista) {
    return lista->cauda == NULL;
}

void insere(Lista* lista, int elemento, Posicao onde) {
    Noh* novo = malloc(sizeof(Noh)); // aloca somente quando necessario
    novo->valor = elemento;

    if (underflow(lista)) { // a lista estah vazia?
        lista->cauda = novo->proximo = novo; // unico noh aponta pra si mesmo
        return;
    }
    switch (onde) {
        // A insercao de um novo noh no inicio da lista coincide em posicao
        // com a insercao no fim
        case CABECA:
        case CAUDA: {
            novo->proximo = lista->cauda->proximo; // nova cauda (ou cabeca)
                                                   // vai receber o endereco
                                                   // salvo na cauda atual
            if (onde == CAUDA) {
                lista->cauda = novo; // soh atualiza a referencia externa se
                                     // o novo noh deve ser considerado como
                                     // nova cauda
            }
            break;
        }
        case ORDEM:
            break;
        }
        default:
            fprintf(stderr, "Posicao INVALIDA para insercao!\n");
            free(novo); // descarta o noh recem-alocado
    }
}

int retira(Lista* lista, Posicao onde, const int* valor) {
    if (underflow(lista)) {
        return INT_MAX; // valor invalido, nao houve remocao
    }
    Noh* velho; // endereco do noh que sera retirado
    switch (onde) {
        case CABECA: {
            velho = lista->cauda->proximo;
            if (velho != lista->cauda) { // cabeca NAO eh igual ah cauda (nao
                                         // eh o unico noh da lista)?
                lista->cauda->proximo = velho->proximo; // cauda aponta para o
                                                        // segundo noh da lista
            } else {
                lista->cauda = NULL; // a lista vai ficar vazia...
            }
            break;

        case CAUDA: {
            break;
        }

        case VALOR:
            break;

        default:
            fprintf(stderr, "Posicao INVALIDA para remocao!\n");
    }
    int val = velho->valor;
    free(velho);
    return val;
}

bool busca(const Lista* lista, int chave) {
    if (underflow(lista)) {
        return false;
    }
    Noh* noh = lista->cauda; // parte da cauda da lista
    do {
        if (noh->valor == chave) {
            return true;
        }
        noh = noh->proximo;
    } while (noh != lista->cauda); // enquanto nao volta ao noh de partida
    return false; // saiu do while porque deu a volta na lista sem encontrar
}

void imprime(const Lista* lista) {
    if (underflow(lista)) {
        printf("[VAZIA]");
        return;
    }
    printf("[CABECA]->");
    Noh* noh = lista->cauda;
    do {
        noh = noh->proximo;
        printf("%d->", noh->valor);
    } while (noh != lista->cauda);
    printf("[CAUDA]");
}

