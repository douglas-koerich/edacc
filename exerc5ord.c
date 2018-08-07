#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void ordCoquetel(int[*], int);

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

	ordCoquetel(vetor, n);

	printf("\nVetor ordenado: ");
	for (int i=0; i<n; ++i) {
		printf("%d ", vetor[i]);
	}
	putchar('\n');

	return 0;
}

void troca(int* px, int* py) {
	int aux = *px;
	*px = *py;
	*py = aux;
}

void ordCoquetel(int vetor[], int n) {
	bool sobe = true;
	for (int v=1; v<=n; ++v,			// tantas varreduras quanto o num. de elementos
						sobe = !sobe) {	// a cada nova iteracao, inverte o valor de 'sobe'
		if (sobe) {	// 'bolha' (menor) deve subir (algoritmo original)
			for (int i=n-1; i>0; --i) {
				if (vetor[i] < vetor[i-1]) {
					troca(&vetor[i], &vetor[i-1]);
				}
			}
		}
		else {		// 'pedra' (maior) deve descer
			for (int i=0; i<n-1; ++i) {
				if (vetor[i] > vetor[i+1]) {
					troca(&vetor[i], &vetor[i+1]);
				}
			}
		}
	}
}

