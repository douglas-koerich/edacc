#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdlib.h>
#include <string.h>
#include "registro.h"

// Use \ em macros para poder fazer em varias linhas
#define TROCA(r1, r2) (\
    { \
        Registro aux; \
        memcpy(&aux, &(r1), sizeof(Registro)); \
        memcpy(&(r1), &(r2), sizeof(Registro)); \
        memcpy(&(r2), &aux, sizeof(Registro)); \
    })

void bubble(Registro*, size_t);
void selection(Registro*, size_t);
void insertion(Registro*, size_t);

void shellsort(Registro*, size_t);
void radixsort(Registro*, size_t);

void mergesort(Registro*, int, int);
void quicksort(Registro*, int, int);

#endif // ORDENACAO_H