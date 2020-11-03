#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "record.h"

// Algoritmos de ordenacao elementares (simples)
void bubble(Record*, size_t);
void selection(Record*, size_t);
void insertion(Record*, size_t);

// Algoritmos aprimorados
void shell(Record*, size_t);
void radix(Record*, size_t);

// Algoritmos eficientes (alto desempenho) -> recursivos!
void merge(Record*, int, int);
void quick(Record*, int, int);

#endif // SORT_H