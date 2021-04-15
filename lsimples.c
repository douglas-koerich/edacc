#include <stdio.h>
#include "lista.h"

struct noh {
    Registro dado;          // elemento armazenado neste noh da lista
    struct noh* proximo;    // referencia/ligacao com o noh seguinte
};
typedef struct noh Noh;

struct lista {
    Noh* cabeca;     // ponteiro para o primeiro noh da lista ("acesso externo")
    size_t contador; // numero de nohs da lista no momento
};

Lista* create(void) {
    /*
    Lista* nova = malloc(sizeof(Lista));
    nova->cabeca = NULL; // lista nao possui um primeiro noh (vazia)
    nova->contador = 0;
    */
    Lista* nova = calloc(1, sizeof(Lista));
    return nova;
}

void destroy(Lista* a_lista) {
    // Antes de apagar a estrutura (struct lista) que faz referencia aos
    // nohs da lista, preciso apagar esses nohs da memoria!
    while (!underflow(a_lista)) {
        Registro nao_usado;
        extract(a_lista, &nao_usado, CABECA);
    }
    free(a_lista);
}

bool underflow(const Lista* a_lista) {
    return a_lista->contador == 0;
}

size_t size(const Lista* a_lista) {
    return a_lista->contador;
}

void print(const Lista* a_lista) {
    Noh* noh = a_lista->cabeca;
    printf("(INICIO) ");
    while (noh != NULL) {
        // Noh eh valido, imprime-o...
        printf("{%d,%c} ", noh->dado.chave, noh->dado.valor);
        noh = noh->proximo;
    }
    printf("(FIM)");
}

void insert(Lista* a_lista, const Registro* novo_elemento, Criterio forma,
            unsigned posicao) {
    Noh* novo_noh = malloc(sizeof(Noh));
    novo_noh->dado = *novo_elemento;

    if (underflow(a_lista)) { // se a lista ainda estiver vazia...
        forma = CABECA; // ... vamos inserir usando o criterio mais "facil"
    }
    switch (forma) {
        case CABECA:    // novo elemento no inicio
            novo_noh->proximo = a_lista->cabeca;
            break;

        case CAUDA: {   // novo elemento no fim da lista
            Noh* noh = a_lista->cabeca;
            while (noh->proximo != NULL) { // enquanto nao for o ultimo...
                // ... vai para o proximo
                noh = noh->proximo;
            }
            noh->proximo = novo_noh;
            novo_noh->proximo = NULL;          
            break;
        }

        case CRESCENTE: // novo elemento em ordem crescente relativo aos
                        // vizinhos
            break;

        case DECRESCENTE:   // idem, em ordem decrescente
            break;

        case ORDINAL:   // na primeira, segunda, ..., n-esima posicao
            break;

        default:
            puts("ERRO: criterio de insercao INVALIDO!");
            destroy(a_lista);

            // Nao esquecer de apagar tambem o noh que foi recem-criado
            // nesta mesma funcao
            free(novo_noh);

            exit(EXIT_FAILURE);
    }
}

void extract(Lista* a_lista, Registro* removido, Criterio forma,
             unsigned posicao) {
    if (underflow(a_lista)) {
        puts("ERRO: lista vazia!");
        destroy(a_lista);
        exit(EXIT_FAILURE);
    }
    Noh* noh = a_lista->cabeca;
    switch (forma) {
        case CABECA:    // remove do inicio
            a_lista->cabeca = noh->proximo;
            *removido = noh->dado;
            free(noh);
            break;

        case CAUDA:     // remove do fim da lista
            break;

        case ORDINAL:   // remove o primeiro, segundo, ..., n-esimo noh
            break;

        case VALOR:     // remove baseado na chave
            break;

        default:
            puts("ERRO: criterio de remocao INVALIDO!");
            destroy(a_lista);
            exit(EXIT_FAILURE);
    }
}

bool search(const Lista* a_lista, int chave_x, Registro* p_reg) {
    Noh* noh = a_lista->cabeca;
    while (noh != NULL) {
        if (noh->dado.chave == chave_x) {
            *p_reg = noh->dado; // copia todo o registro para o endereco
                                // (no ponteiro) passado pra funcao 
            return true;
        }
        noh = noh->proximo;
    }
    return false; // chave_x nao foi encontrada
}
