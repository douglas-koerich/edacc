#ifndef _EXERC5LISTA_H_
#define _EXERC5LISTA_H_

// TAD: lista duplamente encadeada com cabecalho
struct inteiro {
	int numero;
	struct inteiro* anterior;
	struct inteiro* proximo;
};
typedef struct inteiro Noh;

struct cabecalho {
	unsigned tamanho;
	Noh* cabeca;
	Noh* cauda;
};
typedef struct cabecalho Lista;

// Apenas as operacoes do TAD necessarias a execucao do programa
void inicia(Lista*);
void finaliza(Lista*);
void insere(Lista*, int);	// insere no inicio
void ordena(Lista*);
void imprime(Lista*);

#endif

