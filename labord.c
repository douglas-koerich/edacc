#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "registro.h"
#include "algord.h"

int main() {
	srand((unsigned) time(0));
	FILE* arquivo = fopen("/tmp/result.csv", "wt");
	if (arquivo == NULL) {
		perror("Nao pude criar o arquivo");
		return -1;
	}
	fputs("Tamanho;Bubble;Selecao;Insercao;Shell;Radix;Merge;Quick\n", arquivo);
	long tamanho = 1024L;
	while (tamanho <= 16L*1024L*1024L) {
		fprintf(arquivo, "%ld;", tamanho);
		Registro* original = (Registro*) malloc(tamanho*sizeof(Registro)),
				* copia = (Registro*) malloc(tamanho*sizeof(Registro));
		long i;
		printf("Gerando %ld registros...\n", tamanho);
		for (i=0; i<tamanho; ++i) {
			original[i].chave = copia[i].chave = rand();
		}
		struct timespec antes, depois;
		long long _antes, _depois;

		if (tamanho <= 128L*1024L) {
			printf("Ordenando por bolha...");
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
			bubblesort(original, tamanho);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
			puts(" Feito!");
			_antes = antes.tv_sec*1000000000LL+antes.tv_nsec;
			_depois = depois.tv_sec*1000000000LL+depois.tv_nsec;
			fprintf(arquivo, "%lld;", _depois-_antes);
			memcpy(original, copia, sizeof(Registro)*tamanho);

			printf("Ordenando por selecao...");
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
			selectsort(original, tamanho);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
			puts(" Feito!");
			_antes = antes.tv_sec*1000000000LL+antes.tv_nsec;
			_depois = depois.tv_sec*1000000000LL+depois.tv_nsec;
			fprintf(arquivo, "%lld;", _depois-_antes);
			memcpy(original, copia, sizeof(Registro)*tamanho);

			printf("Ordenando por insercao...");
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
			insertsort(original, tamanho);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
			puts(" Feito!");
			_antes = antes.tv_sec*1000000000LL+antes.tv_nsec;
			_depois = depois.tv_sec*1000000000LL+depois.tv_nsec;
			fprintf(arquivo, "%lld;", _depois-_antes);
			memcpy(original, copia, sizeof(Registro)*tamanho);

			printf("Ordenando por shell...");
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
			shellsort(original, tamanho);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
			puts(" Feito!");
			_antes = antes.tv_sec*1000000000LL+antes.tv_nsec;
			_depois = depois.tv_sec*1000000000LL+depois.tv_nsec;
			fprintf(arquivo, "%lld;", _depois-_antes);
			memcpy(original, copia, sizeof(Registro)*tamanho);
		}
		else {
			fputs("0;0;0;0;", arquivo);
		}
		printf("Ordenando por raiz...");
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
		radixsort(original, tamanho);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
		puts(" Feito!");
		_antes = antes.tv_sec*1000000000LL+antes.tv_nsec;
		_depois = depois.tv_sec*1000000000LL+depois.tv_nsec;
		fprintf(arquivo, "%lld;", _depois-_antes);
		memcpy(original, copia, sizeof(Registro)*tamanho);

		printf("Ordenando por merge...");
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
		mergesort(original, 0, tamanho-1);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
		puts(" Feito!");
		_antes = antes.tv_sec*1000000000LL+antes.tv_nsec;
		_depois = depois.tv_sec*1000000000LL+depois.tv_nsec;
		fprintf(arquivo, "%lld;", _depois-_antes);
		memcpy(original, copia, sizeof(Registro)*tamanho);

		printf("Ordenando por quick...");
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);
		quicksort(original, 0, tamanho-1);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
		puts(" Feito!");
		_antes = antes.tv_sec*1000000000LL+antes.tv_nsec;
		_depois = depois.tv_sec*1000000000LL+depois.tv_nsec;
		fprintf(arquivo, "%lld\n", _depois-_antes);

		free(original);
		free(copia);
		tamanho *= 2;
	}
	fclose(arquivo);
	return 0;
}

