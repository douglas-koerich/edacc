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
Hash* h_criar(size_t); // indica o tamanho da tabela a ser criada
void h_destruir(Hash*);
void h_inserir(Hash*, const Reg*);
void h_remover(Hash*, unsigned); // remove o registro que possui a chave
size_t h_tamanho(const Hash*);
Reg* h_buscar(const Hash*, unsigned); // retorna o endereco do registro que possui chave
void h_imprimir(const Hash*);

#endif // HASHING_H_

