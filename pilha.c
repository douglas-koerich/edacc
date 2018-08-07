#include "pilha.h"

void inicia(Pilha* p, size_t tam) {
	p->max = tam;
	p->vetor = (char*) malloc(tam*sizeof(char));
	p->topo = -1;
}

bool underflow(const Pilha* p) {
	return p->topo == -1;
}

bool overflow(const Pilha* p) {
	return p->topo == p->max-1;
}

bool push(Pilha* p, char novo) {
	if (overflow(p)) {
		return false;
	}
	p->vetor[++p->topo] = novo;
	return true;
}

bool pop(Pilha* p, char* endvar) {
	if (underflow(p)) {
		*endvar = '\0';	// opcional
		return false;
	}
	*endvar = p->vetor[p->topo--];
	return true;
}

void finaliza(Pilha* p) {
	free(p->vetor);
	p->max = 0;	// por seguranca
	p->topo = -1;
}

