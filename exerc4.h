#ifndef _EXERC4_H_
#define _EXERC4_H_

#include <stdbool.h>

#define MAX_TITULO	50

struct livro {
	int codigo;
	char titulo[MAX_TITULO+1];
	struct livro* proximo;
	struct livro* anterior;
};
typedef struct livro NohLista;
typedef NohLista* Lista;

void inicia(Lista*);
void finaliza(Lista*);
bool underflow(const Lista*);
void insere(Lista*, int, const char*);
void imprime(const Lista*);

#endif

