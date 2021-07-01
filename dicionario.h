#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "registro.h"

// Definicao opaca de um TAD: dicionario/tabela de dispersao
struct Hash;
typedef struct Hash Hash;

// Operacoes associadas ao TAD
Hash* h_create(void);
void h_destroy(Hash*);
Registro* h_search(const Hash*, int);
void h_insert(Hash*, const Registro*);
void h_extract(Hash*, Registro*, int);
void h_print(const Hash*);

#endif // DICIONARIO_H