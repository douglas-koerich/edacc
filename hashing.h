#ifndef HASHING_H_
#define HASHING_H_

#include <stdbool.h>
#include <stdlib.h>
#include "registro.h"

// Definicao opaca do TAD: tabela de dispersao, usada
// para armazenamento de registros e busca eficiente ~O(1)
struct Hash;
typedef struct Hash Hash;

// Operacoes do TAD
Hash* criar(size_t); // indica o tamanho da tabela a ser criada
void destruir(Hash*);
void inserir(Hash*, const Reg*);
bool remover(Hash*, Reg*);
size_t tamanho(const Hash*);
Reg* buscar(const Hash*, unsigned); // retorna o endereco do registro que possui chave
void imprimir(const Hash*);

#endif // HASHING_H_

