#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include "item.h"

struct hash;
typedef struct hash hash;

hash* create(size_t tamanho);
void destroy(hash* tabela);
item* search(const hash* tabela, int chave);
void insert(hash* tabela, const item* registro);
void extract(hash* tabela, item* registro, int chave);

void print(const hash* tabela);

#endif // HASH_H
