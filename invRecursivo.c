#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void inverte(int*, unsigned, unsigned);

int main() {
	size_t tam;
	printf("Qual o tamanho do vetor a preencher? ");
	scanf("%u", &tam);

	int i, vetor[tam];
	srand((unsigned) time(0));
	printf("Vetor na ordem original: ");
	for (i=0; i<tam; ++i) {
		vetor[i] = rand() % 1000 + 1;
		printf("%d ", vetor[i]);
	}
	putchar('\n');

	inverte(vetor, 0, tam-1);

	printf("Vetor apos inversao: ");
	for (i=0; i<tam; ++i) {
		printf("%d ", vetor[i]);
	}
	putchar('\n');

	return 0;
}

void inverte(int* vet, unsigned esq, unsigned dir) {
	if (esq < dir) {
		int aux = vet[esq];
		vet[esq] = vet[dir];
		vet[dir] = aux;

		inverte(vet, esq+1, dir-1);
	}
}

