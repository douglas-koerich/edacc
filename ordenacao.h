#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdlib.h>
#include "registro.h"

void swap(Registro*, Registro*);
void bubble(Registro [*], size_t);
void select_(Registro [*], size_t);	// pra nao conflitar com select do Linux
void insert(Registro [*], size_t);
void shell(Registro [*], size_t);
void radix(Registro [*], size_t);
void merge(Registro [*], int, int);	// indices de inicio e fim do segmento
void quick(Registro [*], int, int); // idem: sao chamadas recursivas!

#endif

