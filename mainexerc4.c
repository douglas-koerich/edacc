#include <stdio.h>
#include "exerc4pilha.h"

bool tira(struct Pilha*, int);

int main() {
	struct Pilha* pilha = cria(50);

	// Preenche a pilha
	int num;
	do {
		printf("Digite um valor (-1 para terminar): ");
		scanf("%d", &num);
		if (num != -1) {
			if (!push(pilha, num)) {
				puts("Pilha cheia!");
				break;
			}
		}
	} while (num != -1);

	// Imprime a pilha
	print(pilha);

	printf("Digite o valor a tirar: ");
	scanf("%d", &num);

	if (!tira(pilha, num)) {
		puts("Valor nao encontrado!");
	}
	print(pilha);

	destroi(pilha);
	return 0;
}

bool tira(struct Pilha* pilha, int num) {
	struct Pilha* aux = cria(100);
	bool achei = false;
	while (!underflow(pilha)) {
		int x;
		pop(pilha, &x);
		if (x != num) {
			push(aux, x);
		}
		else {
			achei = true;
		}
	}
	while (!underflow(aux)) {
		int x;
		pop(aux, &x);
		push(pilha, x);
	}
	destroi(aux);
	return true;
}

