#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>
#include "registro.h"

enum criterio { // criterio de operacao(oes) da lista
    CABECA, // inicio da lista
    CAUDA,  // fim da lista
    CRESCENTE, // (exclusivo para insercao) em ordem crescente
    DECRESCENTE, // (idem) em ordem decrescente
    ORDINAL, // primeiro, segundo, etc.
    VALOR // (exclusivo para remocao) valor especifico da chave
};
typedef enum criterio Criterio;

struct lista;
typedef struct lista Lista;

Lista* create(void);
void destroy(Lista*);

bool underflow(const Lista*);
size_t size(const Lista*);
void print(const Lista*);
void rprint(const Lista*); // impressao no sentido reverso (a partir da cauda)

// A insercao pode ser feita de maneiras diferentes (livres)
void insert(Lista*, const Registro*, Criterio, unsigned);

// Idem para remocao (retorno vem pelo parametro-ponteiro para Registro)
// No caso de remocao por valor, a chave vai dentro do parametro Registro
void extract(Lista*, Registro*, Criterio, unsigned);

// Pesquisa por valor de chave (int) especifico, preenchendo o registro
// se encontrado (indicado pelo retorno V/F)
bool search(const Lista*, int, Registro*);

// Exercicio 2 da lista proposta
bool compare(const Lista*, const Lista*);

#endif