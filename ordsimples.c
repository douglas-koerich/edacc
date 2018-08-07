#include "registro.h"
#include "ordenacao.h"

// Contiguidade fisica: trocamos todos os campos entre os registros
void swap(Registro* x, Registro* y) {
	Registro aux = *x;
	*x = *y;
	*y = aux;
}

void bubble(Registro a[], size_t n) {
	int j;
	for (j=1; j<=n; ++j) {
		int i;
		for (i=0; i<n-1; ++i) {
			if (a[i].chave > a[i+1].chave) {
				swap(&a[i], &a[i+1]);
			}
		}
	}
}

void select_(Registro a[], size_t n) {
	int j;
	for (j=0; j<n; ++j) {
		int menor = j;	// armazena o indice do menor ateh agora
		int i;
		for (i=j+1; i<n; ++i) {
			if (a[i].chave < a[menor].chave) {
				menor = i;	// atualiza quem eh o menor da vez
			}
		}
		swap(&a[j], &a[menor]);
	}
}

void insert(Registro a[], size_t n) {
	int d;	// indice do primeiro elemento ainda nao ordenado
	for (d=1; d<n; ++d) {
		int o = d-1; // indice dos elementos que ja foram ordenados
		Registro backup = a[d];
		while (o >= 0 && a[o].chave > backup.chave) {
			a[o+1] = a[o];	// desloca o maior para a posicao da direita
			--o;
		}
		a[o+1] = backup;
	}
}
