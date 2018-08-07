#include <stdio.h>
#include "Pilha.h"

void convbin(char [], int);

int main() {
	char string[64];
	int num = 579;

	sprintf(string, "%d", num);	// em decimal
	printf("string: %s\n", string);

	/* Pe. Quevedo: "NON ECSISTE"
	sprintf(string, "%b", num);	// em binario
	*/
	convbin(string, num);
	printf("string: %s\n", string);

	sprintf(string, "%o", num);	// em octal
	printf("string: %s\n", string);

	sprintf(string, "%x", num);	// em hexadecimal
	printf("string: %s\n", string);

	return 0;
}

void convbin(char s[], int n) {
	struct Pilha* aux = criar(32);	// um int tem 32 bits
	while (n > 0) {
		char resto = (n % 2) + '0';	// conversao direta p/ ASCII
		push(aux, resto);
		n = n / 2;
	}
	int i = 0;
	while (!underflow(aux)) {
		char bit = pop(aux);	// '0' ou '1'
		s[i++] = bit;
	}
	s[i] = '\0'; // para marcar o fim da string
	destruir(aux);
}
