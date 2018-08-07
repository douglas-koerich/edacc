#include <stdio.h>
#include "pilha.h"

size_t size(Pilha* p) {
	//return p->topo+1;	// versao xunxada e, salvo dito contrario, invalida
	size_t contador = 0;
	char temp;
	Pilha aux;

	inicia(&aux, 100);
	while (!underflow(p)) {
		pop(p, &temp);
		push(&aux, temp);
		++contador;
	}
	while (!underflow(&aux)) {
		pop(&aux, &temp);
		push(p, temp);
	}
	finaliza(&aux);

	return contador;
}

int main() {
	char teste[] = { 'a', 'b', 'c', '\0' };
	Pilha x;
	int i = 0, n;

	inicia(&x, sizeof(teste));	// inicializa a pilha

	while (teste[i] != '\0') {
		push(&x, teste[i++]);
	}
	printf("Minha pilha tem %u elementos.\n", size(&x));
	while (!underflow(&x)) {
		char temp;
		pop(&x, &temp);
		putchar(temp);
	}
	putchar('\n');

	finaliza(&x);	// apos o uso, libera a pilha na memoria
	return 0;
}
