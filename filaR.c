#include <stdlib.h>
#include <string.h>
#include "filaR.h"

// No da fila na forma encadeada
struct No {
	Registro elemento;
	struct No* proximo;
	struct No* anterior;
};
typedef struct No No;

// Definicao do TAD: Fila de registros
struct Fila {
	No* inicio;
	No* fim;
};

// Operacoes do TAD

struct Fila* criar(void) {
	struct Fila* f = (struct Fila*) malloc(sizeof(struct Fila));
	f->inicio = f->fim = NULL;
	return f;
}

void destruir(struct Fila* f) {
	while (f->inicio != NULL) {
		No* p = f->inicio;
		f->inicio = p->proximo;
		free(p);
	}
	free(f);
}

bool underflow(struct Fila* f) {
	return f->inicio == NULL;
}

bool enqueue(struct Fila* f, const Registro* reg) {
	No* p = (No*) malloc(sizeof(No));
	p->proximo = NULL;
	p->anterior = f->fim;
	memcpy(&p->elemento, reg, sizeof(Registro));
	if (f->fim != NULL) {
		(f->fim)->proximo = p;	// f->fim eh o ultimo noh atual, que deve passar
								// a apontar para o NOVO ultimo noh (criado)
	}
	if (f->inicio == NULL) {	// fila estava vazia antes desse novo elemento?
		f->inicio = p;			// entao o novo noh eh inicio e fim ao mesmo tempo
	}
	f->fim = p;
	return true;
}

bool dequeue(struct Fila* f, Registro* reg) {
	if (underflow(f)) {
		return false;
	}
	No* p = f->inicio;		// salva o ponteiro para o primeiro noh que sera removido
	f->inicio = p->proximo;	// novo inicio sera o proximo (segundo) noh
	if (f->inicio != NULL) {	// existe de fato esse segundo noh (nao salvou NULL)?
		f->inicio->anterior = NULL;
	}
	else {	// fila ficou vazia, marca isso tambem no ponteiro para o ultimo
		f->fim = NULL;
	}
	memcpy(reg, &p->elemento, sizeof(Registro));
	free(p);
	return true;
}

