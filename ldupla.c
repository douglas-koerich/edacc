#include <stdio.h>
#include "lista.h"

struct noh {
    Registro dado;
    struct noh* proximo;
    struct noh* anterior;   // referencia/ligacao com o noh anterior
};
typedef struct noh Noh;

struct lista {
    Noh* cabeca;
    Noh* cauda; // ponteiro adicional para acesso externo ao ultimo noh
    size_t contador;
};

Lista* create(void) {
    Lista* nova = calloc(1, sizeof(Lista));
    return nova;
}

void destroy(Lista* a_lista) {
    while (!underflow(a_lista)) {
        Registro nao_usado;
        extract(a_lista, &nao_usado, CABECA, 0);
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
        printf("{%d,%c} ", noh->dado.chave, noh->dado.valor);
        noh = noh->proximo;
    }
    printf("(FIM)");
}

void rprint(const Lista* a_lista) {
    Noh* noh = a_lista->cauda;
    printf("(FIM) ");
    while (noh != NULL) {
        printf("{%d,%c} ", noh->dado.chave, noh->dado.valor);
        noh = noh->anterior;
    }
    printf("(INICIO)");
}

void insert(Lista* a_lista, const Registro* novo_elemento, Criterio forma,
            unsigned posicao) {
    Noh* novo_noh = malloc(sizeof(Noh));
    novo_noh->dado = *novo_elemento;

    if (underflow(a_lista)) {
        forma = CABECA;
    }
    Noh* noh = a_lista->cabeca;
    switch (forma) {
        case CABECA:
            novo_noh->proximo = a_lista->cabeca;
            a_lista->cabeca = novo_noh;

            // Novos passos para a lista duplamente encadeada
            novo_noh->anterior = NULL;
            if (novo_noh->proximo != NULL) { // a lista nao estava vazia?
                // Vai ao noh seguinte (novo_noh->proximo), que era a cabeca,
                // e muda o seu ponteiro anterior para a nova cabeca
                novo_noh->proximo->anterior = novo_noh;
            } else {
                a_lista->cauda = novo_noh; // novo_noh eh unico, entao eh
                                           // cabeca E cauda da lista
            }
            break;

        case CAUDA: {
            // Nao eh preciso testar se a_lista->cauda eh NULL porque se
            // fosse a lista estaria vazia, e pelo teste de underflow acima
            // o criterio de insercao seria mudado para CABECA...
            novo_noh->proximo = NULL;          

            novo_noh->anterior = a_lista->cauda;
            a_lista->cauda = novo_noh;

            // Vai ao noh anterior (novo_noh->anterior), que era a cauda,
            // e muda o seu ponteiro proximo para a nova cauda
            novo_noh->anterior->proximo = novo_noh;
            break;
        }

        case CRESCENTE: {
            while (noh != NULL
                   && noh->dado.chave < novo_noh->dado.chave) {
                noh = noh->proximo;
            }
            novo_noh->proximo = noh;
            if (noh == NULL) {
                novo_noh->anterior = a_lista->cauda;
                a_lista->cauda = novo_noh;
            } else {
                if (noh->anterior != NULL) {
                    noh->anterior->proximo = novo_noh;
                } else {
                    a_lista->cabeca = novo_noh;
                }
                novo_noh->anterior = noh->anterior;
                noh->anterior = novo_noh;
            }
            break;
        }
        case DECRESCENTE: {
            while (noh != NULL
                   && noh->dado.chave > novo_noh->dado.chave) {
                noh = noh->proximo;
            }
            novo_noh->proximo = noh;
            if (noh == NULL) {
                novo_noh->anterior = a_lista->cauda;
                a_lista->cauda = novo_noh;
            } else {
                if (noh->anterior != NULL) {
                    noh->anterior->proximo = novo_noh;
                } else {
                    a_lista->cabeca = novo_noh;
                }
                novo_noh->anterior = noh->anterior;
                noh->anterior = novo_noh;
            }
            break;
        }
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
    ++a_lista->contador;
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
        case CABECA:
            a_lista->cabeca = noh->proximo;
            *removido = noh->dado;
            if (noh->proximo != NULL) {
                noh->proximo->anterior = NULL;
            } else {
                // Noh sendo removido era o unico, entao a referencia de cauda
                // tambem precisa ser anulada
                a_lista->cauda = NULL;
            }
            free(noh);
            break;

        case CAUDA: {
            noh = a_lista->cauda;
            a_lista->cauda = noh->anterior;
            *removido = noh->dado;
            if (noh->anterior != NULL) {
                noh->anterior->proximo = NULL;
            } else {
                a_lista->cabeca = NULL;
            }
            free(noh);
            break;
        }
        case ORDINAL:   // remove o primeiro, segundo, ..., n-esimo noh
            break;

        case VALOR: {
            while (noh != NULL) {
                if (noh->dado.chave == removido->chave) {
                    *removido = noh->dado;
                    if (noh->anterior != NULL) {
                        noh->anterior->proximo = noh->proximo;
                    } else {
                        a_lista->cabeca = noh->proximo;
                    }
                    if (noh->proximo != NULL) {
                        noh->proximo->anterior = noh->anterior;
                    } else {
                        a_lista->cauda = noh->anterior;
                    }
                    free(noh);

                    --a_lista->contador;
                    break;
                }
                noh = noh->proximo;
            }
            return;
        }
        default:
            puts("ERRO: criterio de remocao INVALIDO!");
            destroy(a_lista);
            exit(EXIT_FAILURE);
    }
    --a_lista->contador;
}

bool search(const Lista* a_lista, int chave_x, Registro* p_reg) {
    Noh* noh = a_lista->cabeca;
    while (noh != NULL) {
        if (noh->dado.chave == chave_x) {
            *p_reg = noh->dado;
            return true;
        }
        noh = noh->proximo;
    }
    return false;
}
