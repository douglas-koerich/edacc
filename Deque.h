#ifndef DEQUE_H
#define DEQUE_H

#include <stdlib.h>
#include <stdbool.h>

// Definicao do tipo: Deque (de caracteres)
struct Deque;

// Definicao das opcoes de lado da execucao da operacao
enum Lado {
	INICIO,
	FIM
};

// Definicao das operacoes (interface do TAD)
struct Deque* criar(size_t max);
void destruir(struct Deque* d);
bool add(struct Deque* d, enum Lado l, char c);
char del(struct Deque* d, enum Lado l);
bool underflow(struct Deque* d);
bool overflow(struct Deque* d);
void imprimir(struct Deque* d);

#endif	// DEQUE_H

