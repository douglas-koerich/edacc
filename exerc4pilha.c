#include <stdio.h>
#include <ctype.h>
#include "TADs.h"

void remover(struct Pilha*, char);

int main() {
	struct Pilha* p = p_criar(10);

	char c;
	do {
		printf("Digite um caracter para empilhar: ");
		scanf(" %c", &c);
		if (isalpha(c)) {
			push(p, c);
		}
	}
	while (!p_overflow(p) && isalpha(c));

	puts("Pilha antes da remocao:");
	p_imprimir(p);

	printf("Digite um caracter para remover: ");
	scanf(" %c", &c);

	remover(p, c);

	puts("Pilha depois da remocao:");
	p_imprimir(p);

	p_destruir(p);
	return 0;
}

void remover(struct Pilha* p, char c) {
	struct Pilha* aux = p_criar(100);
	while (!p_underflow(p)) {
		char x = pop(p);
		if (x != c) {
			push(aux, x);
		}
	}
	while (!p_underflow(aux)) {
		push(p, pop(aux));
	}
	p_destruir(aux);
}
