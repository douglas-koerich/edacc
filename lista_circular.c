#include <stdio.h>
#include "lista.h"

struct node {
    int dado;
    struct node* link;
};
typedef struct node node;

struct list {
    node* cabeca;
    node* cauda;
    size_t tamanho;
};

list* l_create(void) {
    list* nova = malloc(sizeof(list));
    nova->cabeca = nova->cauda = NULL;
    nova->tamanho = 0;
    return nova;
}

void l_destroy(list* l) {
    if (l == NULL) {
        return;
    }
    while (!l_underflow(l)) {
        l_extract(l, HEAD, 0);
    }
    free(l);
}

void l_insert(list* l, int v, where w, unsigned n) {
    if (l == NULL) {
        return;
    }
    node* p = malloc(sizeof(node));
    p->dado = v;
    if (l_underflow(l)) {
        l->cabeca = l->cauda = p->link = p; // note que o novo noh (p)
                                            // deve apontar pra si mesmo
        l->tamanho = 1;
        return;
    }
    if (w == POSN) {
        if (n <= 1) {
            w = HEAD;
        } else if (n > l_size(l)) {
            w = TAIL;
        }
    }
    switch (w) {
        case HEAD:      // insercao de novo noh como cabeca...
        case TAIL: {    // ... ou como cauda sao a MESMA operacao
            node* q = l->cauda;
            p->link = q->link;
            q->link = p;
            if (w == HEAD) {
                l->cabeca = p;
            } else {
                l->cauda = p;
            }
            break;
        }

        case POSN: {
            node* q = l->cauda;
            node* a;
            int i = 0; // inicia com 0 pois o laco inicia pela cauda
            do {
                a = q;
                q = q->link;
                ++i;
            } while (i < n);
            p->link = q;
            a->link = p;
            break;
        }

        default:
            puts("Posicao invalida para insercao!");
            exit(EXIT_FAILURE);
    }
    ++l->tamanho;
}

int l_extract(list* l, where w, unsigned n) {
    if (l_underflow(l)) {
        return INT_MIN;
    }
    if (w == POSN) {
        if (n <= 1) {
            w = HEAD;
        } else if (n == l_size(l)) {
            w = TAIL;
        } else if (n > l_size(l)) {
            puts("Posicao indicada maior que o comprimento da lista");
            return INT_MIN;
        }
    }
    node* p = l->cauda;
    if (l_size(l) == 1) {
        l->cauda = l->cabeca = NULL;
    } else {
        switch (w) {
            case HEAD: {
                p = l->cabeca;
                node* q = l->cauda;
                q->link = l->cabeca = p->link;
                break;
            }

            case TAIL: {
                node* a;
                do {
                    a = p;
                    p = p->link;
                } while (p != l->cauda);
                l->cauda = a;
                a->link = p->link;
                break;
            }

            case POSN: {
                node* a;
                int i = 0;
                do {
                    a = p;
                    p = p->link;
                    ++i;
                } while (i < n);
                a->link = p->link;
                break;
            }

            default:
                puts("Posicao invalida para remocao!");
                exit(EXIT_FAILURE);
        }
    }
    int v = p->dado;
    free(p);
    --l->tamanho;
    return v;
}

bool l_search(const list* l, int v) {
    if (l_underflow(l)) {
        return false;
    }
    node* p = l->cauda; // inicializa ponteiro de percurso pela cauda da
                        // lista (que eh o seu ponto de acesso principal)
    do {
        p = p->link; // na *primeira* iteracao do laco, vai para a cabeca
        if (p->dado == v) {
            return true;
        }
    } while (p != l->cauda);
    return false; // se saiu do laco acima, eh porque voltou ao noh de cauda;
                  // entao o valor nao foi encontrado
}

size_t l_size(const list* l) {
    if (l == NULL) {
        return 0;
    }
    return l->tamanho;
}

bool l_underflow(const list* l) {
    return l == NULL || l->cauda == NULL; // numa lista circular o acesso
                                          // externo mais importante eh o da
                                          // cauda, pois desse noh chega-se
                                          // rapidamente na cabeca (proximo)
}

void l_print(const list* l) {
    if (l_underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");

    // Algoritmo eh semelhante ao que foi implementado para busca (l_search)
    node* p = l->cauda;
    do {
        p = p->link;
        printf("%d ", p->dado);
    } while (p != l->cauda);

    printf("(CAUDA)");
}

bool l_equal(const list* l1, const list* l2) {
    if (l1 == NULL || l2 == NULL) {
        return false;
    }
    if (l_size(l1) != l_size(l2)) {
        return false;
    }
    if (l_size(l1)) {   // nao precisa testar o tamanho de l2 porque eh
                        // igual ao de l1 (senao teria saido acima)
        return true; // duas listas vazias sao consideradas iguais
    }

    // Novamente, o algoritmo eh semelhante ao percurso da busca, soh que
    // agora sendo feito simultaneamente sobre as duas listas (que tem o
    // mesmo tamanho, portanto chegarao juntas as respectivas caudas)
    node* p1 = l1->cauda;
    node* p2 = l2->cauda;
    do {
        p1 = p1->link, p2 = p2->link;
        if (p1->dado != p2->dado) {
            return false;
        }
    } while (p1 != l1->cauda);

    return true; // se voltou ateh a cauda de ambas sem encontrar diferencas
                 // (fim do laco) entao as listas sao iguais 
}