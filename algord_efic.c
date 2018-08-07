#include <stdlib.h>
#include <string.h>
#include "algord.h"

void ordShell(Registro_Exemplo vetor[], int n) {
	int incrementos[20], k, j;
	for (k=1, j=0; k<n; ++j) {
		incrementos[j] = k;
		k = 3*k + 1;
	}
	for (--j; j>=0; --j) {
		int s;
		k = incrementos[j];
		for (s=0; s<k; ++s) {
			int desord;
			for (desord=k; desord<n; desord+=k) {
				int orden;
				Registro_Exemplo aux = vetor[desord];
				for (orden=desord-k; orden>=0 && aux.chave_ordenacao<vetor[orden].chave_ordenacao; orden-=k) {
					vetor[orden+k] = vetor[orden];
				}
				vetor[orden+k] = aux;
			}
		}
	}
}

void ordShell_s(Registro_Exemplo vetor[], int n) {
	int incrementos[20], k, j;
	for (k=1, j=0; k<n; ++j) {
		incrementos[j] = k;
		k = 3*k + 1;
	}
	for (--j; j>=0; --j) {
		int s;
		k = incrementos[j];
		for (s=0; s<k; ++s) {
			int p;
			for (p=s; p<n-1; p+=k) {
				Registro_Exemplo aux;
				int i, menor = p;
				for (i=p+k; i<n; i+=k) {
					if (vetor[i].chave_ordenacao < vetor[menor].chave_ordenacao) {
						menor = i;
					}
				}
				aux = vetor[p];
				vetor[p] = vetor[menor];
				vetor[menor] = aux;
			}
		}
	}
}

typedef struct no_fila {
	Registro_Exemplo reg;
	struct no_fila* prox;
} NoFila;
typedef NoFila* FilaL;
static int underflow(const FilaL f) { return f == NULL; }
static void enqueue(FilaL* f, const Registro_Exemplo* r) {
	NoFila* n = (NoFila*) malloc(sizeof(NoFila));
	memcpy(&n->reg, r, sizeof(Registro_Exemplo));
	n->prox = NULL;
	if (*f == NULL) *f = n;
	else {
		NoFila* p = *f;
		while (p->prox != NULL) p = p->prox;
		p->prox = n;
	}
}
static void dequeue(FilaL* f, Registro_Exemplo* r) {
	NoFila* p = *f;
	if (p == NULL) return;
	memcpy(r, &p->reg, sizeof(Registro_Exemplo));
	*f = p->prox;
	free(p);
}

void ordRadix(Registro_Exemplo vetor[], int n) {
	const int max_digitos = 9;
	int d, fator;
	for (d = fator = 1; d <= max_digitos; ++d, fator *= 10) {
		FilaL digito[10] = { NULL };
		int i, dig;
		for (i = 0; i < n; ++i) {
			dig = vetor[i].chave_ordenacao / fator % 10;
			enqueue(&digito[dig], &vetor[i]);
		}
		for (i = dig = 0; dig < 10; ++dig) {
			while (!underflow(&digito[dig]) {
				dequeue(&digito[dig], &vetor[i++]);
			}
		}
	}
}

static void intercala(Registro_Exemplo vetor[], int esq, int meio, int dir) {
	int e = esq, d = meio+1, m = 0, n = dir-esq+1;
	Registro_Exemplo* aux = (Registro_Exemplo*) malloc(sizeof(Registro_Exemplo) * n);
	while (e <= meio || d <= dir) {
		if (e > meio) {
			while (d <= dir) {
				aux[m++] = vetor[d++];
			}
			continue;
		}
		else if (d > dir) {
			while (e <= meio) {
				aux[m++] = vetor[e++];
			}
			continue;
		}
		if (vetor[e].chave_ordenacao < vetor[d].chave_ordenacao) {
			aux[m++] = vetor[e++];
		}
		else {
			aux[m++] = vetor[d++];
		}
	}
	memcpy(vetor+esq, aux, sizeof(Registro_Exemplo) * n);
	free(aux);
}

void ordMerge(Registro_Exemplo vetor[], int esq, int dir) {
	if (esq < dir) {
		int meio = (esq+dir)/2;
		ordMerge(vetor, esq, meio);
		ordMerge(vetor, meio+1, dir);
		intercala(vetor, esq, meio, dir);
	}
}	

void ordQuick(Registro_Exemplo vetor[], int esq, int dir) {
    int e = esq, d = dir, chave_pivo = vetor[(esq+dir)/2].chave_ordenacao;
	do {
		while (vetor[e].chave_ordenacao < chave_pivo)	++e;
		while (vetor[d].chave_ordenacao > chave_pivo)	--d;
		if (e <= d) {
			Registro_Exemplo aux = vetor[e];
			vetor[e] = vetor[d];
			vetor[d] = aux;
			++e; --d;
		}
	}
	while (e <= d);
	if ((d-esq) > 0)
		ordQuick(vetor, esq, d);
	if ((dir-e) > 0)
		ordQuick(vetor, e, dir);
}
