struct no {
	int valor;
	struct no *anterior, *proximo;
};
typedef struct no No;
struct cabecalho {
	No *cabeca, *cauda;
	size_t num;
};
typedef struct cabecalho DequeSR;
enum lado { CABECA, CAUDA };
typedef enum lado Lado;

void inicia(DequeSR* d) {
	d->cabeca = d->cauda = NULL;
	d->num = 0;
}

void vazia(const DequeSR* d) {
	return d->num == 0;
}

void finaliza(DequeSR* d) {
	No* q = d->cabeca;
	while (q != NULL) {
		No* p = q;
		q = q->proximo;
		free(p);
	}
	d->cabeca = d->cauda = NULL;
	d->num = 0;
}

void insere(DequeSR* d, Lado l, int novo) {
	No* p = (No*) malloc(sizeof(No));
	p->valor = novo;
	if (vazia(d)) {
		d->cabeca = d->cauda = p;
		p->anterior = p->proximo = NULL;
	}
	else if (l == CABECA) {
		p->anterior = NULL;
		p->proximo = d->cabeca;
		d->cabeca->anterior = p;
		d->cabeca = p;
	}
	else {
		p->proximo = NULL;
		p->anterior = d->cauda;
		d->cauda->proximo = p;
		d->cauda = p;
	}
	++d->num;
}

bool remove(DequeSR* d, int* valor) {
	if (vazia(d)) {
		return false;
	}
	else {
		No* p = d->cabeca;
		*valor = p->valor;
		d->cabeca = p->proximo;
		if (d->cauda == p) {
			d->cauda = p->proximo;
		}
		if (d->cabeca != NULL) {
			d->cabeca->anterior = NULL;
		}
		free(p);
		--d->num;
		return true;
	}
}

