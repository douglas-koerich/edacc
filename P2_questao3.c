#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING	4	// 12 bits equivalem a 4 digitos octais (3 bits)

typedef struct no_fila {
	char string[MAX_STRING+1];
	struct no_fila* prox;
} NoFila;
typedef NoFila* FilaL;
static int underflow(const FilaL f) { return f == NULL; }
static void enqueue(FilaL* f, const char* s) {
	NoFila* n = (NoFila*) malloc(sizeof(NoFila));
	strcpy(n->string, s);
	n->prox = NULL;
	if (*f == NULL) *f = n;
	else {
		NoFila* p = *f;
		while (p->prox != NULL) p = p->prox;
		p->prox = n;
	}
}
static void dequeue(FilaL* f, char* s) {
	NoFila* p = *f;
	if (p == NULL) return;
	strcpy(s, p->string);
	*f = p->prox;
	free(p);
}

void ordRadix(char* conjunto[], int num) {
	const int max_digitos = 4;
	int d;
	for (d = 1; d <= max_digitos; ++d) {
		FilaL digito[8] = { NULL };
		int i;
		char dig;
		for (i = 0; i < num; ++i) {
			int posicao = strlen(conjunto[i]) - d;
			dig = posicao < 0? 0: conjunto[i][posicao] - '0';
			enqueue(&digito[dig], conjunto[i]);
		}
		for (i = dig = 0; dig < 8; ++dig) {
			while (!underflow(digito[dig])) {
				dequeue(&digito[dig], conjunto[i++]);
			}
		}
	}
}

#define NUM	7

int main(void) {
	char lista[NUM][MAX_STRING+1] = {
		"670", "113", "241", "555", "47", "7", "336"
	};
	char* conjunto[NUM];
	int i;
	for (i=0; i<NUM; ++i) {
		conjunto[i] = lista[i];
		printf("%s ", conjunto[i]);
	}
	putchar('\n');
	ordRadix(conjunto, NUM);
	for (i=0; i<NUM; ++i) {
	   printf("%s ", lista[i]);
	}	   
	putchar('\n');
	return 0;
}

