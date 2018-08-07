#ifndef _LISTA_R_H_
#define _LISTA_R_H_

struct inteiro {
	int numero;
	struct inteiro* proximo;
};
typedef struct inteiro NohLista;
typedef NohLista* Lista;

void inicia(Lista*);
void finaliza(Lista*);
void insere(Lista*, int);
NohLista* busca_i(Lista, int);
NohLista* busca_r(NohLista*, int);

#endif

