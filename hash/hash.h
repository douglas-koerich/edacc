#ifndef HASH_H
#define HASH_H

#include "registro.h"

// Definicao opaca do tipo abstrato de dados "Hash"
struct Hash;
typedef struct Hash Hash;

// Operacoes de manipulacao (interface do TAD) com a tabela de
// espalhamento/dispersao/hash
Hash* criar(void);
void destruir(Hash* hash);
void inserir(Hash* hash, const R* novo);
void retirar(Hash* hash, unsigned chave);
const R* buscar(const Hash* hash, unsigned chave);
void imprimir(const Hash* hash);

#endif // HASH_H

