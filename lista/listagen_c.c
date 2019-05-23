#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listagen.h"

// Definicao de um noh da lista encadeada CIRCULAR de ligacao SIMPLES
struct noh {
    Tipo valor;
    struct noh* proximo; // armazena apenas a conexao com o noh sucessor
};
typedef struct noh Noh;

struct lista { // "objeto" de referencia externa
    Noh* cauda; // com a localizacao do ultimo consegue-se chegar facilmente ao
                // primeiro noh da lista
    size_t num_nohs; // opcional
};

Lista* cria(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cauda = NULL; // nao existe um noh-cauda
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
    return l->cauda == NULL;
}

void dump(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    Noh* i = l->cauda; // acessa a lista atraves da sua referencia externa
    do {
        i = i->proximo; // na primeira passagem do laco, vai para a cabeca
        unsigned char* pbyte = (unsigned char*) &i->valor; // endereco do primeiro byte do tipo
        int b;
        printf("%p{ ", i); // imprime a localizacao do noh na memoria
        for (b=0; b<sizeof(Tipo); ++b, ++pbyte) { // para cada um dos bytes do tipo...
            printf("%02hhX ", *pbyte); // ... imprime o byte da vez em hexa
        }
        printf("}->%p ", i->proximo); // imprime a localizacao do PROXIMO noh na memoria
    } while (i != l->cauda);
    printf("(CAUDA)");
}

// Os algoritmos que posicionam um novo noh no inicio e no fim sao o MESMO, porque
// a posicao relativa desse noh eh a MESMA
static Noh* ins_extremo(Lista* l, const Tipo* v) {
    Noh* n = malloc(sizeof(Noh));
    memcpy(&n->valor, v, sizeof(Tipo));
    if (l->cauda == NULL) { // lista ainda estah vazia?
        n->proximo = n;
    } else {
        n->proximo = l->cauda->proximo; // aponta para aquele que eh o primeiro
                                        // da lista (apontado pelo ultimo atual)
        l->cauda->proximo = n;
    }
    ++l->num_nohs;
    return n;
}

void ins_inicio(Lista* l, const Tipo* v) {
    ins_extremo(l, v);
}

void ins_fim(Lista* l, const Tipo* v) {
    l->cauda = ins_extremo(l, v);
}

void rem_inicio(Lista* l, Tipo* v) {
    Noh* i = l->cauda->proximo; // noh a ser removido eh a cabeca, ou seja,
                                // o proximo a partir da cauda
    memcpy(v, &i->valor, sizeof(Tipo));
    if (l->cauda == i) {
        l->cauda = NULL;
    } else {
        l->cauda->proximo = i->proximo;
    }
    free(i);
    --l->num_nohs;
}

void rem_fim(Lista* l, Tipo* v) {
    Noh* i = l->cauda;
    Noh* i_ant = i->proximo; // inicia na cabeca da lista
    while (i_ant->proximo != i) { // enquanto o noh em percurso nao eh o
                                  // noh anterior da cauda...
        i_ant = i_ant->proximo;   // ... continua a procura pelo penultimo
    }
    memcpy(v, &i->valor, sizeof(Tipo));
    if (i_ant == i) { // o anterior estava apontando pra cauda, indicando
                      // que soh existia um noh (ele mesmo) na lista?
        l->cauda = NULL;
    } else {
        i_ant->proximo = i->proximo; // o anterior (penultimo) aponta para a cabeca
        l->cauda = i_ant;
    }
    free(i); // remove o noh da memoria
    --l->num_nohs;
}

void rem_valor(Lista* l, const Tipo* v) {
}

