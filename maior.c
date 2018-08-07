#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

int maior(int*, int);
int maior_r(int*, int, int);
int maior_l(int*, int);

int main(int argc, char* argv[]) {
	struct rlimit rlim;
	if (getrlimit(RLIMIT_STACK, &rlim) < 0) {
		puts("Nao pode ler o valor limite da pilha");
		return EXIT_FAILURE;
	}
	printf("Pilha: cur=%lld, max=%lld.\n", (long long) rlim.rlim_cur, (long long) rlim.rlim_max);

	if (argc < 2) {
		puts("Numero invalido de parametros");
		printf("Digite %s <arquivo>\n", argv[0]);
		return EXIT_FAILURE;
	}
	FILE* arq = fopen(argv[1], "wt");
	if (arq == NULL) {
		puts("Nao pode criar o arquivo");
		return EXIT_FAILURE;
	}

	rlim.rlim_cur = 128 * 1024 * 1024;	// 128 MB
	if (setrlimit(RLIMIT_STACK, &rlim) < 0) {
		puts("Nao pode mudar o valor limite da pilha");
		return EXIT_FAILURE;
	}
	printf("Pilha: cur=%lld, max=%lld.\n", (long long) rlim.rlim_cur, (long long) rlim.rlim_max);

	// Sem a semente randomica, todas as vezes gera a mesma sequencia
	// srand((unsigned) time(0));
	int n, t;
	for (n=50000; n<2500000; n+=50000) {
		int* vetor = (int*) malloc(sizeof(int)*n);
		if (vetor == NULL) {
			puts("Erro de alocacao do vetor");
			return EXIT_FAILURE;
		}

		int i;
		for (i=0; i<n; ++i) {
			vetor[i] = rand();
			// printf("%010d ", vetor[i]);
		}
		// putchar('\n');

		fprintf(arq, "%d;", n);
		for (t=0; t<5; ++t) {
			struct timespec antes, depois;
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &antes);

			int indMaior = maior(vetor, n);

			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &depois);
			unsigned long long ll_antes = antes.tv_sec*1000000000+antes.tv_nsec,
				ll_depois = depois.tv_sec*1000000000+depois.tv_nsec;
			fprintf(arq, "%llu;", ll_depois-ll_antes);
		}
		fputc('\n', arq);
		free(vetor);
	}
	fclose(arq);
	return EXIT_SUCCESS;
}

int maior(int* vetor, int n) {
	// return maior_l(vetor, n);
	return maior_r(vetor, 0, n-1);
}

int maior_r(int* vetor, int inf, int sup) {
	if (inf == sup) {								// 3 +
		return inf;									// 2 (condicao terminal)
	}
	int meio = (inf+sup)/2;							// 5 +
	int maior_inf = maior_r(vetor, inf, meio);		// FC(n/2) + 4 +
	int maior_sup = maior_r(vetor, meio+1, sup);	// FC(n/2) + 5 +
	if (vetor[maior_inf] > vetor[maior_sup]) {		// 9 +
		return maior_inf;							// 2
	}
	else {
		return maior_sup;
	}
}
/* Funcao de complexidade (FC) de maior_r()
 *         | 5				, se n = 1
 * FC(n) = |
 *         | 2FC(n/2) + 28	, se n > 1
 */

int maior_l(int* vetor, int num) {
	if (num == 1) {									// 2 +
		return 0;									// 1 (condicao terminal)
	}
	int maior_seg = maior_l(vetor+1, num-1) + 1;	// 6 + FC(n-1) +
	if (vetor[0] > vetor[maior_seg]) {				// 8 +
		return 0;									
	}
	else {
		return maior_seg;							// 2
	}
}
/* Funcao de complexidade (FC) de maior_l()
 *         | 3				, se n = 1
 * FC(n) = | ou
 *         | FC(n-1) + 18	, se n > 1
 *
 * Resolvendo a equacao de recorrencia, chegamos a FC(n) = 18n - 15
 * A ordem de complexidade (classe assintotica) eh O(n)
 */

