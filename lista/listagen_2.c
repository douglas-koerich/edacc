#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listagen.h"

// Definicao de um noh da lista encadeada de ligacao DUPLA
struct noh {
    Tipo valor;
    struct noh* anterior; // armazena a conexao com o noh antecessor
    struct noh* proximo; // armazena a conexao com o noh sucessor
};
typedef struct noh Noh;

struct lista { // "objeto" de referencia externa
    Noh* cabeca;    // permite o percurso no sentido direto
    Noh* cauda;     // permite o percurso no sentido inverso
    size_t num_nohs; // opcional
};

Lista* cria(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cabeca = NULL; // nao existe um noh-cabeca
    l->num_nohs = 0;
    return l;
}

void destroi(Lista* l) {
    while (!underflow(l)) { // enquanto restar algum noh na lista...
        Tipo dummy;
        rem_inicio(l, &dummy);
    }
    free(l);
}

bool underflow(const Lista* l) {
    return l->cabeca == NULL;
}

void dump(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    Noh* i;
    for (i=l->cabeca; i!=NULL; i=i->proximo) { // para todos os nohs da lista
        unsigned char* pbyte = (unsigned char*) &i->valor; // endereco do primeiro byte do tipo
        int b;
        printf("{ ");
        for (b=0; b<sizeof(Tipo); ++b, ++pbyte) { // para cada um dos bytes do tipo...
            printf("%02hhX ", *pbyte); // ... imprime o byte da vez em hexa
        }
        printf("}@%p ", i); // imprime a localizacao do noh na memoria
    }
    printf("(CAUDA)");
}

void ins_inicio(Lista* l, const Tipo* v) {
    Noh* n = malloc(sizeof(Noh));
    memcpy(&n->valor, v, sizeof(Tipo)); // armazena o valor no novo noh
    n->proximo = l->cabeca; // o proximo noh do novo eh o antigo inicio da lista
    l->cabeca = n; // o novo noh eh a nova cabeca da lista
    ++l->num_nohs;

    n->anterior = NULL; // sendo o (novo) primeiro noh, nao terah antecessor
    if (n->proximo != NULL) {
       n->proximo->anterior = n; // leia assim: (n->proximo)->anterior = ...
    } else { // nao existia um outro noh antes...
        l->cauda = n; // ... entao o (novo) primeiro eh tambem o (novo) ultimo
    }
}

void ins_fim(Lista* l, const Tipo* v) {
    if (underflow(l)) {
        ins_inicio(l, v);
        return;
    }
    Noh* n = malloc(sizeof(Noh));
    memcpy(&n->valor, v, sizeof(Tipo));
    n->proximo = NULL; // novo ultimo noh da lista
    n->anterior = l->cauda;
    n->anterior->proximo = n; // nao preciso verificar se (n->anterior) eh NULL
                              // porque se o fosse a lista estaria vazia e o
                              // teste de underflow te-lo-ia detectado na entrada
                              // da funcao
    ++l->num_nohs;
}

void rem_inicio(Lista* l, Tipo* v) {
    Noh* i = l->cabeca;
    l->cabeca = i->proximo;
    memcpy(v, &i->valor, sizeof(Tipo));
    free(i);
    if (l->cabeca == NULL) {
        l->cauda = NULL;
    } else {
        l->cabeca->anterior = NULL;
    }
    --l->num_nohs;
}

void rem_fim(Lista* l, Tipo* v) {
    Noh* i = l->cauda;
    l->cauda = i->anterior;
    memcpy(v, &i->valor, sizeof(Tipo));
    if (i->anterior != NULL) {
        i->anterior->proximo = NULL;
    } else {
        l->cabeca = NULL;
    }
    free(i); // remove o noh da memoria
    --l->num_nohs;
}

void rem_valor(Lista* l, const Tipo* v) {
    Noh* i = l->cabeca;
    while (i != NULL) {
        if (memcmp(&i->valor, v, sizeof(Tipo)) == 0) {
            // Achei o valor, remove
            if (i->anterior != NULL) { // se existe um noh anterior...
                // ... esse noh anterior deve ter como proximo o sucessor do
                // que vai ser removido
                i->anterior->proximo = i->proximo; // valido tambem se i for o ultimo
            } else {
                l->cabeca = i->proximo;
            }
            if (i->proximo != NULL) {
                i->proximo->anterior = i->anterior;
            } else {
                l->cauda = i->anterior;
            }
            Noh* x = i;
            i = i->proximo;
            free(x);
            --l->num_nohs;
        } else {
            i = i->proximo;
        }
    }
}

