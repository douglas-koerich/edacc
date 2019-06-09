#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

// Definicao do estado de uma entrada da tabela de hashing
enum Estado {
    LIVRE,  // 0
    OCUPADA // 1
};
typedef enum Estado Estado;

// Definicao de fim da sequencia encadeada de chaves sinonimas
#define FIM_SINONIMAS -1

// Definicao de uma entrada da tabela de hashing
struct Entrada {
    R dado;         // o registro armazenado
    Estado estado;  // se existe ou nao um registro nesta entrada da tabela
    int sinonima;   // indice de uma chave sinonima que pode estar na regiao extra da tabela
};
typedef struct Entrada Entrada;

struct Hash {
    Entrada* vetor; // vetor de entradas (estado + dado + indice-da-sinonima)
    size_t M;       // tamanho do vetor
    Entrada* extra; // vetor extra de entradas (para as chaves sinominas)
    size_t P;       // tamanho do extra (pode aumentar a medida das colisoes)
};

// Implementacao da funcao de hashing (a que vai definir o indice no vetor
// a partir do valor da chave)
// (OBS.: escolheu-se o metodo pseudo-aleatorio)

static int h(unsigned chave, size_t tamanho) { // 1o. parametro eh a chave do registro
    srand(chave);
    int aleatorio = rand();
    int indice = aleatorio % tamanho;
    return indice;
}

// Implementacao das operacoes da interface

Hash* cria(size_t tamanho) {
    Hash* tabela = malloc(sizeof(Hash));
    tabela->M = tabela->P = tamanho;

    // Usa calloc porque ela inicializa a memoria com zeros, o que vai acabar
    // "armazenando" LIVRE (0) em todas as entradas :-) ...

    tabela->vetor = calloc(tamanho, sizeof(Entrada));
    tabela->extra = calloc(tamanho, sizeof(Entrada)); // tamanho extra "a gosto"

    // Indicar que todas as entradas estao com suas ligacoes com uma proxima
    // chave sinonima como invalidas
    int i;
    for (i = 0; i < tamanho; ++i) {
        tabela->vetor[i].sinonima = tabela->extra[i].sinonima = FIM_SINONIMAS;
    }
    return tabela;
}

void destroi(Hash* tabela) {
    free(tabela->extra);
    free(tabela->vetor);
    free(tabela);
}

void inserir(Hash* tabela, const R* registro) {
    int onde = h(registro->chave, tabela->M); // usa a funcao de hashing para
                                              // definir o local no vetor
    Entrada* pEntrada = &tabela->vetor[onde];
    if (pEntrada->estado == OCUPADA) {
        // Tratamento de colisoes pela estrategia de encadeamento INTERIOR

        while (pEntrada->sinonima != FIM_SINONIMAS) { // equivalente ah busca pelo endereco
                                                      // NULL que faziamos na lista encadeada
            pEntrada = &tabela->extra[pEntrada->sinonima]; // aponta pra proxima entrada
            if (pEntrada->estado == LIVRE) { // encontrei uma posicao que foi liberada por
                                             // uma chave sinonima antiga ao ser removida
                break;
            }
        }
        if (pEntrada->estado == OCUPADA) { // terminou o laco sem achar uma livre
            // Ao chegar neste ponto, estou na ultima entrada da sequencia de sinonimas;
            // preciso encontrar uma posicao totalmente livre no vetor extra para usar
            int i;
            for (i = 0; i < tabela->P; ++i) {
                if (tabela->extra[i].estado == LIVRE &&
                    tabela->extra[i].sinonima == FIM_SINONIMAS) { // nao vou ocupar uma posicao
                                                                  // liberada por outra chave
                    break;
                }
            }
            if (i == tabela->P) {
                // Ao percorrer TODO o vetor extra nao se encontrou sequer uma posicao totalmente
                // livre; entao, realocamos o vetor extra com um tamanho adicional
                tabela->P *= 2; // dobramos o tamanho da area extra a cada lotacao desse vetor
                tabela->extra = realloc(tabela->extra, sizeof(Entrada)*tabela->P);
                int j;
                for (j = i; j < tabela->P; ++j) {
                    memset(&tabela->extra[j], 0, sizeof(Entrada)); // zera a nova entrada
                    tabela->extra[j].sinonima = FIM_SINONIMAS;
                }
            }
            // Vou comecar a ocupar a area expandida a partir do primeiro indice livre
            pEntrada->sinonima = i;
            pEntrada = &tabela->extra[i];
        }
    }
    memcpy(&pEntrada->dado, registro, sizeof(R));
    pEntrada->estado = OCUPADA;
}

// Ao inves de retornar o indice como antes, precisa retornar o ponteiro
// do registro, uma vez que ele pode estar em vetores diferentes ao longo da busca

R* busca(const Hash* tabela, unsigned chave) {
    int onde = h(chave, tabela->M); // usa a funcao de hashing pra recuperar o
                                    // local dessa chave na tabela
    Entrada* pEntrada = &tabela->vetor[onde];

    // Enquanto estiver na sequencia de chaves sinonimas (mesmo considerando as
    // liberadas que tem proximas)
    while ( pEntrada->estado == OCUPADA ||
           (pEntrada->estado == LIVRE && pEntrada->sinonima != FIM_SINONIMAS)) {

        // Existe registro nesta entrada?
        if (pEntrada->estado == OCUPADA && pEntrada->dado.chave == chave) {
            return &pEntrada->dado;
        }
        pEntrada = &tabela->extra[pEntrada->sinonima];
    }
    return NULL;
}

bool remover(Hash* tabela, R* destino, unsigned chave) {
    int onde = h(chave, tabela->M);
    Entrada* pEntrada = &tabela->vetor[onde];
    Entrada* pAnterior = NULL; // vai lembrar quem era a chave anterior para o caso de
                               // remocao do fim da sequencia (lista) de sinonimas

    // Enquanto estiver na sequencia de chaves sinonimas (mesmo considerando as
    // liberadas que tem proximas)
    while ( pEntrada->estado == OCUPADA ||
           (pEntrada->estado == LIVRE && pEntrada->sinonima != FIM_SINONIMAS)) {

        // Existe registro nesta entrada?
        if (pEntrada->estado == OCUPADA && pEntrada->dado.chave == chave) {
            // Encontrei a chave, vou remove-la da tabela
            memcpy(destino, &pEntrada->dado, sizeof(R));
            pEntrada->estado = LIVRE;

            // Se estiver removendo do FIM da sequencia (e nao do meio), significa
            // que vai se tornar uma entrada "totalmente" livre, disponivel inclusive
            // para outras chaves nao-sinonimas a esta; entao, precisa interromper a
            // sequencia na entrada anterior
            if (pEntrada->sinonima == FIM_SINONIMAS && pAnterior != NULL) {
                pAnterior->sinonima = FIM_SINONIMAS;
            }
            return true;
        }
        pAnterior = pEntrada;
        pEntrada = &tabela->extra[pEntrada->sinonima];
    }
    return false;
}

void debug(const Hash* tabela) {
    int i;
    for (i=0; i<tabela->M; ++i) {
        Entrada* pEntrada = &tabela->vetor[i];
        printf("[%d] ", i);
        while (pEntrada != NULL) {
            if (pEntrada->estado == OCUPADA) {
                printf("{%5u} ", pEntrada->dado.chave);
            } else {
                printf("{livre} ");
            }
            printf("--> [%d] ", pEntrada->sinonima);
            pEntrada = pEntrada->sinonima != FIM_SINONIMAS?
                       &tabela->extra[pEntrada->sinonima] : NULL;
        }
        putchar('\n');
    }
}

