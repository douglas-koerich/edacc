#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>	// bool
#include <stdlib.h>		// size_t

// Somente a definicao da estrutura para permitir a compilacao
struct Deque;

// Duas extremidades (lados) onde pode-se executar a insercao/remocao
enum Lado { INICIO, FIM };	// INICIO=0, FIM=1

// Prototipos da interface do TAD
struct Deque* cria(size_t);
void destroi(struct Deque*);
bool overflow(const struct Deque*);				// deque cheio?
bool underflow(const struct Deque*);			// deque vazio?
bool inserir(struct Deque*, enum Lado, int);	// insere int no deque de int's
bool remover(struct Deque*, enum Lado, int*);	// remove do deque para endereco
void print(const struct Deque*);

#endif	// DEQUE_H
