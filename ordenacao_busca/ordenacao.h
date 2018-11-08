#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdlib.h> // para uso do size_t
#include "registro.h"

void bolha(Registro [*], size_t);
void selecao(Registro [*], size_t);
void insercao(Registro [*], size_t);

void radixsort(Registro [*], size_t);
void mergesort(Registro [*], int, int);
void quicksort(Registro [*], int, int);

#endif // ORDENACAO_H
