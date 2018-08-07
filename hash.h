#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include "registro.h"

struct hash;
typedef struct hash hash;

hash* cria_h(size_t t);
void destroi_h(hash* h);
void inserir_h(hash* h, const registro* r);
registro* busca_h(const hash* h, unsigned short x);
void imprime_h(const hash* h);

#endif  // HASH_H
