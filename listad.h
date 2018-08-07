#ifndef LISTAD_H
#define LISTAD_H

#include <stdbool.h>
#include <stdlib.h>
#include "tipo.h"

// TAD: Lista DUPLAMENTE ENCADEADA de elementos
struct Lista;

// Interface do TAD: lista
struct Lista* cria(void);
void destroi(struct Lista* l);          // destroi a lista passada como parametro
bool underflow(const struct Lista* l);  // testa se a lista estah vazia (nao eh possivel remover)
void imprime(const struct Lista* l);    // imprime a sequencia de elementos na tela

tipo* busca(const struct Lista* l, tipo val);   // busca pelo valor na lista devolvendo seu endereco na memoria
                                                // ou nulo (NULL) se nao esta contido na lista
// Diferentes opcoes de insercao na lista
bool inserirInicio(struct Lista* l, tipo val);  // insere como primeiro elemento da lista
bool inserirFim(struct Lista* l, tipo val);     // insere como ultimo elemento da lista
bool inserirPosicao(struct Lista* l, tipo val, size_t pos); // insere na pos-esima posicao (1..n) da lista
bool inserirOrdem(struct Lista* l, tipo val);   // para uso em listas classificadas em ordem crescente

// Diferentes opcoes de remocao da lista
bool removerInicio(struct Lista* l, tipo* pval);    // remove o primeiro elemento da lista
bool removerFim(struct Lista* l, tipo* pval);       // remove o ultimo elemento da lista
bool removerPosicao(struct Lista* l, tipo* pval, size_t pos); // remove da pos-esima posicao (1..n) da lista
bool removerValor(struct Lista* l, tipo val, size_t* ppos); // remove 'val', pondo em 'ppos' a posicao (1..n) onde encontrou

// Operacao de percurso reverso na lista
void imprime_r(const struct Lista* l);  // imprime a sequencia invertida de elementos na tela

#endif
