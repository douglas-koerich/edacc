#ifndef L5E1_H
#define L5E1_H

// Definicao da lista encadeada
#include <stdbool.h>
#include <stdlib.h>
#include "record.h"

struct List_;
typedef struct List_ List;

List* create(void);
void destroy(List* list);
void insert(List* list, const Record* new_element);
Record* discard(List* list);
bool underflow(const List* list);
size_t size(const List* list);
void print(const List* list);
void sort(List* list);

// Ao inves de uma funcao, uma MACRO para a operacao de troca entre posicoes
#define swap(r1, r2) \
    Record* rtemp = malloc(sizeof(Record)); \
    memcpy(rtemp, (r1), sizeof(Record)); \
    memcpy((r1), (r2), sizeof(Record)); \
    memcpy((r2), rtemp, sizeof(Record)); \
    free(rtemp);

#endif // L5E1_H