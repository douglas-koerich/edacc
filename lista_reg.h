#ifndef LISTA_REG_H
#define LISTA_REG_H

#include <stdbool.h>
#include <stdlib.h>
#include "registro.h"

struct Lista;
typedef struct Lista Lista;

enum Posicao {
    CABECA,      // para insercao (remocao) no (do) inicio da lista
    CAUDA,       // idem para o fim da lista
    CRESCENTE,   // para insercao em classificacao crescente dos elementos
    DECRESCENTE, // idem para classificacao decrescente
    FIXA         // para insercao (remoca) na (da) n-esima posicao da lista
};
typedef enum Posicao Posicao;

Lista* criar(void);
void destruir(Lista*);
void inserir(Lista*, const Reg*, Posicao, int);
bool remover(Lista*, Reg*, Posicao, int);
void remover_r(Lista*, unsigned); // remover o registro cuja chave eh passada
                                  // como parametro
bool underflow(const Lista*);
Reg* buscar(const Lista*, unsigned); // devolve o registro com a chave informada
size_t comprimento(const Lista*);

void imprimir(const Lista*);

void ordenar(Lista*); // reorganizar os nohs da lista em ordem crescente

#endif // LISTA_REG_H

