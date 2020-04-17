#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool busca(unsigned*, size_t, unsigned);

int main(void) {
	size_t tamanho;
	printf("Digite o tamanho do vetor a ser gerado: ");
	scanf("%zu", &tamanho);

	unsigned* vetor = malloc(tamanho * sizeof(unsigned));
	int i;
	for (i = 0; i < tamanho; ++i) {
		vetor[i] = rand() % 100 + 1; // de 1 a 100
		printf("%u ", vetor[i]);
	}
	putchar('\n');

	printf("Digite um valor a buscar no vetor: ");
	unsigned valor;
	scanf("%u", &valor);

	if (busca(vetor, tamanho, valor) == true) {
		puts("Valor encontrado!");
	}
	else {
		puts("Valor nao encontrado!");
	}
	free(vetor);
	return EXIT_SUCCESS;
}

/*
bool busca(unsigned* vetor, size_t tamanho, unsigned valor) {
	int i;
	for (i = 0; i < tamanho; ++i) {
		if (vetor[i] == valor) {
			return true;
		}
	}
	return false;
}
*/

bool busca(unsigned* vetor, size_t tamanho, unsigned valor) {
	if (tamanho == 0) { // 1a. condicao terminal: "vetor" de tamanho nulo
		return false;
	}
	if (*vetor == valor) { // 2a. condicao terminal: valor estah no inicio
		return true;	   // do "vetor (restante?)"
	}
	// Chama a funcao recursiva passando a proxima posicao do vetor a
	// ser considerada como o inicio do "vetor restante" para ela, e com
	// o tamanho desse "restante"
	return busca(vetor + 1, tamanho - 1, valor);
}