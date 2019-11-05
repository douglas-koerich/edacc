#ifndef ALG_ORDENACAO_H
#define ALG_ORDENACAO_H

#include <stdlib.h>
#include "registro.h"

void bolha(Reg [*], size_t); // tamanho do vetor
void selecao(Reg [*], size_t);
void insercao(Reg [*], size_t);
void shellsort(Reg [*], size_t);
void radixsort(Reg [*], size_t);
void mergesort(Reg [*], int, int); // indices das extremidades do [trecho de] vetor
void quicksort(Reg [*], int, int); // variacao nao-recursiva: TENENBAUM pag. 504

#endif // ALG_ORDENACAO_H
