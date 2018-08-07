#include <stdio.h>
#include <math.h>

int hashing(int);
int novo(int);

int main(void) {
	int vetor[] = { 224562, 137456, 214562, 140415, 214576, 162145, 144467, 199645, 234534, -1 };
	int i = 0;

	while (vetor[i] > 0) {
		printf("chave = %d, hashing = %d, novo = %d\n", vetor[i], hashing(vetor[i]), novo(vetor[i]));
		++i;
	}
	return 0;
}

int hashing(int chave) {
	int prefixo = chave / 1000;
	int quadrado = pow(prefixo, 2);
	int dig2, dig3, dig4;
	if (quadrado >= 100000) {
		dig2 = quadrado/10000 % 10;
		dig3 = quadrado/1000 % 10;
		dig4 = quadrado/100 % 10;
	}
	else {
		dig2 = quadrado/1000 % 10;
		dig3 = quadrado/100 % 10;
		dig4 = quadrado/10 % 10;
	}
	int extrato = dig2*100 + dig3*10 + dig4;
	return extrato % 19;
}

int novo(int chave) {
	return (3*hashing(chave) - 1) % 19 + 1;
}

