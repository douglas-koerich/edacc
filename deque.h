#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdbool.h>

// Definicao opaca do TAD para simples referencia de uso pela
// aplicacao que precisa do deque como estrutura de dados
// OBS.: 'T' eh um tipo qualquer, substitua por char, int, um
// registro especifico, etc.
struct DequeT;
typedef struct DequeT DequeT;

// Definicao das posicoes referentes as extremidades do deque
enum Extremo { FRENTE, TRAS };
typedef enum Extremo Extremo;

// Interface de uso do TAD, i.e., suas operacoes basicas
DequeT* cria(void);
void destroi(DequeT*);
void imprime(const DequeT*); // exibe a lista de elementos no deque
bool underflow(const DequeT*);
bool overflow(const DequeT*);
void enqueue(DequeT*, T, Extremo);
T dequeue(DequeT*, Extremo);

#endif

