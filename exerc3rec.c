#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int maximo(int[*], int);
int recursiva(int[*], int, int);

int main(void) {
	srand((unsigned) time(0));
	
	printf("Digite o numero de elementos do vetor: ");
	
	int n;
	scanf("%d", &n);
	
	int vetor[n];
	printf("Vetor: ");
	for (int i=0; i<n; ++i) {
		vetor[i] = rand() % 100000L;
		printf("%d ", vetor[i]);
	}

	int max = maximo(vetor, n);
	printf("\nO maior valor do vetor eh: %d.\n", max);

	return 0;
}

int maximo(int vetor[], int n) {
	return recursiva(vetor, 0, n-1);
}

int recursiva(int vetor[], int inf, int sup) {
	if (inf == sup) {
		return vetor[inf];	// ou vetor[sup], tanto faz...
	}
	int meio = (inf+sup)/2;
	int maxinf = recursiva(vetor, inf, meio);
	int maxsup = recursiva(vetor, meio+1, sup);
	return maxinf > maxsup? maxinf: maxsup;
}

