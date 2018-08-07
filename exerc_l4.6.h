#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdbool.h>

struct Lista;
typedef struct Lista Lista;

enum Extremidade { INICIO, FIM };
typedef enum Extremidade Extremidade;

// Para simplificar, vamos usar uma lista simples de
// numeros inteiros

Lista* cria(void);
void destroi(Lista*);
bool underflow(const Lista*);
void insere(Lista*, Extremidade, int);
int exclui(Lista*, Extremidade);
void imprime(const Lista*);
size_t tamanho(const Lista*);   // funcao recursiva

#endif
