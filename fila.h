#ifndef _FILA_H_
#define _FILA_H_

#include <stdbool.h>

// Definicao opaca do TAD para simples referencia de uso pela
// aplicacao que precisa da fila como estrutura de dados
// OBS.: 'T' eh um tipo qualquer, substitua por char, int, um
// registro especifico, etc.
struct FilaT;
typedef struct FilaT FilaT;

// Interface de uso do TAD, i.e., suas operacoes basicas
FilaT* cria(void);
void destroi(FilaT*);
void imprime(const FilaT*); // exibe a lista de elementos na fila
bool underflow(const FilaT*);
bool overflow(const FilaT*);
void enqueue(FilaT*, T);
T dequeue(FilaT*);

#endif

