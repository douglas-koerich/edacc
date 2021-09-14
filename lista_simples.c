#include <stdio.h>
#include "lista.h"

struct node {
    int dado;
    struct node* link;
};
typedef struct node node;

struct list {
    node* cabeca;
    size_t tamanho;
};

list* l_create(void) {
    list* nova = malloc(sizeof(list));
    nova->cabeca = NULL; // nao ha nenhum noh ainda pra ser enderecado
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

}

int l_extract(list* l, where s, unsigned n) {

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
    size_t contador = 0;
    if (l_underflow(l) == false) {
        node* p = l->cabeca; // inicia percurso pelo endereco do primeiro noh
        while (p != NULL) { // enquanto existe esse noh...
            ++contador; // ... conta-o
            p = p->link; // faz a variavel de percurso apontar para o proximo
        }
    }
    return contador;
    /*
    if (l == NULL) {
        return 0;
    }
    return l->tamanho;
    */
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
