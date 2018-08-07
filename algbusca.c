#include <string.h>
#include <math.h>
#include "algbusca.h"

int buscaSequencial(Registro_Exemplo vetor[], int n, char chaveBusca) {
	int indice;
	for (indice=0; indice<n; ++indice) {
		if (vetor[indice].chave == chaveBusca) {
			return indice;
		}
	}
	return -1;
}

int buscaSentinela(Registro_Exemplo vetor[], int N, int* n, Registro_Exemplo* novo) {
	int indice = 0;
	if (*n >= N) {
		return -1;
	}
	memcpy(vetor+*n, novo, sizeof(Registro_Exemplo));
	while (vetor[indice].chave != novo->chave) {
		++indice;
	}
	if (indice == *n) {
		++(*n);
	}
	return indice;
}

int buscaBinaria(Registro_Exemplo vetor[], int esq, int dir, char chaveBusca) {
	int meio = (esq+dir)/2;
	if (dir < esq) {
		return -1;
	}
	if (vetor[meio].chave == chaveBusca) {
		return meio;
	}
	if (vetor[meio].chave < chaveBusca) {
		return buscaBinaria(vetor, meio+1, dir, chaveBusca);
	}
	else {
		return buscaBinaria(vetor, esq, meio-1, chaveBusca);
	}
}

int buscaInterpolacao(Registro_Exemplo vetor[], int esq, int dir, char chaveBusca) {
	int indice;
	double proporcao, distancia_esq, distancia_total;
	if (dir < esq) {
		return -1;
	}
	if (esq == dir) {
		proporcao = 0.0;
	}
	else {
		double distancia_esq = (double)(chaveBusca - vetor[esq].chave),
			   distancia_total = (double)(vetor[dir].chave - vetor[esq].chave);
		proporcao = fabs(distancia_esq/distancia_total) * (dir-esq);
	}
	indice = proporcao + esq;
	
	if (vetor[indice].chave == chaveBusca) {
		return indice;
	}
	if (vetor[indice].chave < chaveBusca) {
		return buscaInterpolacao(vetor, indice+1, dir, chaveBusca);
	}
	else {
		return buscaInterpolacao(vetor, esq, indice-1, chaveBusca);
	}
}

