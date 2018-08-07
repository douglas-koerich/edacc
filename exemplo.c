#include <stdio.h>
#include "deque.h"

int main() {
	int lista[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, -1 },
	   *pi = lista;
	bool naCabeca = false;
	int temp;
	Deque teste;

	inicia(&teste, 15);

	while (*pi != -1) {
		printf("Inserindo %d na %s:\n", *pi, naCabeca? "cabeca": "cauda");
		enqueue(&teste, naCabeca? CABECA: CAUDA, *pi++);
		imprime(&teste);
		naCabeca = !naCabeca;
	}
	printf("Removendo da cabeca:\n");
	dequeue(&teste, CABECA, &temp);
	imprime(&teste);

	printf("De novo:\n");
	dequeue(&teste, CABECA, &temp);
	imprime(&teste);

	printf("Removendo da cauda:\n");
	dequeue(&teste, CAUDA, &temp);
	imprime(&teste);

	printf("De novo:\n");
	dequeue(&teste, CAUDA, &temp);
	imprime(&teste);

	printf("Inserindo na cauda:\n");
	enqueue(&teste, CAUDA, 10);
	imprime(&teste);

	printf("Inserindo na cabeca:\n");
	enqueue(&teste, CABECA, 11);
	imprime(&teste);

	finaliza(&teste);

	return 0;
}

