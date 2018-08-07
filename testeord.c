#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubblesort(int*, int);
void selectsort(int*, int);
void insertsort(int*, int);
void shellsort(int*, int);
void mergesort(int*, int, int);
void quicksort(int*, int, int);
void troca(int*, int*);

int main(int argc, char* argv[]) {
	if (argc < 3) {
		puts("Numero invalido de parametros!");
		printf("Use: %s <tamanho> <algoritmo>\n", argv[0]);
		puts("     onde 'algoritmo':");
		puts("     1. Bolha (bubblesort)");
		puts("     2. Selecao (selectsort)");
		puts("     3. Insercao (insertsort)");
		puts("     4. Shell (shellsort)");
		puts("     5. Intercalacao (mergesort)");
		puts("     6. Rapido (quicksort)");
		return EXIT_FAILURE;
	}
	int tamanho = atoi(argv[1]),
		algoritmo = atoi(argv[2]);

	int* vetor = (int*) malloc(sizeof(int) * tamanho);

	// Vamos testar os algoritmos no seu pior caso, ou seja, quando o vetor
	// esta na ordem inversa da pretendida
	int i, j;
	for (i=0, j=tamanho; i<tamanho; ++i,--j) {
		vetor[i] = j;
	}

	// Chama o algoritmo desejado
	switch (algoritmo) {
		case 1: // bolha
			bubblesort(vetor, tamanho);
			break;

		case 2: // selecao
			selectsort(vetor, tamanho);
			break;

		case 3: // insercao
			insertsort(vetor, tamanho);
			break;

		case 4: // Shell
			shellsort(vetor, tamanho);
			break;

		case 5: // intercalacao 
			mergesort(vetor, 0, tamanho-1);	// passa os limites do vetor
			break;

		case 6: // rapido
			quicksort(vetor, 0, tamanho-1);
			break;

		default:
			puts("Algoritmo invalido!");
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void troca(int* x, int* y) {
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}

void bubblesort(int* v, int t) {
	// Laco externo: varre o vetor pelo numero de vezes do seu tamanho
	int i;
	for (i=1; i<=t; ++i) {
		// Laco interno: a bolha mais leve sobe
		int j;
		for (j=t-1; j>0; --j) {	// j nao chega a 0 pq sempre compara com ant
			if (v[j] < v[j-1]) {	// o sinal depende da orden ser cresc/decr
				troca(v+j, v+j-1);
			}
		}
	}
}

void selectsort(int* v, int t) {
	int inicio;
	for (inicio=0; inicio<t; ++inicio) {
		int i, pos_menor=inicio;
		for (i=inicio+1; i<t; ++i) {
			if (v[i] < v[pos_menor]) {
				pos_menor = i;
			}
		}
		troca(v+inicio, v+pos_menor);
	}
}

void insertsort(int* v, int t) {
	int fim_ordenados;
	for (fim_ordenados=0; fim_ordenados<t-1; ++fim_ordenados) {
		int nao_ordenado = fim_ordenados + 1,
			backup = v[nao_ordenado], i;
		for (i=fim_ordenados; i>=0 && v[i]>backup; --i) {
			v[i+1] = v[i];	// empurra o valor maior para posicao seguinte
		}
		v[i+1] = backup;
	}
}

#define INCR	50
void shellsort(int* v, int t) {
	// Constroi a sequencia de incrementos que depois vai ser percorrida
	// do maior para o menor
	int incrementos[INCR], i, k=1;
	for (i=0; i<INCR && k<t; ++i) {	// para de calcular se k>=t
		incrementos[i] = k;
		k = 3*k + 1;
	}
	// Como parou ao chegar ao fim do vetor (i==INCR) ou porque k>=t, entao
	// temos que iniciar pelo incremento da posicao anterior (INCR-1 ou
	// aquele *anterior* ao ultimo i - quando ainda era k<t)
	--i;
	while (i>0) {	// Ate chegar ao k = 1
		k = incrementos[--i];	// ja decrementa o i para o proximo laco

		// Pulando de k em k no vetor, tenho que fazer isso com k segmentos,
		// o primeiro comecando com 0/k/2k/..., o segundo com 1/1+k/1+2k/...,
		// e assim por diante ate o ultimo comecando com k-1/2k-1/...
		int segmento;
		for (segmento=0; segmento<k; ++segmento) {
			int inicio_segmento;
			// Todos os deslocamentos dentro do segmento devem ser feitos
			// de k em k (por isso o inicio+k, o i+=k, e assim por diante)
			for (inicio_segmento=segmento; inicio_segmento<t; inicio_segmento+=k) {
				int i, pos_menor=inicio_segmento;
				for (i=inicio_segmento+k; i<t; i+=k) {
					if (v[i] < v[pos_menor]) {
						pos_menor = i;
					}
				}
				troca(v+inicio_segmento, v+pos_menor);
			}
		}
	}
}

void intercala(int* v, int e, int m, int d) {
	// Preciso de um vetor auxiliar que vai receber os valores que estao
	// fora de ordem em v e que soh podem ser colocados em ordem numa outra
	// area de memoria (senao sobre-escreveria)
	int tamanho = d-e+1;
	int* vetor_auxiliar = (int*) malloc(tamanho * sizeof(int));
	int aux = 0;

	// Tenho duas metades para percorrer: a primeira vai de e ate m, e a
	// outra vai de m+1 ate d
	int esq = e, dir = m+1;
	while (esq<=m && dir<=d) {	// nao terminei nenhuma das metades ainda
		if (v[esq] < v[dir]) {
			vetor_auxiliar[aux++] = v[esq++];
		}
		else {
			vetor_auxiliar[aux++] = v[dir++];
		}
	}
	// Provavelmente uma das metades vai acabar antes:
	// a esquerda ficou pendente?
	while (esq<=m) {
		vetor_auxiliar[aux++] = v[esq++];
	}
	// ou nao, foi a direita que ficou pendente?
	while (dir<=d) {
		vetor_auxiliar[aux++] = v[dir++];
	}
	// O vetor auxiliar tem as duas metades juntas e agora ordenadas
	memcpy(v+e, vetor_auxiliar, tamanho*sizeof(int));
	free(vetor_auxiliar);
}

void mergesort(int* v, int e, int d) {
	if (e<d) {	// Deve existir este teste para parar a recursividade!
		int m = (e+d)/2;
		mergesort(v, e, m);
		mergesort(v, m+1, d);
		intercala(v, e, m, d);
	}
}

void quicksort(int* v, int e, int d) {
	int pivo = v[(e+d)/2];
	int esq = e, dir = d;
	do {
		while (v[esq] <= pivo) ++esq;	// para quando encontrar maior
		while (v[dir] >= pivo) --dir;	// para quando encontrar menor
		if (esq<dir) {
			troca(v+esq, v+dir);
			++esq, --dir;	// continuo dos proximos
		}
	}
	while (esq<dir);
	quicksort(v, e, dir);
	quicksort(v, esq, d);
}

