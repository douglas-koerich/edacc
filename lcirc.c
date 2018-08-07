#include <stdlib.h>
#include <stdio.h>
#include "lcirc.h"

void inicia(Lista* l) {
	*l = NULL;
}

void finaliza(Lista* l) {
	if (underflow(l)) {
		return;
	}
	// Enquanto estiver apontando pra algum noh diferente
	// de mim mesmo (ou seja, enquanto eu nao for o unico)...
	while (*l != (*l)->proximo) {
		// Vou apagar esse noh diferente de mim...
		No* q = (*l)->proximo;

		// ... mas antes tenho que salvar o proximo dele!
		(*l)->proximo = q->proximo;
		free(q);
	}
	// Finalmente, apago o unico noh que restou
	free(*l);
	*l = NULL;
}

bool underflow(const Lista* l) {
	return *l == NULL;
}

void insInicio(Lista* l, int novo) {
	// Cria e preenche com valor um novo noh em memoria
	No* p = (No*) malloc(sizeof(No));
	p->valor = novo;

	if (underflow(l)) {
		// Se a lista estah vazia, o novo noh aponta pra si
		// mesmo
		p->proximo = p;

		// Nesse caso, o fim da lista indicado em *l eh
		// o proprio noh de inicio
		*l = p;
	}
	else {
		// O novo inicio deve apontar para o antigo inicio
		p->proximo = (*l)->proximo;

		// O fim deve apontar para o novo inicio
		(*l)->proximo = p;
	}
}

bool remInicio(Lista* l, int* valor) {
	if (underflow(l)) {
		return false;
	}
	else {
		// Aponta para o noh que vai ser apagado, que eh
		// o proximo do noh no fim da lista
		No* q = (*l)->proximo;
		*valor = q->valor;
		if (q == *l) {
			// Se esse noh do inicio eh tambem o noh do fim,
			// a lista voltarah a ficar vazia
			*l = NULL;
		}
		else {
			// Deve apontar com o noh de fim pra aquele que
			// serah o novo noh de inicio
			(*l)->proximo = q->proximo;
		}
		free(q);
		return true;
	}
}

void insFim(Lista* l, int novo) {
	// Cria e preenche com valor um novo noh em memoria
	No* p = (No*) malloc(sizeof(No));
	p->valor = novo;

	if (underflow(l)) {
		// Se a lista estah vazia, o novo noh aponta pra si
		// mesmo
		p->proximo = p;
	}
	else {
		// O novo fim deve apontar para o inicio que estah
		// indicado no antigo fim
		p->proximo = (*l)->proximo;

		// O antigo fim deve apontar para o novo fim
		(*l)->proximo = p;
	}
	*l = p;
}

bool remFim(Lista* l, int* valor) {
	if (underflow(l)) {
		return false;
	}
	else {
		// Aponta para o noh que vai ser apagado, que eh
		// o fim da lista
		No* q = *l;
		*valor = q->valor;
		if (q == q->proximo) {
			// Se esse noh aponta pra si mesmo, ele eh o
			// unico da lista, que voltarah a ficar vazia
			*l = NULL;
		}
		else {
			// Eh necessario "dar a volta" pela lista pra
			// encontrar o no *anterior* ao noh de fim
			No* r = q;
			while (r->proximo != q) {
				r = r->proximo;
			}
			// Estando no noh anterior ao fim, que serah o
			// novo fim, deve faze-lo apontar para o inicio
			r->proximo = q->proximo;
			*l = r;
		}
		free(q);
		return true;
	}
}

bool remValor(Lista* l, int valor) {
	if (underflow(l)) {
		return false;
	}
	else {
		No* r = *l, *q = r->proximo;

		// Iniciando pelo comeco da lista, vamos fazer a busca
		// pelo noh com o valor; note que, se nao encontrarmos
		// o valor, temos que parar se dermos a volta completa
		while (q->valor != valor && q != *l) {
			r = q;	// salva o noh anterior da vez...
			q = q->proximo;
		}

		// Parou porque encontrou o valor?
		if (q->valor == valor) {
			if (q == q->proximo) {
				// Se esse noh aponta pra si mesmo, ele eh o
				// unico da lista, que voltarah a ficar vazia
				*l = NULL;
			}
			else {
				// Faz o noh anterior apontar para o noh
				// seguinte ao noh que sera apagado
				r->proximo = q->proximo;
				if (q == *l) {
					// Se o noh que vai ser apagado eh o fim,
					// o ponteiro externo tem que ser
					// atualizado
					*l = r;
				}
			}
			free(q);
			return true;
		}
		else {
			return false;
		}
	}
}

void imprime(const Lista* l) {
	No* q;
	if (underflow(l)) {
		puts("Lista vazia!");
		return;
	}
	// Comeca a impressao do inicio da lista...
	q = (*l)->proximo;
	do {
		printf("%d ", q->valor);
		q = q->proximo;
	} while (q != (*l)->proximo);
	// ... e para quando chega no mesmo ponto ("deu a volta")
	putchar('\n');
}

void insValor(Lista* l, int novo) {
	// Cria e preenche com valor um novo noh em memoria
	No* p = (No*) malloc(sizeof(No));
	p->valor = novo;

	if (underflow(l)) {
		// Se a lista estah vazia, o novo noh aponta pra si
		// mesmo
		p->proximo = p;
		*l = p;
	}
	else {
		No* r = *l, *q = r->proximo;

		// Iniciando pelo comeco da lista, vamos fazer a busca
		// pelo noh com o valor; note que, se nao encontrarmos
		// o valor, temos que parar se dermos a volta completa
		while (q->valor < novo && q != *l) {
			r = q;
			q = q->proximo;
		}
		// Encontrou o ponto de insercao?
		if (q->valor >= novo) {
			p->proximo = q;
			r->proximo = p;
		}
		else {
			// Atingiu o fim mas todos os valores eram menores
			p->proximo = q->proximo;
			q->proximo = p;
			*l = p;
		}
	}
}
