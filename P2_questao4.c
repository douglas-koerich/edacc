#include <stdlib.h>
#include <stdio.h>

struct noh_lista {
	int valor;
	struct noh_lista* proximo;
	struct noh_lista* anterior;
};
typedef struct noh_lista Noh;

struct cabecalho {
	Noh* cabeca;
	Noh* cauda;
};
typedef struct cabecalho Lista;

void inserir(Lista* l, int novo) {	// insercao no inicio
	Noh* p = (Noh*) malloc(sizeof(Noh));
	p->valor = novo;
	p->anterior = NULL;
	p->proximo = l->cabeca;
	if (l->cabeca != NULL) {
		l->cabeca->anterior = p;
	}
	l->cabeca = p;
	if (l->cauda == NULL) {
		l->cauda = p;
	}
}

void imprimir(Lista* l) {
	Noh* p = l->cabeca;
	while (p != NULL) {
		printf("<-%d->", p->valor);
		p = p->proximo;
	}
	putchar('\n');
}

void remover_tudo(Lista* l) {
	while (l->cabeca != NULL) {
		Noh* p = l->cabeca;
		l->cabeca = p->proximo;
		free(p);
	}
	l->cauda = NULL;
}

void ordInsercao(Lista* l) {
	if (l->cabeca == NULL) {
		return;
	}
    Noh* desord = l->cabeca->proximo;
	while (desord != NULL) {
		int aux = desord->valor;
        Noh* orden = desord->anterior;
		while (orden != NULL && aux < orden->valor) {
			orden->proximo->valor = orden->valor;
			orden = orden->anterior;
		}
		if (orden == NULL) {
			l->cabeca->valor = aux;
		}
		else {
			orden->proximo->valor = aux;
		}
		desord = desord->proximo;
    }
}

int main(void) {
	int vetor[] = { 23, 12, 89, 44, 3, 18, 35, -1 };
	Lista l = { NULL, NULL };	// cabeca e cauda nulas

	int i = 0;
	while (vetor[i] > 0) {
		inserir(&l, vetor[i++]);
	}
	imprimir(&l);

	ordInsercao(&l);
	imprimir(&l);

	remover_tudo(&l);

	return 0;
}
	
