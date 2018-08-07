#include <math.h>
#include "algbusca.h"

int buscaSequencial(int vetor[], int n, int chaveBusca) {
	int indice;
	for (indice=0; indice<n; ++indice) {
		if (vetor[indice] == chaveBusca) {
			return indice;
		}
	}
	return -1;
}

int buscaBinaria(int vetor[], int esq, int dir, int chaveBusca) {
	if (dir < esq) {
		return -1;
	}
	int meio = (esq+dir)/2;
	if (vetor[meio] == chaveBusca) {
		return meio;
	}
	if (vetor[meio] < chaveBusca) {
		return buscaBinaria(vetor, meio+1, dir, chaveBusca);
	}
	else {
		return buscaBinaria(vetor, esq, meio-1, chaveBusca);
	}
}

int buscaInterpolacao(int vetor[], int esq, int dir, int chaveBusca) {
	if (dir < esq) {
		return -1;
	}
	double proporcao, distancia_esq, distancia_total;
	if (esq == dir) {
		proporcao = 0.0;
	}
	else {
		double distancia_esq = (double)(chaveBusca - vetor[esq]),
			   distancia_total = (double)(vetor[dir] - vetor[esq]);
		proporcao = fabs(distancia_esq/distancia_total) * (dir-esq);
	}
	int indice = proporcao + esq;
	
	if (vetor[indice] == chaveBusca) {
		return indice;
	}
	if (vetor[indice] < chaveBusca) {
		return buscaInterpolacao(vetor, indice+1, dir, chaveBusca);
	}
	else {
		return buscaInterpolacao(vetor, esq, indice-1, chaveBusca);
	}
}

