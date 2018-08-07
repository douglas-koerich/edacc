#ifndef _LISTA_CIRCULAR_H_
#define _LISTA_CIRCULAR_H_

#include <stdbool.h>

struct no {
	int valor;
	struct no* proximo;
};
typedef struct no No;
typedef struct no* Lista;

void inicia(Lista*);
void finaliza(Lista*);
bool underflow(const Lista*);
void insInicio(Lista*, int);
bool remInicio(Lista*, int*);
void insFim(Lista*, int);
bool remFim(Lista*, int*);
bool remValor(Lista*, int);
void imprime(const Lista*);
void insValor(Lista*, int);	// para lista ordenada

#endif

