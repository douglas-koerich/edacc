#ifndef HASH_H
#define HASH_H

#include <stdbool.h>
#include <stdlib.h>
#include "registro.h"

// Definicao opaca da estrutura do TAD
typedef struct HashReg HashReg;

HashReg* cria(size_t tamanho_tabela);
void destroi(HashReg* hash);
void insere(HashReg* hash, const Reg* reg);
const Reg* busca(const HashReg* hash, const char chave[]);
Reg exclui(HashReg* hash, const char chave[]);
void imprime(const HashReg* hash);

#endif // HASH_H

