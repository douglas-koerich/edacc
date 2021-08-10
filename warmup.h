#ifndef WARMUP_H
#define WARMUP_H

#define MAX_ELEMENTOS 100

// Opcoes de insercao/remocao
/*
#define INICIO 0
#define FIM 1
#define EM_ORDEM 2
#define VALOR 3
*/
enum criterio {
    INICIO,
    FIM,
    EM_ORDEM,
    VALOR
};
typedef enum criterio criterio;

#include <stdbool.h>    // para referencia do tipo 'bool'
#include <stdlib.h>     // para referencia do tipo 'size_t'

int* cria(size_t maximo);               // retorna o endereco de inicio do novo vetor
void destroi(int* vetor);               // recebe a referencia (endereco) do vetor a ser destruido
size_t comprimento(const int* vetor);   // retorna o numero de elementos armazenados (nao a capacidade)
bool vazio(const int* vetor);           // retorna resultado do teste se vetor estah vazio
void imprime(const int* vetor);         // imprime a sequencia de elementos armazenados
int busca(const int* vetor, int valor); // retorna o indice do valor procurado (ou -1 se nao for encontrado)
void insere(int* vetor, int valor, criterio opcao); // adiciona o novo valor no local indicado do vetor
int retira(int* vetor, criterio opcao, int valor);  // remove um valor do vetor segundo o criterio (opcao) indicado

#endif // WARMUP_H