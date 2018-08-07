/**
 * TAD: Lista encadeada simples
 * Este arquivo-fonte implementa a real estrutura de dados sem
 * que isto seja disponibilizado (visivel) ao usuario
 */

#include <stdio.h>
#include <stdlib.h>
#include "ListaE.h"

// Definicao do noh da lista
struct No {
	int elemento;
	struct No* proximo;
};
typedef struct No No;

// Definicao da lista enquanto estrutura de dados
struct Lista {
	No* cabeca;
};

// Implementacao das operacoes

struct Lista* criar(void) {
	struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
	l->cabeca = NULL;
	return l;
}

void destruir(struct Lista* l) {
	while (l->cabeca != NULL) {
		No* p = l->cabeca;
		l->cabeca = p->proximo;
		free(p);
	}
	free(l);
}

void imprimir(struct Lista* l) {
	if (l->cabeca == NULL) {
		puts("(vazia)");
		return;
	}
	putchar('\n');
	No* p = l->cabeca;
	while (p != NULL) {
		printf("%d-->", p->elemento);
		p = p->proximo;
	}
	puts("||");
}

// Retorna o endereco do elemento (nao do noh!) na lista,
// ou NULL (ponteiro invalido) se nao for encontrado
int* buscar(struct Lista* l, int valor) {
	No* p = l->cabeca;
	while (p != NULL) {
		if (p->elemento == valor) {
			return &p->elemento;
		}
		p = p->proximo;
	}
	return NULL;
}

// Retorna verdadeiro (1) se valor foi encontrado e removido,
// ou falso (0) se valor nao foi encontrado na lista
int remover_val(struct Lista* l, int valor) {
	if (l->cabeca == NULL) {
		return 0;
	}
	if (l->cabeca->elemento == valor) {
		No* p = l->cabeca;
		l->cabeca = p->proximo;
		free(p);
	}
	else {
		No* p = l->cabeca, * ant = NULL;
		while (p != NULL && p->elemento != valor) {
			ant = p;
			p = p->proximo;
		}
		if (p == NULL) {
			return 0;
		}
		ant->proximo = p->proximo;
		free(p);
	}
	return 1;
}

// Retorna verdadeiro (1) se valor foi acrescentado a lista, senao
// retorna falso (0) pois a lista estah cheia
int adicionar(struct Lista* l, int valor, enum Posicao pos) {
	No* p = (No*) malloc(sizeof(No));
	p->elemento = valor;
	switch (pos) {
		case INICIO:
			p->proximo = l->cabeca;
			l->cabeca = p;
			break;
			
		case FIM: {
			p->proximo = NULL;
			if (l->cabeca == NULL) {
				l->cabeca = p;
				break;	// termina o case!
			}
			No* q = l->cabeca;
			while (q->proximo != NULL) {
				q = q->proximo;
			}
			q->proximo = p;
			break;
		}
		
		default: {	// ORDEM
			if (l->cabeca == NULL) {
				p->proximo = NULL;
				l->cabeca = p;
				break;	// termina o default!
			}
			if (l->cabeca->elemento >= valor) {
				p->proximo = l->cabeca;
				l->cabeca = p;
				break;
			}
			No* q = l->cabeca, * ant = NULL;
			while (q != NULL && q->elemento < valor) {
				ant = q;
				q = q->proximo;
			}
			p->proximo = q;
			ant->proximo = p;
		}
	}
	return 1;
}

int remover(struct Lista* l, enum Posicao pos, int* valor) {
	if (l->cabeca == NULL) {
		return 0;
	}
	switch (pos) {
		case ORDEM:
			return 0;	// opcao invalida
			
		case INICIO: {
			No* p = l->cabeca;
			*valor = p->elemento;
			l->cabeca = p->proximo;
			free(p);
			break;
		}
		
		default: { // FIM
			if (l->cabeca->proximo == NULL) {
				*valor = l->cabeca->elemento;
				free(l->cabeca);
				l->cabeca = NULL;
			}	
			else {
				No* p = l->cabeca, * ant = NULL;
				while (p->proximo != NULL) {
					ant = p;
					p = p->proximo;
				}
				*valor = p->elemento;
				ant->proximo = NULL;
				free(p);
			}
		}
	}
	return 1;
}

int remover_npos(struct Lista* l, unsigned npos, int* valor) {
	if (l->cabeca == NULL) {
		return 0;
	}
	if (npos == 1) {
		No* p = l->cabeca;
		*valor = p->elemento;
		l->cabeca = p->proximo;
		free(p);
	}
	else {
		unsigned pos = 1;
		No *p = l->cabeca, * ant = NULL;
		while (pos < npos && p != NULL) {
			ant = p;
			p = p->proximo;
			++pos;
		}
		if (p == NULL) {
			return 0;
		}
		*valor = p->elemento;
		ant->proximo = p->proximo;
		free(p);
	}
	return 1;
}

