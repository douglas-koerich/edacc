#include <stdlib.h>		// exit()
#include <stdio.h>
#include "pilhabits.h"

void dec2bin(unsigned short origem_dec, char* destino_bin);

int main() {
	unsigned short int num;

	printf("Digite um numero positivo entre 0 e 65535: ");
	scanf("%hu", &num);

	printf("DEC = %hu\n", num);
	printf("OCT = %o\n", num);
	printf("HEX = %x\n", num);

	char binario[17]; // 16 "bits" ('0'/'1') + terminador nulo
	dec2bin(num, binario);

	printf("BIN = %s\n", binario);

	return 0;
}

void dec2bin(unsigned short origem_dec, char* destino_bin) {
	struct Pilha* aux = cria(16);

	unsigned short quociente = origem_dec;
	do {
		unsigned short resto = quociente % 2;
		quociente = quociente / 2;
		bit digito = resto + '0'; // transforma 0/1 em '0'/'1'
		if (push(aux, digito) == false) {
			puts("Erro, abortando programa...");
			exit(-1);
		}
	} while (quociente != 0);

	int indice = 0;
	while (!underflow(aux)) {
		bit digito;
		pop(aux, &digito);
		destino_bin[indice++] = digito;
	}
	destino_bin[indice] = '\0';

	destroi(aux);
}
