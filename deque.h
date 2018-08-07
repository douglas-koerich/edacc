#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdlib.h>
#include <stdbool.h>

enum lado {
	CABECA,
	CAUDA
};
typedef enum lado Lado;

struct deque {
	int* vetor;
	size_t max, num;
	int cabeca, cauda;
};
typedef struct deque Deque;

void inicia(Deque*, size_t);
bool underflow(const Deque*);
bool overflow(const Deque*);
bool enqueue(Deque*, Lado, int);
bool dequeue(Deque*, Lado, int*);
void imprime(const Deque*);
void finaliza(Deque*);

#endif

