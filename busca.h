#ifndef BUSCA_H
#define BUSCA_H

#include <stdlib.h>
#include "registro.h"

int sequencial(const Registro*, size_t, int);
int binaria(const Registro*, int, int, int);
int interpolacao(const Registro*, int, int, int);
int espalhamento(const Registro*, size_t, int);

#endif // BUSCA_H