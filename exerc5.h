#ifndef _EXERC5_H_
#define _EXERC5_H_

#include <stdbool.h>

struct inteiro {
	int numero;
	struct inteiro* proximo;
};
typedef struct inteiro NoLista;
typedef NoLista* Lista;

void l_inicia(Lista* l);
void l_finaliza(Lista* l);
void l_insFim(Lista*, int novo);
bool l_remInicio(Lista*, int* removido);
void l_imprime(Lista*);
bool l_underflow(Lista* l);
void l_inverte(Lista* l);

#define MAX_PILHA 100

struct pilha {
	int vetor[MAX_PILHA];
	int topo;
};
typedef struct pilha Pilha;

void inicia(Pilha* p);
bool push(Pilha* p, int novo);
bool pop(Pilha* p, int* removido);
bool underflow(Pilha* p);
bool overflow(Pilha* p);

#endif

