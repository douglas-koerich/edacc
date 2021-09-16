#include <stdio.h>
#include "lista.h"

struct node {
    int dado;
    struct node* link;
};
typedef struct node node;

struct list {
    node* cabeca; // "acesso externo" para a lista
    node* cauda; // para facilitar o acesso ao fim da lista
    size_t tamanho;
};

list* l_create(void) {
    list* nova = malloc(sizeof(list));
    nova->cabeca = nova->cauda = NULL; // nao ha nenhum noh ainda
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
    if (l_underflow(l)) { // lista ainda vazia?
        w = HEAD; // novo noh serah ao mesmo tempo cabeca e cauda da lista
    }
    switch (w) {
        case HEAD:
            p->link = l->cabeca;
            l->cabeca = p;
            if (p->link == NULL) { // eh o unico elemento da lista agora?
                l->cauda = p;
            }
            break;

        case TAIL: {
            p->link = NULL;
            /*
            node* q = l->cabeca;
            while (q->link != NULL) { // enquanto nao chegar no ultimo
                q = q->link; // avanca para o proximo pra testar novamente
            }
            */
            node* q = l->cauda;
            q->link = l->cauda = p;
            break;
        }

        case POSN:

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
    node* p;
    switch (w) {
        case HEAD:
            p = l->cabeca;
            l->cabeca = p->link;
            if (p->link == NULL) { // removendo o ultimo noh?
                l->cauda = NULL;
            }
            break;

        case TAIL: {
            p = l->cabeca;
            node* a = NULL; // ao iniciar o percurso pelo inicio (cabeca) da
                            // lista, nao se tem um noh anterior a ele(a)
            while (p->link != NULL) { // enquanto nao chegar no ultimo
                a = p; // salva o noh da vez como o anterior a ser lembrado
                       // no proximo passo do laco (ou no fim dele)
                p = p->link; // avanca para o proximo pra testar novamente
            }
            if (a != NULL) { // se existe um noh anterior...
                a->link = NULL; // ... ele se torna o novo ultimo
            } else { // se nao existe, eh porque o fim da lista eh tambem o
                     // inicio dela
                l->cabeca = NULL;
            }
            l->cauda = a; // (sendo _a_ nulo ou nao)
            break;
        }

        case POSN:

        default:
            puts("Posicao invalida para remocao!");
            exit(EXIT_FAILURE);
    }
    int v = p->dado;
    free(p);
    --l->tamanho;
    return v;
}

bool l_search(const list* l, int v) {
    if (l == NULL) {
        return false;
    }
    node* p = l->cabeca; // inicia busca pelo endereco do primeiro noh
    while (p != NULL) { // enquanto existe esse noh...
        if (p->dado == v) {
            return true;
        }
        p = p->link; // faz a variavel de percurso apontar para o proximo noh
    }
    return false; // percorreu toda a lista sem encontrar...
}

size_t l_size(const list* l) {
    /*
    size_t contador = 0;
    if (l_underflow(l) == false) {
        node* p = l->cabeca; // inicia percurso pelo endereco do primeiro noh
        while (p != NULL) { // enquanto existe esse noh...
            ++contador; // ... conta-o
            p = p->link; // faz a variavel de percurso apontar para o proximo
        }
    }
    return contador;
    */
    if (l == NULL) {
        return 0;
    }
    return l->tamanho;
}

bool l_underflow(const list* l) {
    return l == NULL || l->cabeca == NULL;
}

void l_print(const list* l) {
    if (l_underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    node* p = l->cabeca; // inicia percurso pelo endereco do primeiro noh
    while (p != NULL) { // enquanto existe esse noh...
        printf("%d ", p->dado); // ... imprime o seu valor
        p = p->link; // faz a variavel de percurso apontar para o proximo noh
    }
    printf("(CAUDA)");
}
