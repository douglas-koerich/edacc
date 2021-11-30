#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>
#include "item.h"

struct list;
typedef struct list list;

list* l_create(void);
void l_destroy(list* l);
void l_insert(list* l, const item* i);
bool l_extract(list* l, item* i, int k);
item* l_search(const list* l, int k);
size_t l_size(const list* l);
bool l_underflow(const list* l);
void l_print(const list* l);

#endif // LISTA_H