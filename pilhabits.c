#include "pilhabits.h"

#define MAX_BITS 128

struct Pilha {
	bit sequencia[MAX_BITS];
	size_t max;
	int topo;
};

struct Pilha* cria(size_t numBits) {
	if (numBits > MAX_BITS) {
		return NULL;	// tamanho invalido, nao ha como
						// respeitar o parametro solicitado
	}
	struct Pilha* pilha = (struct Pilha*) malloc(sizeof(struct Pilha));
	pilha->max = numBits;
	pilha->topo = -1;
	return pilha;
}

void destroi(struct Pilha* pilha) {
	free(pilha);
}

bool underflow(const struct Pilha* pilha) {
	return pilha->topo == -1;
}

bool overflow(const struct Pilha* pilha) {
	return pilha->topo == pilha->max - 1;
}

bool push(struct Pilha* pilha, bit novo) {
	if (overflow(pilha)) {
		return false;
	}
	pilha->sequencia[++pilha->topo] = novo;
	return true;
}

bool pop(struct Pilha* pilha, bit* digito) {
	if (underflow(pilha)) {
		return false;
	}
	if (digito == NULL) {	// robustez da biblioteca
		return false;
	}
	*digito = pilha->sequencia[pilha->topo--];
	return true;
}

