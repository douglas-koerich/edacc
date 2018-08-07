#ifndef _EXERC7_H_
#define _EXERC7_H_

#include <stdbool.h>

struct inteiro {
	int numero;
	struct inteiro* proximo;
};
typedef struct inteiro NoLista;

struct cabecalho {
	unsigned contador;
	NoLista* cabeca;
	NoLista* cauda;
};
typedef struct cabecalho Lista;

void inicia(Lista*);
void finaliza(Lista*);
void insFim(Lista*, int);
bool remInicio(Lista*, int*);
bool underflow(Lista*);
void imprime(Lista*);

Lista* intercala(Lista*, Lista*);

#endif

