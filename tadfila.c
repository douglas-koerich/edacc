#include <stdio.h>
#include "tadfila.h"

struct Fila {
	int* vetor;
	size_t max;
	int inicio, fim;
};

struct Fila* cria(size_t tamanho) {
	struct Fila* f = (struct Fila*) malloc(sizeof(struct Fila));
	/* Fila linear:
	f->vetor = (int*) malloc(tamanho*sizeof(int));
	f->max = tamanho;
	*/
	// Fila circular: reserva 1 posicao para o "sacrificio"
	f->vetor = (int*) malloc((tamanho+1)*sizeof(int));
	f->max = tamanho+1;
	/* Fila linear (nao circular)
	f->inicio = 0;	// se inicio > fim, fila estah vazia
	f->fim = -1;
	*/
	// Fila circular
	f->fim = f->max-1;	// o indice anterior a 0 (zero) eh o 
						// indice da ultima posicao do vetor
	f->inicio = f->max-1;	// para evitar o "falsa vazia"
							// quando f->fim voltou ao indice 0
							// agora, fila vazia: inicio=fim e
							// inicio eh o indice ANTERIOR ao
							// elemento que sera removido
	return f;
}

void destroi(struct Fila* f) {
	free(f->vetor);
	free(f);
}

bool underflow(const struct Fila* f) {
	/* Fila linear:
	return f->inicio > f->fim;
	*/
	// Fila circular:
	return f->inicio == f->fim;
}

bool overflow(const struct Fila* f) {
	/* Fila linear:
	return f->fim == f->max-1;
	*/
	if (f->inicio == 0) {
		return f->fim == f->max-1;
	}
	else {
		return f->fim == f->inicio - 1;
	}
}

bool enqueue(struct Fila* f, int novo) {
	if (overflow(f)) {
		return false;
	}
	// Semelhante ao push da pilha
	/* Fila linear:
	++f->fim;
	*/
	// Fila circular:
	if (f->fim == f->max-1) {
		f->fim = 0;	// "proxima posicao" eh no inicio do vetor
	}
	else {
		++f->fim;
	}
	f->vetor[f->fim] = novo;
	return true;
}

bool dequeue(struct Fila* f, int* endereco) {
	if (underflow(f)) {
		return false;
	}
	// Diferentemente da pilha, o indice de referencia para
	// remocao eh incrementado (e nao decrementado) apos a
	// operacao
	// Fila circular: o indice de inicio estah "apontando" para
	// a posicao ANTERIOR ao elemento que sera removido
	if (f->inicio == f->max-1) {
		f->inicio = 0;	// "proxima posicao" eh no inicio do vetor
	}
	else {
		++f->inicio;
	}
	*endereco = f->vetor[f->inicio];
	/* Fila linear: o incremento do inicio era feito DEPOIS do
	 * acesso ao elemento
	++f->inicio;
	*/
	return true;
}

void print(const struct Fila* f) {
	printf("Inicio--| ");
	int i;
	/* Fila linear:
	for (i=f->inicio; i<=f->fim; ++i) {
		printf("%d ", f->vetor[i]);
	}
	printf("|--Fim\n");
	printf("Existem %d posicoes livres no vetor\n",
		   f->max - (f->fim - f->inicio + 1));
	*/
	int contador = 0;
	i = f->inicio;
	while (i != f->fim) {
		if (i == f->max-1) i = 0;
		else ++i;
		printf("%d ", f->vetor[i]);
		++contador;
	}
	printf("|--Fim\n");
	printf("Existem %d posicoes livres no vetor\n",
		   f->max - 1 - contador);
}

