#include "pilha.h"

void p_inicia(Pilha* p, size_t tam) {
	p->max = tam;
	p->vetor = (int*) malloc(tam*sizeof(int));
	p->topo = -1;
}

bool p_underflow(const Pilha* p) {
	return p->topo == -1;
}

bool p_overflow(const Pilha* p) {
	return p->topo == p->max-1;
}

bool push(Pilha* p, int novo) {
	if (p_overflow(p)) {
		return false;
	}
	p->vetor[++p->topo] = novo;
	return true;
}

bool pop(Pilha* p, int* endvar) {
	if (p_underflow(p)) {
		*endvar = -1;	// opcional
		return false;
	}
	*endvar = p->vetor[p->topo--];
	return true;
}

void p_finaliza(Pilha* p) {
	free(p->vetor);
	p->max = 0;	// por seguranca
	p->topo = -1;
}

