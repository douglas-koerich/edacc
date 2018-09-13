#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

struct Noh {
    TipoChave chave;
    TipoReg registro;
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Lista {
    Noh* cauda; // noh terminal (ultimo) da lista encadeada
};

Lista* cria(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cauda = NULL;
    return l;
}

bool underflow(const Lista* l) {
    return l->cauda == NULL;
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
        // Na lista circular, a insercao no fim e no inicio poem o novo noh
        // na MESMA posicao (depois do ultimo/antes do primeiro)
        case INICIO:
        case FIM:
            if (underflow(l)) {
                n->proximo = n;
            } else {
                Noh* u = l->cauda; // ponteiro para o ultimo noh atualmente
                n->proximo = u->proximo;
                u->proximo = n;
            }
            if (p == FIM) {
                l->cauda = n; // referencia (ponteiro) externa(o) soh eh
                              // atualizada(o) se insercao eh no FIM da lista
            }
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

    TipoReg r = {}; // registro vazio
    Noh* n = l->cauda; // faz acesso ao ultimo noh da lista
    switch (p) {
        case INICIO:
            if (n->proximo != n) { // cauda da lista NAO estah sozinha
                Noh* c = n->proximo; // ponteiro para a cabeca da lista
                n->proximo = c->proximo; // ultimo agora aponta para o segundo
                r = c->registro;
                free(c);
                break; // break do 'case INICIO' se noh nao era UNICO
            }
            // ATENCAO: a falta de 'break' aqui eh INTENCIONAL, pois no caso
            // de lista com um UNICO noh, a remocao do INICIO eh igual a do FIM;
            // sem o 'break', a execucao continua pelo 'case FIM' abaixo...

        case FIM:
            if (n->proximo == n) { // somente este noh na lista
                l->cauda = NULL;
            } else {
                // Eh necessario encontrar o penultimo elemento para marca-lo
                // como o novo fim da lista
                Noh* c = n->proximo; // comeca pela cabeca da lista
                while (c->proximo != n) {
                    c = c->proximo;
                }
                // O ponteiro 'c' termina o laco acima apontando para o
                // penultimo noh; ele deve ser o ultimo agora
                c->proximo = n->proximo; // ele passa a apontar para o inicio
                l->cauda = c;
            }    
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
        remover(l, 0, INICIO);
    }
}


void imprime(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    // Inicia impressao pela cabeca
    printf("(CABECA) ");
    Noh* n = l->cauda->proximo;
    do {
        imprime_tipo(n->chave, &n->registro);
        printf("-->");
        n = n->proximo;
    } while (n != l->cauda->proximo);
    printf(" (CAUDA)--->(CABECA)\n");
}

TipoReg* busca(const Lista* l, TipoChave x) {
    if (underflow(l)) {
        return NULL;
    }
    // Inicia a busca pela cabeca
    Noh* n = l->cauda;
    do {
        if (n->chave == x) {
            return &n->registro;
        }
        n = n->proximo;
    } while (n != l->cauda);
    return NULL; // chegou ao fim sem encontrar a chave
}

