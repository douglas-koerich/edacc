#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

struct Noh {
    TipoChave chave;
    TipoReg registro;
    struct Noh* anterior; // novo campo da estrutura do noh
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Lista {
    Noh* cabeca;
};

Lista* cria(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cabeca = NULL;
    return l;
}

bool underflow(const Lista* l) {
    return l->cabeca == NULL;
}

bool overflow(const Lista* l) {
    Noh* f = malloc(sizeof(Noh));
    if (f == NULL) {
        return true;
    }
    free(f);
    return false;
}

void inserir(Lista* l, TipoChave x, const TipoReg* r, Posicao p) {
    Noh* n = malloc(sizeof(Noh));
    n->chave = x;
    n->registro = *r; // memcpy(&n->registro, r, sizeof(TipoReg));
    switch (p) {
        case FIM:
            n->proximo = NULL;
            if (!underflow(l)) {
                Noh* u = l->cabeca;
                while (u->proximo != NULL) {
                    u = u->proximo;
                }
                // Na saida do laco, 'u' estah apontando para a cauda (ultimo)
                u->proximo = n;
                n->anterior = u;
                break; // o 'break' do 'case FIM' soh existe se !underflow
            }
            // ATENCAO: a falta de 'break' aqui eh INTENCIONAL, pois no caso
            // de lista vazia, a insercao no FIM eh igual a insercao no INICIO;
            // sem o 'break', a execucao continua pelo 'case INICIO' abaixo...

        case INICIO:
            n->anterior = NULL;
            n->proximo = l->cabeca;
            l->cabeca = n;
            break;

        case ORDEM: // caso especial onde a posicao tem a ver com o valor
                    // da chave 'x' que estah sendo inserida; eh preciso
                    // percorrer a lista procurando o ponto certo onde o
                    // novo noh vai ser "enxertado"
            break;

        default:
            // Posicao VALOR nao eh valida para insercao
            puts("POSICAO DE INSERCAO INVALIDA!");
    }
}

TipoReg remover(Lista* l, TipoChave x, Posicao p) {
    // Presume-se que houve uma chamada anterior a underflow() para
    // verificar se a lista estava vazia ANTES da chamada a remover()

    TipoReg r = {};
    Noh* n = l->cabeca;
    switch (p) {
        case FIM:
            if (n->proximo != NULL) { // cabeca da lista NAO estah sozinha
                while (n->proximo != NULL) {
                    n = n->proximo;
                }
                r = n->registro;
                n->anterior->proximo = NULL; // atualiza o anterior como nova cauda
                                             // (ultimo noh) da lista
                free(n);
                break; // break do 'case FIM' se noh nao era UNICO
            }
            // ATENCAO: a falta de 'break' aqui eh INTENCIONAL, pois no caso
            // de lista com um UNICO noh, a remocao do FIM eh igual a do INICIO;
            // sem o 'break', a execucao continua pelo 'case INICIO' abaixo...

        case INICIO:
            l->cabeca = n->proximo;
            if (n->proximo != NULL) { // existia um segundo que agora eh primeiro?
                n->proximo->anterior = NULL; // ele (n->proximo) deve anular o
            }                                // ponteiro anterior
            r = n->registro;
            free(n);
            break;

        case VALOR:
            break;

        default:
            // Posicao ORDEM nao eh valida para remocao
            puts("POSICAO/VALOR DE REMOCAO INVALIDA!");
    }
    return r;
}

void destroi(Lista* l) {
    while (!underflow(l)) {
        Noh* n = l->cabeca;
        l->cabeca = n->proximo; 
        free(n);
    }
    free(l);
}


void imprime(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) NULL<-");
    Noh* n = l->cabeca;
    while (n != NULL) {
        imprime_tipo(n->chave, &n->registro);
        if (n->proximo != NULL) { // existe o proximo?
            putchar('<'); // alguem aponta para este noh (n)
        }
        printf("->");
        n = n->proximo;
    }
    printf("NULL (CAUDA)\n");
}

TipoReg* busca(const Lista* l, TipoChave x) {
    Noh* n = l->cabeca;
    while (n != NULL) {
        if (n->chave == x) {
            return &n->registro;
        }
        n = n->proximo;
    }
    return NULL;
}

