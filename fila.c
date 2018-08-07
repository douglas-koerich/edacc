#include <stdio.h>
#include "fila.h"

void f_inicia(Fila* f, size_t tam) {
	f->max = tam+1;
	f->vetor = (int*) malloc(f->max * sizeof(int));
	f->inicio = f->fim = f->max-1;
}

void f_finaliza(Fila* f) {
	f->max = 0;
	f->inicio = f->fim = -1;
	free(f->vetor);
}

bool f_underflow(const Fila* f) {
	return f->fim == f->inicio;
}

bool f_overflow(const Fila* f) {
	return f->fim == (f->inicio - 1 + f->max) % f->max;
}

bool enqueue(Fila* f, int novo) {
	if (f_overflow(f))
		return false;
	f->fim = (f->fim + 1) % f->max;
	f->vetor[f->fim] = novo;
	return true;
}

bool dequeue(Fila* f, int* valor) {
	if (f_underflow(f))
		return false;
	f->inicio = (f->inicio + 1) % f->max;
	*valor = f->vetor[f->inicio];
	return true;
}

void f_imprime(const Fila* f) {
	int indice;
	if (f_underflow(f)) {
		puts("Fila vazia!");
		return;
	}
	for (indice = (f->inicio + 1) % f->max;
		 indice != f->fim;
		 indice = (indice + 1) % f->max) {
		printf("%d ", f->vetor[indice]);
	}
	printf("%d\n", f->vetor[f->fim]);
}

size_t f_tamanho(const Fila* f) {
	return f->max;
}

