#include <stdio.h>
#include <ctype.h>
#include "TADs.h"

void inverter(struct Fila*);

int main() {
	struct Fila* f = f_criar(20);

	char c;
	do {
		printf("Digite um caracter para por na fila: ");
		scanf(" %c", &c);
		if (isalpha(c)) {
			enqueue(f, c);
		}
	}
	while (!f_overflow(f) && isalpha(c));

	puts("Fila antes da inversao:");
	f_imprimir(f);

	inverter(f);

	puts("Fila depois da inversao:");
	f_imprimir(f);

	f_destruir(f);
	return 0;
}

void inverter(struct Fila* f) {
	struct Pilha* aux = p_criar(100);
	while (!f_underflow(f)) {
		push(aux, dequeue(f));
	}
	while (!p_underflow(aux)) {
		enqueue(f, pop(aux));
	}
	p_destruir(aux);
}

