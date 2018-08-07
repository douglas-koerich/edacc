#include <stdio.h>

float media_r(int*, int);

int main() {
	int n;

	printf("Digite o numero de elementos do vetor: ");
	scanf("%d", &n);

	int vetor[n];
	int i;
	for (i=0; i<n; ++i) {
		vetor[i] = i+1;
	}

	printf("Vetor gerado: ");
	for (i=0; i<n; ++i) {
		printf("%d ", vetor[i]);
	}
	putchar('\n');

	float media = media_r(vetor, n);

	printf("A media dos valores armazenados no vetor eh %f\n", media);
	return 0;
}

float media_r(int* vetor, int n) {
	if (n == 0) {
		return 0.0;
	}
	if (n == 1) {
		return *vetor;
	}
	float m = (*vetor + (n-1)*media_r(vetor+1, n-1))/n;
	return m;
}

