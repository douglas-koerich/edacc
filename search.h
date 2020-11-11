#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include "record.h"

// Algoritmos de pesquisa (busca) - retorno eh o indice da chave encontrada
int sequential(const Record*, size_t, int);
int binary(const Record*, int, int, int);
int interpolation(const Record*, int, int, int);

// TAD: Tabela de espalhamento (busca por hashing)

#endif // SEARCH_H