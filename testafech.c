#include <stdio.h>
#include <stdbool.h>
#include "Pilha.h"

bool teste(char*);

int main() {
	char expressao[128];

	puts("Digite uma expressao com parenteses para validacao: ");
	gets(expressao);

	bool ok = teste(expressao);

	if (ok == true) {
		puts("A expressao esta correta.");
	}
	else {
		puts("A expressao contem um erro.");
	}
	return 0;
}

bool teste(char* expr) {
	struct Pilha* aux = criar(128);
	int i = 0;
	while (expr[i] != '\0') {
		switch (expr[i]) {
			case '(':
				push(aux, expr[i]);
				break;

			case ')':
				if (underflow(aux)) {
					destruir(aux);	// libera memoria da pilha
					return false;
				}
				pop(aux);	// simplesmente descarta o '('
				break;

			default:
				// qualquer outro caracter eh ignorado
				;
		}
		++i;
	}
	bool vazia_ok = underflow(aux);
	destruir(aux);
	return vazia_ok;
}

