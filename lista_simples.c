#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lista.h"

struct NoInt {
    int valor;
    struct NoInt* proximo;
};
typedef struct NoInt NoInt;

struct ListaInt {
    NoInt* cabeca;
};

ListaInt* cria(void) {
    ListaInt* l = malloc(sizeof(ListaInt));
    l->cabeca = NULL;
    return l;
}

void destroi(ListaInt* l) {
    while (!underflow(l)) {
        exclui(l, INICIO);
    }
    free(l);
}

bool underflow(const ListaInt* l) {
    return l->cabeca == NULL;
}

void insere(ListaInt* l, Extremo e, int numero) {
    NoInt* noh = malloc(sizeof(NoInt));
    noh->valor = numero;
    if (e == INICIO || underflow(l)) { // se lista ainda estiver vazia,
                                       // nao interessa a extremidade indicada em 'e'
        noh->proximo = l->cabeca;
        l->cabeca = noh;
    } else {
        noh->proximo = NULL;
        NoInt* ult = l->cabeca;
        while (ult->proximo != NULL) {
            ult = ult->proximo;
        }
        ult->proximo = noh;
    }
}

void insere_ordem(ListaInt* l, int numero) {
    NoInt* noh = malloc(sizeof(NoInt));
    noh->valor = numero;
    NoInt* ant = NULL;
    NoInt* cur = l->cabeca;
    while (cur != NULL && cur->valor < numero) {
        ant = cur;
        cur = cur->proximo;
    }
    noh->proximo = cur;
    if (ant == NULL) {
        l->cabeca = noh;
    } else {
        ant->proximo = noh;
    }
}

void insere_posicao(ListaInt* l, int numero, int posicao) {
    if (posicao <= 0) {
        return;
    }
    NoInt* noh = malloc(sizeof(NoInt));
    noh->valor = numero;
    if (underflow(l) || posicao == 1) {
        noh->proximo = l->cabeca;
        l->cabeca = noh;
    } else {
        NoInt* cur = l->cabeca;
        int pos = 1;
        while (pos < posicao-1) {
            if (cur->proximo == NULL) {
                break; // lista acabou antes da 'posicao'
            }
            cur = cur->proximo, ++pos;
        }
        noh->proximo = cur->proximo;
        cur->proximo = noh;
    }
}

int exclui(ListaInt* l, Extremo e) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    assert(!underflow(l));

    int numero;
    if (e == INICIO) {
        numero = l->cabeca->valor;
        NoInt* prim = l->cabeca;
        l->cabeca = prim->proximo;
        free(prim);
    } else {
        NoInt* ant = NULL;
        NoInt* ult = l->cabeca;
        while (ult->proximo != NULL) {
            ant = ult;
            ult = ult->proximo;
        }
        numero = ult->valor;
        if (ant == NULL) {
            l->cabeca = NULL;
        } else {
            ant->proximo = NULL;
        }
        free(ult);
    }
    return numero;
}

int exclui_posicao(ListaInt* l, int posicao) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    // ou com uma posicao invalida
    assert(!underflow(l) && posicao > 0);

    NoInt* ant = NULL;
    NoInt* cur = l->cabeca;
    int pos = 1;
    while (pos < posicao) {
        if (cur->proximo == NULL) {
            break; // lista acaba antes da 'posicao'
        }
        ant = cur, cur = cur->proximo, ++pos;
    }
    int numero = cur->valor;
    if (ant == NULL) {
        l->cabeca = cur->proximo;
    } else {
        ant->proximo = cur->proximo;
    }
    free(cur);
    return numero;
}

void exclui_valor(ListaInt* l, int numero) {
    // Aborta(!) o programa se tenta excluir de uma lista vazia
    assert(!underflow(l));

    NoInt* ant = NULL;
    NoInt* noh = l->cabeca;

    // Remove TODOS os nohs que tem o mesmo numero
    while (noh != NULL) {
        if (noh->valor == numero) {
            if (ant == NULL) {
                l->cabeca = noh->proximo;
            } else {
                ant->proximo = noh->proximo;
            }
            NoInt* rem = noh;
            noh = noh->proximo;
            free(rem);
        } else {
            ant = noh;
            noh = noh->proximo;
        }
    }
}

bool busca(const ListaInt* l, int numero) {
    NoInt* noh = l->cabeca;
    while (noh != NULL) {
        if (noh->valor == numero) {
            return true;
        }
        noh = noh->proximo;
    }
    return false;
}

void imprime(const ListaInt* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    NoInt* noh = l->cabeca;
    while (noh != NULL) {
        printf("%d", noh->valor);
        if (noh->proximo != NULL) {
            printf("-->");
        }
        noh = noh->proximo;
    }
    printf(" (CAUDA)");
}

void insere_exclusivo(ListaInt* l, int numero) {
    NoInt* noh = malloc(sizeof(NoInt));
    noh->valor = numero;
    noh->proximo = NULL;
    if (underflow(l)) {
        l->cabeca = noh;
        return;
    }
    // Eh melhor inserir no fim, porque assim jah passa pelos nohs
    // anteriores conferindo se nao eh duplicata
    NoInt* ult = l->cabeca;
    while (ult->proximo != NULL) {
        if (ult->valor == numero) {
            free(noh);
            return; // jah existe na lista
        }
        ult = ult->proximo;
    }
    ult->proximo = noh;
}

/**
 * SOLUCAO PARA O EXERCICIO 1 DA LISTA
 */
void concatena_exclusivas(ListaInt* l1, ListaInt* l2) {
    // Se a primeira estiver vazia, jah aponta direto pra segunda
    if (underflow(l1)) {
        l1->cabeca = l2->cabeca;
        return;
    }
    // Primeiro, exclui de l2 todos os valores que jah existirem em l1
    NoInt* ult = l1->cabeca;
    while (ult != NULL) {
        exclui_valor(l2, ult->valor);
        ult = ult->proximo;
    }
    // Se a segunda estiver ou ficar vazia, nao ha o que fazer
    if (underflow(l2)) {
        return;
    }
    // Faz a cauda (ultimo noh) da primeira apontar para a cabeca (primeiro noh)
    // da segunda lista
    ult = l1->cabeca;
    while (ult->proximo != NULL) {
        ult = ult->proximo;
    }
    ult->proximo = l2->cabeca;

    // A segunda lista deve ser anulada, pois foi concatenada na primeira!
    l2->cabeca = NULL;
}

/**
 * SOLUCAO PARA O EXERCICIO 2 DA LISTA
 */
bool iguais(const ListaInt* l1, const ListaInt* l2) {
    if (underflow(l1)) {        // se a primeira lista estah vazia...
        return underflow(l2);   // retorna 'iguais' se a segunda tambem estiver
    } else if (underflow(l2)) {
        return false;           // soh a segunda lista estah vazia
    } else {
        NoInt* noh1 = l1->cabeca;
        NoInt* noh2 = l2->cabeca;

        // Continua comparando enquanto nao chegar ao fim de AMBAS
        while (noh1 != NULL && noh2 != NULL) {
            if (noh1->valor != noh2->valor) {
                return false; // nem precisa ir ateh o fim (de alguma)
            }
            noh1 = noh1->proximo, noh2 = noh2->proximo;
        }
        // Se o laco terminou, soh podem ser iguais se AMBAS atingiram seu
        // final, e nao se uma acabou antes da outra
        return noh1 == NULL && noh2 == NULL;
    }
}

