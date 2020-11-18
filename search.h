#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include "record.h"

// Algoritmos de pesquisa (busca) - retorno eh o indice da chave encontrada
int sequential(const Record*, size_t, int);
int binary(const Record*, int, int, int);
int interpolation(const Record*, int, int, int);

// TAD: Tabela de espalhamento (busca por hashing)
struct Dictionary_;
typedef struct Dictionary_ Dictionary;

Dictionary* create(size_t max_elements);
void destroy(Dictionary* dictionary);
void insert(Dictionary* dictionary, const Record* new_element);
Record* discard(Dictionary* dictionary, int search_key);
Record* find(const Dictionary* dictionary, int search_key);

#endif // SEARCH_H