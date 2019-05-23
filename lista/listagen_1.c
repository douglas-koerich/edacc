#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listagen.h"

// Definicao de um noh da lista encadeada de ligacao SIMPLES
struct noh {
    Tipo valor;
    struct noh* proximo; // armazena apenas a conexao com o noh sucessor
};
typedef struct noh Noh;

struct lista { // "objeto" de referencia externa
    Noh* cabeca;
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
        printf("%p{ ", i); // imprime a localizacao do noh na memoria
        for (b=0; b<sizeof(Tipo); ++b, ++pbyte) { // para cada um dos bytes do tipo...
            printf("%02hhX ", *pbyte); // ... imprime o byte da vez em hexa
        }
        printf("}->%p ", i->proximo); // imprime a localizacao do PROXIMO noh na memoria
    }
    printf("(CAUDA)");
}

void ins_inicio(Lista* l, const Tipo* v) {
    Noh* n = malloc(sizeof(Noh));
    memcpy(&n->valor, v, sizeof(Tipo)); // armazena o valor no novo noh
    n->proximo = l->cabeca; // o proximo noh do novo eh o antigo inicio da lista
    l->cabeca = n; // o novo noh eh a nova cabeca da lista
    ++l->num_nohs;
}

void ins_fim(Lista* l, const Tipo* v) {
    if (underflow(l)) {
        ins_inicio(l, v);
        return;
    }
    Noh* n = malloc(sizeof(Noh));
    memcpy(&n->valor, v, sizeof(Tipo));
    n->proximo = NULL; // novo ultimo noh da lista
    Noh* i = l->cabeca; // todo percurso de busca inicia na cabeca
    while (i->proximo != NULL) { // enquanto nao for o ultimo (atual)...
        i = i->proximo; // ... "caminha" para o proximo noh da lista
    }
    i->proximo = n;
    ++l->num_nohs;
}

void rem_inicio(Lista* l, Tipo* v) {
    Noh* i = l->cabeca;
    l->cabeca = i->proximo;
    memcpy(v, &i->valor, sizeof(Tipo));
    free(i);
    --l->num_nohs;
}

void rem_fim(Lista* l, Tipo* v) {
    Noh* i = l->cabeca;
    Noh* i_ant = NULL;
    while (i->proximo != NULL) { // enquanto nao acha o ultimo noh...
        i_ant = i; // salva a posicao do noh anterior para uso no fim
        i = i->proximo;
    }
    memcpy(v, &i->valor, sizeof(Tipo));
    free(i); // remove o noh da memoria
    if (i_ant != NULL) { // existe um noh anterior?
        i_ant->proximo = NULL;
    } else { // nao havendo um anterior, isso significa que a lista ficara vazia
        l->cabeca = NULL; // precisa atualizar a referencia externa
    }
    --l->num_nohs;
}

void rem_valor(Lista* l, const Tipo* v) {
    Noh* i = l->cabeca;
    Noh* i_ant = NULL;
    while (i != NULL) {
        if (memcmp(&i->valor, v, sizeof(Tipo)) == 0) {
            // Achei o valor, remove
            if (i_ant != NULL) {
                i_ant->proximo = i->proximo; // valido tambem se i for o ultimo
            } else {
                l->cabeca = i->proximo;
            }
            // Avanca o cursor para o proximo mas MANTEM o anterior onde estah
            Noh* x = i;
            i = i->proximo;
            free(x);
            --l->num_nohs;
        } else {
            // Soh avanca o par de ponteiros i_ant/i se nao houve remocao
            // do noh em questao
            i_ant = i;
            i = i->proximo;
        }
    }
}

// Exercicio 2 da lista referente ao tema "Listas Encadeadas"
bool iguais(const Lista* l1, const Lista* l2) {
    Noh* n1 = l1->cabeca;
    Noh* n2 = l2->cabeca;
    while (n1 != NULL && n2 != NULL) {
        if (n1->valor != n2->valor) {
            return false;
        }
        n1 = n1->proximo;
        n2 = n2->proximo;
    }
    if (n1 != NULL || n2 != NULL) {
        // O laco while termina quando uma OU ambas as listas chegam ao fim;
        // se a outra nao chegou tambem, entao nao sao iguais
        return false;
    }
    return true;
}

// Exercicio 6 da lista referente ao tema "Recursividade"
static size_t tamanho_r(const Noh* n) {
    if (n == NULL) {
        return 0;
    }
    return tamanho_r(n->proximo) + 1; // a contagem que vier da sequencia na
                                      // lista, mais 1 correspondente a este noh
}

static size_t tamanho(const Lista* l) {
    // Como o tipo 'Lista' nao pode ser usado recursivamente - porque
    // nao tem a referencia do proximo noh -, a solucao implica o uso
    // de uma funcao auxiliar - esta, sim, recursiva!
    return tamanho_r(l->cabeca);
}


