#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "algord.h"

int main() {
	unsigned m, expoente = 2, mantissa[3] = { 1, 2, 5 }, antes, depois;
	Registro_Exemplo* vetoriginal, * vetbackup;
	FILE* tabela = fopen("/tmp/tabela.txt", "wt");
	if (tabela == NULL) {
		return -1;
	}
	fputs("N;Bolha;Selecao;Insercao;Radix;Shell;Merge;Quick\n", tabela);
	while (expoente <= 6) {
		for (m = 0; m < 3; ++m) {
			int i, j;
			unsigned tam = mantissa[m]*pow(10, expoente);
			vetoriginal = (Registro_Exemplo*) malloc(sizeof(Registro_Exemplo)*tam);
			vetbackup = (Registro_Exemplo*) malloc(sizeof(Registro_Exemplo)*tam);
			printf("Gerando vetor com %u elementos...\n", tam);
			for (i = tam-1, j = 0; i >= 0; --i, j++) {
				vetoriginal[i].chave_ordenacao = vetbackup[i].chave_ordenacao = j;
			}
			fprintf(tabela, "%u;", tam);
			if (tam <= 100000) {
				puts("Ordenando por bolha...");
				antes = clock();
				ordBolha(vetoriginal, tam);
				depois = clock();
				fprintf(tabela, "%u;", (depois-antes)/10000);
				memcpy(vetoriginal, vetbackup, tam*sizeof(unsigned));

				puts("Ordenando por selecao...");
				antes = clock();
				ordSelecao(vetoriginal, tam);
				depois = clock();
				fprintf(tabela, "%u;", (depois-antes)/10000);
				memcpy(vetoriginal, vetbackup, tam*sizeof(unsigned));

				puts("Ordenando por insercao...");
				antes = clock();
				ordInsercao(vetoriginal, tam);
				depois = clock();
				fprintf(tabela, "%u;", (depois-antes)/10000);
				memcpy(vetoriginal, vetbackup, tam*sizeof(unsigned));

				puts("Ordenando por radix...");
				antes = clock();
				ordRadix(vetoriginal, tam);
				depois = clock();
				fprintf(tabela, "%u;", (depois-antes)/10000);
				memcpy(vetoriginal, vetbackup, tam*sizeof(unsigned));
			}
			else {
				fprintf(tabela, "0;0;0;0;");
			}
			puts("Ordenando por shell...");
			antes = clock();
			ordShell(vetoriginal, tam);
			depois = clock();
			fprintf(tabela, "%u;", (depois-antes)/10000);
			memcpy(vetoriginal, vetbackup, tam*sizeof(unsigned));

			puts("Ordenando por merge...");
			antes = clock();
			ordMerge(vetoriginal, 0, tam-1);
			depois = clock();
			fprintf(tabela, "%u;", (depois-antes)/10000);
			memcpy(vetoriginal, vetbackup, tam*sizeof(unsigned));

			puts("Ordenando por quick...");
			antes = clock();
			ordQuick(vetoriginal, 0, tam-1);
			depois = clock();
			fprintf(tabela, "%u\n", (depois-antes)/10000);

			free(vetoriginal);
			free(vetbackup);
		}
		++expoente;
	}
	fclose(tabela);
	return 0;
}
