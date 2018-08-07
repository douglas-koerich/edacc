#include <stdio.h>
#include <string.h>
#include "pilha.h"

bool valida(const char* expr) {
	Pilha aux;
	bool ok = true;

	inicia(&aux, strlen(expr));

	while (*expr != '\0') {
		switch (*expr) {
			case '(':
				push(&aux, '(');
				break;
			case ')':
				if (underflow(&aux)) {
					ok = false;	// um ) sem o ( anterior
				}
				else {
					char dummy;
					pop(&aux, &dummy);
				}
				break;
			default:
				// faz nada, vai para o proximo
				;
		}
		++expr;
	}
	if (!underflow(&aux)) {
		ok = false;	// um ou mais ( sobrou sem o ) que o eliminasse
	}
	finaliza(&aux);

	return ok;
}

int main() {
	const char* expressao = "x = (a+b)*5 - c*)(d-e)/f)";
	printf("A expressao %seh valida!\n", valida(expressao)? "": "NAO ");
	return 0;
}
