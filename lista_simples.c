#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

struct Noh {
    generico* elemento;
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

void destroi(Lista* l) {
    while (!underflow(l)) {
        // Jah que usamos uma funcao 'exclui', temos que dar conta
        // do elemento alocado dinamicamente e devolvido por ela
        generico* descarte = exclui(l, INICIO);
        free(descarte);
    }
    free(l);
}

bool underflow(const Lista* l) {
    return l->cabeca == NULL;
}

void insere(Lista* l, Extremidade e, const generico* g) {
    Noh* n = malloc(sizeof(Noh));
    n->elemento = malloc(sizeof(generico));
    memcpy(n->elemento, g, sizeof(generico));
    if (e == INICIO || l->cabeca == NULL) { // se lista ainda estiver vazia,
                                            // nao interessa a extremidade indicada em 'e'
        n->proximo = l->cabeca;
        l->cabeca = n;
    } else { // FIM
        n->proximo = NULL;  // novo noh serah o novo ultimo
        Noh* u = l->cabeca;
        while (u->proximo != NULL) {
            u = u->proximo;
        }
        u->proximo = n;
    }
}

void insere_ordem(Lista* l, const generico* g) {
    // (...)
}

void insere_posicao(Lista* l, unsigned p, const generico* g) {
    // (...)
}

generico* exclui(Lista* l, Extremidade e) {
    if (underflow(l)) {
        return NULL;
    }
    generico* g = malloc(sizeof(generico));
    if (e == INICIO) {
        memcpy(g, l->cabeca->elemento, sizeof(generico));
        Noh* aux = l->cabeca;
        l->cabeca = l->cabeca->proximo;
        free(aux->elemento);
        free(aux);
    } else { // FIM
        Noh* aux = NULL;    // 'aux' terah o endereco do anterior ao 'u'
        Noh* u = l->cabeca;
        while (u->proximo != NULL) {
            aux = u;    // salva o endereco pra lembrar quem era o anterior
            u = u->proximo;
        }
        memcpy(g, u->elemento, sizeof(generico));
        if (aux == NULL) {  // o primeiro 'u->proximo' jah era NULL, entao
                            // nem entrou no laco while pra atualizar 'aux'
            l->cabeca = NULL;
        } else {
            aux->proximo = NULL;
        }
        free(u->elemento);
        free(u);
    }
    return g;
}

generico* exclui_posicao(Lista* l, unsigned p) {
    // (...)
    return NULL;
}

generico* exclui_valor(Lista* l, const generico* g) {
    if (underflow(l)) {
        return NULL;
    }
    Noh* aux = NULL;    // preciso do auxiliar novamente pra lembrar qual era o
                        // noh anterior daquele que vou excluir
    Noh* n = l->cabeca;
    while (n != NULL) {
        // Usa callback de comparacao para inspecionar o valor
        if (n->elemento->compara(n->elemento->coisa, g->coisa) == 0) {
            // Achei o valor neste noh, vou remove-lo
            generico* g = malloc(sizeof(generico)); // para retornar o generico removido
            memcpy(g, n->elemento, sizeof(generico));
            if (aux == NULL) {
                // Jah encontrou o valor no primeiro noh (nem salvou o anterior),
                // eh como excluir do inicio
                l->cabeca = n->proximo;
            } else {
                // Conecta o noh anterior ao proximo noh deste que vai ser excluido
                aux->proximo = n->proximo;
            }
            // Libera o generico e o proprio noh da memoria
            free(n->elemento);
            free(n);
            return g;
        }
        // Nao achei ainda, vou ao proximo...
        aux = n;
        n = n->proximo;
    }
    return NULL;
}

generico* busca(const Lista* l, const generico* g) {
    if (underflow(l)) {
        return NULL;
    }
    Noh* n = l->cabeca;
    while (n != NULL) {
        // Usa callback de comparacao para inspecionar o valor
        if (n->elemento->compara(n->elemento->coisa, g->coisa) == 0) {
            return n->elemento; // retorna o elemento encontrado
        }
        n = n->proximo;
    }
    return NULL;    // chegou ao fim da lista sem sucesso na busca
}

void imprime(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    Noh* n = l->cabeca;
    while (n != NULL) {
        n->elemento->imprime(n->elemento->coisa);
        if (n->proximo != NULL) {
            printf("-->");
        }
        n = n->proximo;
    }
    printf(" (CAUDA)");
}
