#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int* busca(int*, size_t, int);

int main(void) {
	srand((unsigned)time(NULL));

	size_t n;
	printf("Digite o tamanho do vetor: ");
	scanf("%zu", &n);

	int* vetor = malloc(sizeof(int) * n);

	printf("Conteudo do vetor aleatorio: ");
	int i;
	for (i = 0; i < n; ++i) {
		vetor[i] = rand() % 1000;
		printf("%d ", vetor[i]);
	}

	printf("\nDigite um valor a ser localizado no vetor: ");
	scanf("%d", &i);

	int* loc = busca(vetor, n, i);
	if (loc == NULL) {
		puts("O valor informado nao foi localizado!");
	}
	else {
		// Como 'loc' e 'vetor' sao ponteiros para int (int*), a subtracao entre eles
		// nos dah o numero de inteiros que existe como "distancia" entre eles, ou seja,
		// o indice de onde fica 'loc'
		printf("O valor foi localizado no indice %d.\n", loc-vetor);
	}

	free(vetor);

	return EXIT_SUCCESS;
}

/*
int* busca(int* vet, size_t tam, int val) {
	int i;
	for (i = 0; i < tam; ++i) {
		if (*(vet + i) == val) {
			return (vet + i);
		}
	}
	return NULL;
}
*/

int* busca(int* vet, size_t tam, int val) {
	if (tam == 0) {	// 1a. condicao terminal (em que nao se chama novamente a funcao)
		return NULL;	// nao ha mais o que comparar
	}
	if (*vet == val) {	// 2a. condicao terminal
		return vet;	// a solucao foi trivial, pode ser retornada
	}
	return busca(vet + 1, tam - 1, val); // retorna o resultado da chamada recursiva
}
