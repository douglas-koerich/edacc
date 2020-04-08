#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "lista.h"

// Definicao interna de um tipo que armazena na memoria:
// - O elemento (inteiro, registro, etc.)
// - O "link" pro proximo elemento, isto eh, o ponteiro para o proximo noh
// - NOVIDADE: outro "link" para o elemento anterior
struct Noh {
    int valor;
    struct Noh* proximo;
    struct Noh* anterior;
};
typedef struct Noh Noh;

// Definicao concreta do TAD: Lista
struct Lista {
    Noh* cabeca; // ponteiro para o primeiro noh da lista
    Noh* cauda;  // NOVIDADE: ponteiro para o ultimo noh da lista
};

Lista* cria(void) {
    Lista* nova = malloc(sizeof(Lista)); // alocacao da estrutura contendo
                                         // apenas o ponteiro da cabeca
    nova->cabeca = nova->cauda = NULL; // nao existe ainda um noh na lista
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
    return lista->cabeca == NULL; // ou return lista->cauda == NULL;
}

void insere(Lista* lista, int elemento, Posicao onde) {
    Noh* novo = malloc(sizeof(Noh)); // aloca somente quando necessario
    novo->valor = elemento;

    if (underflow(lista)) { // a lista estah vazia?
        onde = CABECA; // usa o metodo mais simples, que eh inserir na
                       // cabeca
    }
    switch (onde) {
        case CABECA:
            break;

        case CAUDA: {
            novo->proximo = NULL; // todo noh que fica no fim da lista nao
                                  // aponta pra ninguem (nao ha proximo)

            // Mesmo tendo o ponteiro 'cauda' na 'struct Lista', vamos fazer
            // o percurso para encontrar o fim da lista de nohs
            Noh* noh = lista->cabeca;
            while (noh->proximo != NULL) {
                noh = noh->proximo;
            }
            noh->proximo = novo; // o antigo ultimo noh aponta agora para
                                 // o novo ultimo noh
            novo->anterior = noh; // NOVIDADE: precisa marcar o antigo ultimo noh
                                  // como o noh anterior ao novo ultimo
            lista->cauda = novo;  // Alem disso, precisa atualizar a referencia
                                  // externa para o ultimo noh
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
        case CABECA:
            break;


        // Mesmo tendo o ponteiro 'cauda' na 'struct Lista', vamos fazer
        // o percurso para encontrar o fim da lista de nohs
        case CAUDA: {
            Noh* noh = lista->cabeca;
            while (noh->proximo != NULL) {
                noh = noh->proximo;
            }
            velho = noh; // chegou ao noh que serah removido
            if (noh->anterior == NULL) { // nao existe um anterior (eh o primeiro)?
                lista->cabeca = NULL; // a lista vai ficar vazia
                lista->cauda = NULL;  // NOVIDADE: precisa atualizar tambem
            } else {
                noh->anterior->proximo = NULL; // o penultimo torna-se ultimo
                                               // da lista
                lista->cauda = noh->anterior; // NOVIDADE: atualiza a referencia da
                                              // cauda
            }
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
    Noh* noh = lista->cabeca;
    while (noh != NULL) {
        if (noh->valor == chave) {
            return true;
        }
        noh = noh->proximo;
    }
    return false;
}

void imprime(const Lista* lista) {
    if (underflow(lista)) {
        printf("[VAZIA]");
        return;
    }
    printf("[CABECA]->");
    Noh* noh = lista->cabeca;
    while (noh != NULL) {
        printf("%d->", noh->valor);
        noh = noh->proximo;
    }
    printf("[CAUDA]");
}
