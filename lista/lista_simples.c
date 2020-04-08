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
    Noh* cabeca; // ponteiro para o primeiro noh da lista
};

Lista* cria(void) {
    Lista* nova = malloc(sizeof(Lista)); // alocacao da estrutura contendo
                                         // apenas o ponteiro da cabeca
    nova->cabeca = NULL; // nao existe ainda um noh na lista
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
    return lista->cabeca == NULL;
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
            novo->proximo = lista->cabeca; // recupera o endereco do (agora)
                                           // antigo primeiro noh da lista
            lista->cabeca = novo; // redefine quem eh o novo primeiro noh
            break;

        case CAUDA: {
            novo->proximo = NULL; // todo noh que fica no fim da lista nao
                                  // aponta pra ninguem (nao ha proximo)
            Noh* noh = lista->cabeca;
            while (noh->proximo != NULL) {
                noh = noh->proximo;
            }
            noh->proximo = novo; // o antigo ultimo noh aponta agora para
                                 // o novo ultimo noh
            break;
        }
        case ORDEM: { // Eh necessario encontrar o ponto de insercao desse
                      // noh sem ferir a ordem com relacao aos demais; pode
                      // ser que esse ponto seja o inicio (cabeca), meio ou
                      // fim (cauda) da lista
            Noh* noh = lista->cabeca;
            Noh* anterior = NULL; // novamente precisamos da memoria do
                                  // noh anterior ao ponto de parada

            // 'noh' deve ser aquele que vai ficar depois do novo
            while (noh != NULL && noh->valor < novo->valor) {
                anterior = noh;
                noh = noh->proximo;
            }
            // O novo noh eh inserido *antes* do ponto de parada do laco
            if (noh == NULL) { // chegou ao fim da fila?
                novo->proximo = NULL; // este novo noh eh o ultimo (tem o
                                      // maior valor entre os nohs)
                anterior->proximo = novo;
            } else {
                novo->proximo = noh; // aponta para o noh que tem o valor
                                     // maior ou igual ao novo
                if (anterior == NULL) { // o noh que tem o valor maior ou
                                        // igual ao novo eh o primeiro!!
                    lista->cabeca = novo; // novo noh eh a nova cabeca
                } else { // existe um noh anterior que tem um valor menor
                         // do que o valor do novo noh
                    anterior->proximo = novo;
                }
            }
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
            velho = lista->cabeca;
            lista->cabeca = velho->proximo;
            break;

        case CAUDA: {
            Noh* noh = lista->cabeca;
            Noh* anterior = NULL; // "memoria" de qual era o noh anterior
                                  // atualizada a cada passo do laco
            while (noh->proximo != NULL) {
                anterior = noh; // lembra onde estava antes
                noh = noh->proximo;
            }
            velho = noh; // chegou ao noh que serah removido
            if (anterior == NULL) { // nao existe um anterior?
                lista->cabeca = NULL; // a lista vai ficar vazia
            } else {
                anterior->proximo = NULL; // o penultimo torna-se ultimo
                                          // da lista
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
