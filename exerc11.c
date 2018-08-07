#include <stdio.h>
#include "fila.h"

#define MAX_FILA	15

void mescla(Fila* fa, Fila* fb, Fila* fc) {
	Fila aux_b, aux_c;
	int temp, tb = -1, tc = -1;

	inicia(&aux_b, tamanho(fb));
	inicia(&aux_c, tamanho(fc));

	size_t tam = tamanho(fb) + tamanho(fc);
	inicia(fa, tam);

	while (!underflow(fb) || !underflow(fc)) {
		if (underflow(fb)) {
			if (tc != -1) {
				enqueue(fa, tc);
			}
			while (!underflow(fc)) {
				dequeue(fc, &temp);
				enqueue(fa, temp);
				enqueue(&aux_c, temp);
			}
		}
		else if (underflow(fc)) {
			if (tb != -1) {
				enqueue(fa, tb);
			}
			while (!underflow(fb)) {
				dequeue(fb, &temp);
				enqueue(fa, temp);
				enqueue(&aux_b, temp);
			}
		}
		else {
			if (tb < 0) {
				dequeue(fb, &tb);
				enqueue(&aux_b, tb);
			}
			if (tc < 0) {
				dequeue(fc, &tc);
				enqueue(&aux_c, tc);
			}
			if (tb < tc) {
				enqueue(fa, tb);
				tb = -1;
			}
			else {
				enqueue(fa, tc);
				tc = -1;
			}
		}
	}
	while (!underflow(&aux_b)) {
		dequeue(&aux_b, &temp);
		enqueue(fb, temp);
	}
	while (!underflow(&aux_c)) {
		dequeue(&aux_c, &temp);
		enqueue(fc, temp);
	}
	finaliza(&aux_c);
	finaliza(&aux_b);
}

int main() {
	int v1[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, -1 },
		v2[] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, -1 };
	int i;

	Fila f1, f2, f3;

	inicia(&f1, MAX_FILA);
	inicia(&f2, MAX_FILA);

	for (i=0; v1[i] >= 0; ++i)
		enqueue(&f1, v1[i]);
	for (i=0; v2[i] >= 0; ++i)
		enqueue(&f2, v2[i]);

	printf("Fila 1: ");
	imprime(&f1);
	printf("Fila 2: ");
	imprime(&f2);

	mescla(&f3, &f1, &f2);
	printf("Fila 3: ");
	imprime(&f3);
	printf("Fila 1: ");
	imprime(&f1);
	printf("Fila 2: ");
	imprime(&f2);

	finaliza(&f1);
	finaliza(&f2);
	finaliza(&f3);

	return 0;
}

