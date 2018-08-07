#include <stdlib.h>
#include "lista.h"

/*
 * Lista encadeada SIMPLES
 */

void ls_criar(Lista* l) {
	*l = NULL;
}

void ls_destruir(Lista* l) {
	while (*l) {
		No* n = *l;
		*l = n->proximo;
		free(n);
	}
}

No* ls_buscar(Lista l, int v) {
	No* n = l;
	while (n && n->elemento != v) {
		n = n->proximo;
	}
	return n;
}

int ls_insInicio(Lista* l, int v) {
	No* n = (No*) malloc(sizeof(No));
	if (!n) {
		return 0;	/* Falha ao criar o novo no */
	}
	n->elemento = v;
	n->proximo = *l;
	*l = n;
	return 1;
}

int ls_insFim(Lista* l, int v) {
	No* n = (No*) malloc(sizeof(No));
	if (!n) {
		return 0;
	}
	n->elemento = v;
	n->proximo = NULL;
	if (!*l) {
		*l = n;
	}
	else {
		No* p = *l;
		while (p->proximo) {
			p = p->proximo;
		}
		p->proximo = n;
	}
	return 1;
}

int ls_remInicio(Lista* l, int* ev) {
	No* n = *l;
	if (!n) {
		return 0;	/* Lista vazia */
	}
	*ev = n->elemento;
	*l = n->proximo;
	free(n);
	return 1;
}

int ls_remFim(Lista* l, int* ev) {
	No** p = l;
	No* n = *p;
	if (!n) {
		return 0;	/* Lista vazia */
	}
	while (n->proximo) {
		p = &n->proximo;
		n = n->proximo;
	}
	*ev = n->elemento;
	*p = NULL;
	free(n);
	return 1;
}

/*
 * Lista encadeada com cabecalho
 */

void lh_criar(ListaH* cab) {
	cab->tamanho = 0;
	cab->cabeca = NULL;
}

void lh_destruir(ListaH* cab) {
	while (cab->cabeca) {
		No* n = cab->cabeca;
		cab->cabeca = n->proximo;
		free(n);
	}
	cab->tamanho = 0;
}

No* lh_buscar(const ListaH* cab, int v) {
	No* n = cab->cabeca;
	while (n && n->elemento != v) {
		n = n->proximo;
	}
	return n;
}

int lh_insInicio(ListaH* cab, int v) {
	No* n = (No*) malloc(sizeof(No));
	if (!n) {
		return 0;	/* Falha ao criar o novo no */
	}
	n->elemento = v;
	n->proximo = cab->cabeca;
	cab->cabeca = n;
	++cab->tamanho;
	return 1;
}

int lh_insFim(ListaH* cab, int v) {
	No* n = (No*) malloc(sizeof(No));
	if (!n) {
		return 0;
	}
	n->elemento = v;
	n->proximo = NULL;
	if (!cab->cabeca) {
		cab->cabeca = n;
	}
	else {
		No* p = cab->cabeca;
		while (p->proximo) {
			p = p->proximo;
		}
		p->proximo = n;
	}
	++cab->tamanho;
	return 1;
}

int lh_remInicio(ListaH* cab, int* ev) {
	No* n = cab->cabeca;
	if (!n) {
		return 0;	/* Lista vazia */
	}
	*ev = n->elemento;
	cab->cabeca = n->proximo;
	--cab->tamanho;
	free(n);
	return 1;
}

int lh_remFim(ListaH* cab, int* ev) {
	No** p = &cab->cabeca;
	No* n = *p;
	if (!n) {
		return 0;	/* Lista vazia */
	}
	while (n->proximo) {
		p = &n->proximo;
		n = n->proximo;
	}
	*ev = n->elemento;
	*p = NULL;
	--cab->tamanho;
	free(n);
	return 1;
}

/*
 * Lista encadeada CIRCULAR 
 */

void lc_criar(ListaC* l) {
	*l = NULL;
}

void lc_destruir(ListaC* l) {
	while (*l) {
		No* n = *l;
		*l = n->proximo;
		if (*l == *l) {
			*l = NULL;
		}
		free(n);
	}
}

No* lc_buscar(ListaC l, int v) {
	No* n = l;
	if (!n) {
		return NULL;
	}
	do {
		if (n->elemento == v) {
			return n;
		}
		n = n->proximo;
	}
	while (n != l);
	return NULL;
}

int lc_insInicio(ListaC* l, int v) {
	No* n = (No*) malloc(sizeof(No));
	if (!n) {
		return 0;	/* Falha ao criar o novo no */
	}
	n->elemento = v;
	if (*l) {
		n->proximo = (*l)->proximo;
	}
	else {
		*l = n;
	}
	(*l)->proximo = n;
	return 1;
}

int lc_insFim(ListaC* l, int v) {
	No* n = (No*) malloc(sizeof(No));
	if (!n) {
		return 0;
	}
	n->elemento = v;
	n->proximo = *l? *l: n;
	*l = n;
	return 1;
}

int lc_remInicio(ListaC* l, int* ev) {
	No* n;
	if (!*l) {
		return 0;	/* Lista vazia */
	}
	n = (*l)->proximo;
	(*l)->proximo = n->proximo;
	free(n);
	if (*l == n) {
		*l = NULL;
	}
	return 1;
}

int lc_remFim(ListaC* l, int* ev) {
	No* n = *l;
	if (!n) {
		return 0;	/* Lista vazia */
	}
	do {
		*l = (*l)->proximo;
	}
	while ((*l)->proximo != n);
	free(n);
	if (*l == n) {
		*l = NULL;
	}
	return 1;
}

/*
 * Lista encadeada DUPLA 
 */

void ld_criar(ListaD* l) {
	*l = NULL;
}

void ld_destruir(ListaD* l) {
	while (*l) {
		DNo* n = *l;
		*l = n->proximo;
		free(n);
	}
}

DNo* ld_buscar(ListaD l, int v) {
	DNo* n = l;
	while (n && n->elemento != v) {
		n = n->proximo;
	}
	return n;
}

int ld_insInicio(ListaD* l, int v) {
	DNo* n = (DNo*) malloc(sizeof(DNo));
	if (!n) {
		return 0;	/* Falha ao criar o novo no */
	}
	n->elemento = v;
	n->proximo = *l;
	n->anterior = NULL;
	*l = n;
	return 1;
}

int ld_insFim(ListaD* l, int v) {
	DNo* n = (DNo*) malloc(sizeof(DNo));
	if (!n) {
		return 0;
	}
	n->elemento = v;
	n->proximo = n->anterior = NULL;
	if (!*l) {
		*l = n;
	}
	else {
		DNo* p = *l;
		while (p->proximo) {
			p = p->proximo;
		}
		p->proximo = n;
		n->anterior = p;
	}
	return 1;
}

int ld_remInicio(ListaD* l, int* ev) {
	DNo* n = *l;
	if (!n) {
		return 0;	/* Lista vazia */
	}
	*ev = n->elemento;
	*l = n->proximo;
	if (*l) {
		(*l)->anterior = NULL;
	}
	free(n);
	return 1;
}

int ld_remFim(ListaD* l, int* ev) {
	DNo** p = l;
	DNo* n = *p;
	if (!n) {
		return 0;	/* Lista vazia */
	}
	while (n->proximo) {
		p = &n->proximo;
		n = n->proximo;
	}
	*ev = n->elemento;
	*p = NULL;
	free(n);
	return 1;
}

