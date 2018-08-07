#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "registro.h"
#include "ordenacao.h"

// O numero de chamadas recursivas de merge e quicksort fara a pilha estourar
// com seu tamanho pre-definido! Por isso, precisamos aumentar esse tamanho
#include <sys/time.h>
#include <sys/resource.h>

long long converte(const struct timespec*);

int main(int argc, char* argv[]) {
	struct rlimit rlim;
	if (getrlimit(RLIMIT_STACK, &rlim) < 0) {
		puts("Nao pode ler o valor limite da pilha");
		return -1;
	}
	/*
	printf("Tamanho da pilha: atual=%lld, max=%lld.\n",
		(long long) rlim.rlim_cur, (long long) rlim.rlim_max);
	*/
	rlim.rlim_cur = 128 * 1024 * 1024;	// 128 MB
	if (setrlimit(RLIMIT_STACK, &rlim) < 0) {
		puts("Nao pode mudar o valor limite da pilha");
		return -1;
	}
	srand((unsigned)time(0));
	int tamanho;
	FILE* arquivo = fopen("/tmp/tabela.txt", "wt");
	if (arquivo == NULL) {
		perror("Nao pude criar o arquivo");
		return -1;
	}
	fprintf(arquivo, "Tamanho;Bolha;Selecao;Insercao;Shell;Radix;Merge;Quick\n");
	for (tamanho = 2<<5; tamanho <= (2<<24); tamanho *= 2) {
		printf("Calculando para tamanho=%d: ", tamanho);
		fprintf(arquivo, "%d;", tamanho);

		Registro* vetor = (Registro*) malloc(sizeof(Registro)*tamanho);
		Registro* copia = (Registro*) malloc(sizeof(Registro)*tamanho);

		// Gera um vetor aleatorio
		int i;
		for (i=0; i<tamanho; ++i) {
			vetor[i].chave = rand();
		}
		memcpy(copia, vetor, tamanho*sizeof(Registro));

		/**
		 * ord_medtempo: Usando funcoes para medir o tempo cronologico gasto pelo
		 * algoritmo
		 **/
		// clock_t antes, depois;
		
		/**
		 * ord_medreal: Usando funcoes para medir o tempo util de CPU gasto pelo
		 * algoritmo
		 **/
		struct timespec antes, depois;
		long long _antes, _depois;

		if (tamanho < (2<<16)) {
			putchar('B'); fflush(stdout);
			/* ord_medtempo
			antes = clock();	// estampa de tempo anterior
			bubble(vetor, tamanho);
			depois = clock();	// estampa de tempo posterior
			fprintf(arquivo, "%f;", (float)(depois-antes)/CLOCKS_PER_SEC);
			*/
			// ord_medcpu
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
			bubble(vetor, tamanho);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
			_antes = converte(&antes);
			_depois = converte(&depois);
			fprintf(arquivo, "%lld;", _depois-_antes);

			memcpy(vetor, copia, tamanho*sizeof(Registro));

			putchar('S'); fflush(stdout);
			/* ord_medtempo
			antes = clock();
			select_(vetor, tamanho);
			depois = clock();
			fprintf(arquivo, "%f;", (float)(depois-antes)/CLOCKS_PER_SEC);
			*/
			// ord_medcpu
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
			select_(vetor, tamanho);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
			_antes = converte(&antes);
			_depois = converte(&depois);
			fprintf(arquivo, "%lld;", _depois-_antes);

			memcpy(vetor, copia, tamanho*sizeof(Registro));

			putchar('I'); fflush(stdout);
			/* ord_medtempo
			antes = clock();
			insert(vetor, tamanho);
			depois = clock();
			fprintf(arquivo, "%f;", (float)(depois-antes)/CLOCKS_PER_SEC);
			*/
			// ord_medcpu
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
			insert(vetor, tamanho);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
			_antes = converte(&antes);
			_depois = converte(&depois);
			fprintf(arquivo, "%lld;", _depois-_antes);

			memcpy(vetor, copia, tamanho*sizeof(Registro));
		}
		else {
			fprintf(arquivo,"0.0;0.0;0.0;");
		}
		if (tamanho < (2<<20)) {
			putchar('H'); fflush(stdout);
			/* ord_medtempo
			antes = clock();
			shell(vetor, tamanho);
			depois = clock();
			fprintf(arquivo, "%f;", (float)(depois-antes)/CLOCKS_PER_SEC);
			*/
			// ord_medcpu
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
			shell(vetor, tamanho);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
			_antes = converte(&antes);
			_depois = converte(&depois);
			fprintf(arquivo, "%lld;", _depois-_antes);

			memcpy(vetor, copia, tamanho*sizeof(Registro));
		}
		else {
			fprintf(arquivo,"0.0;");
		}
		putchar('R'); fflush(stdout);
		/* ord_medtempo
		antes = clock();
		radix(vetor, tamanho);
		depois = clock();
		fprintf(arquivo, "%f;", (float)(depois-antes)/CLOCKS_PER_SEC);
		*/
		// ord_medcpu
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
		radix(vetor, tamanho);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
		_antes = converte(&antes);
		_depois = converte(&depois);
		fprintf(arquivo, "%lld;", _depois-_antes);

		memcpy(vetor, copia, tamanho*sizeof(Registro));

		putchar('M'); fflush(stdout);
		/* ord_medtempo
		antes = clock();
		merge(vetor, 0, tamanho-1);
		depois = clock();
		fprintf(arquivo, "%f;", (float)(depois-antes)/CLOCKS_PER_SEC);
		*/
		// ord_medcpu
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
		merge(vetor, 0, tamanho-1);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
		_antes = converte(&antes);
		_depois = converte(&depois);
		fprintf(arquivo, "%lld;", _depois-_antes);

		memcpy(vetor, copia, tamanho*sizeof(Registro));

		puts("Q");
		/* ord_medtempo
		antes = clock();
		quick(vetor, 0, tamanho-1);
		depois = clock();
		fprintf(arquivo, "%f\n", (float)(depois-antes)/CLOCKS_PER_SEC);
		*/
		// ord_medcpu
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
		quick(vetor, 0, tamanho-1);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
		_antes = converte(&antes);
		_depois = converte(&depois);
		fprintf(arquivo, "%lld\n", _depois-_antes);

		free(vetor);
		free(copia);
	}
	fclose(arquivo);
	return 0;
}

long long converte(const struct timespec* t) {
	return t->tv_sec*1000000000LL + t->tv_nsec;
}

