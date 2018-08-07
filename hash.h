#ifndef HASH_H
#define HASH_H

#include <stdbool.h>

// Definicao do registro armazenado
struct registro {
    int chave;
    char dado;
};
typedef struct registro Registro;

// Definicao do TAD: tabela hash
typedef struct hash Hash;

// Interface do TAD:
Hash* criar(size_t tamanho);
void destruir(Hash* tabela);
bool overflow(const Hash* tabela);
bool inserir(Hash* tabela, const Registro* novo);
void remover(Hash* tabela, int chave);
Registro* buscar(const Hash* tabela, int chave);
void imprimir(const Hash* tabela);

#endif
