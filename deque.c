#include <stdio.h>
#include "deque.h"

void inicia(Deque* d, size_t tam) {
	d->vetor = (int*) calloc(tam, sizeof(int));	// "zera" a memoria
	d->max = tam;
	d->num = 0;
	d->cauda = -1;		// diferenca em
	d->cabeca = 0;		// relacao a 'inicio' e 'fim' na fila
}

bool underflow(const Deque* d) {
	return d->num == 0;
}

bool overflow(const Deque* d) {
	return d->num == d->max;
}

bool enqueue(Deque* d, Lado l, int novo) {
	if (overflow(d)) {
		return false;
	}
	if (l == CAUDA) {	// como na fila
		d->cauda = (d->cauda + 1) % d->max;
		d->vetor[d->cauda] = novo;
	}
	else {
		d->cabeca = (d->cabeca - 1 + d->max) % d->max;
		d->vetor[d->cabeca] = novo;
	}
	++d->num;
	return true;
}

bool dequeue(Deque* d, Lado l, int* valor) {
	if (underflow(d)) {
		return false;
	}
	if (l == CABECA) {	// como na fila
		*valor = d->vetor[d->cabeca];
		d->vetor[d->cabeca] = 0;	// no exemplo, usado como "vazio"
		d->cabeca = (d->cabeca + 1) % d->max;
	}
	else {
		*valor = d->vetor[d->cauda];
		d->vetor[d->cauda] = 0;	// no exemplo, usado como "vazio"
		d->cauda = (d->cauda - 1 + d->max) % d->max;
	}
	--d->num;
	return true;
}

void imprime(const Deque* d) {
	size_t i;
	for (i=0; i<d->max; ++i) printf(" %3u", i); putchar('\n');
	for (i=0; i<d->max; ++i) printf("----"); printf("-\n");
	for (i=0; i<d->max; ++i) {
		if (d->vetor[i]) printf("| %-2d", d->vetor[i]);
		else printf("|   ");
	}
	printf("|\n");
	for (i=0; i<d->max; ++i) printf("----"); printf("-\n");
}

void finaliza(Deque* d) {
	d->max = d->num = 0;
	free(d->vetor);
}

