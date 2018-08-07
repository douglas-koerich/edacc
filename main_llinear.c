#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "llinear_estatica.h"

int main() {
	srand((unsigned)time(0));

	ListaEstatica l = iniciaLista(10);
	for (unsigned e = 100; e < 105; ++e) {
		TipoElemento elem = { e, rand() };
		inserir(&l, elem);
	}
	imprimir(&l);
	TipoElemento* elem;
	elem = busca(&l, 100);
	if (elem != NULL) {
		printf("O valor no elemento 100 eh %d.\n", elem->campo);
	}
	elem = busca(&l, 120);
	if (elem == NULL) {
		puts("O elemento 120 nao existe");
	}

	remover(&l, 100);
	imprimir(&l);
	elem = busca(&l, 100);
	if (elem != NULL) {
		printf("O valor no elemento 100 eh %d.\n", elem->campo);
	}
	else {
		puts("O elemento 100 nao existe");
	}

	finalizaLista(&l);

	return 0;
}
