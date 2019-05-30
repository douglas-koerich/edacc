#ifndef HASH_H_
#define HASH_H_

#include <stdbool.h>
#include <stdlib.h>
#include "registro.h" // Tipo de registro que eh armazenado/buscado

// TAD da funcionalide de armazenamento (insercao), busca e retirada (remocao)
// por tabela de hashing
typedef struct Hash Hash; // estrutura OPACA que implementa a tabela de hashing

// Interface de operacoes do TAD da tabela de hashing
Hash* cria(size_t); // indica o tamanho da tabela a ser criada
void destroi(Hash*);
bool inserir(Hash*, const R*);      // le do ponteiro para a tabela de hashing
                                    // (retorna false se posicao estava ocupada)
bool remover(Hash*, R*, unsigned);  // salva no ponteiro o que remove da tabela
                                    // com base na chave procurada
                                    // (retorna false se chave nao encontrada)
int busca(const Hash*, unsigned);   // retorna o indice da posicao onde estah a chave
                                    // (ou -1 se nao encontrada)

void debug(const Hash*); // imprime a tabela de hashing com seu conteudo atual

#endif // HASH_H_

