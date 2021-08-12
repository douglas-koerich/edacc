#ifndef WARMUP_H
#define WARMUP_H

enum criterio {
    INICIO,
    FIM,
    EM_ORDEM,
    VALOR
};
typedef enum criterio criterio;

#include <stdbool.h>    // para referencia do tipo 'bool'
#include <stdlib.h>     // para referencia do tipo 'size_t'

// Tipo ABSTRATO (conceitual) de Dado: conjunto de numeros inteiros
struct lista;   // definicao oculta ("opaca") de uma lista de numeros
typedef struct lista lista;

lista* cria(size_t maximo);         // retorna o endereco de inicio da nova lista
void destroi(lista* l);             // recebe a referencia da lista a ser destruida
size_t comprimento(const lista* l); // retorna o numero de elementos armazenados (nao a capacidade)
bool vazio(const lista* l);         // retorna resultado do teste se lista estah vazia
void imprime(const lista* l);       // imprime a sequencia de elementos armazenados
int busca(const lista* l, int v);   // retorna o indice do valor procurado (ou -1 se nao for encontrado)
void insere(lista* l, int v, criterio o); // adiciona o novo valor no local indicado da lista
int retira(lista* l, criterio o, int v);  // remove um valor da lista segundo o criterio (opcao) indicado

#endif // WARMUP_H