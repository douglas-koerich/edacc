#include <stdio.h>

int pot(int, int);
int fat(int);
int fib(int);

int main() {
	int base, expoente, potencia, fatorial, fibonacci;

	printf("Digite o valor da base: ");
	scanf("%d", &base);

	printf("Digite o valor do expoente: ");
	scanf("%d", &expoente);

	potencia = pot(base, expoente);
	
	fatorial = fat(base);

	fibonacci = fib(base);

	printf("%d elevado a %d eh igual a %d\n", base, expoente, potencia);
	printf("O fatorial de %d eh %d\n", base, fatorial);
	printf("O numero de fibonacci de ordem %d eh %d\n", base, fibonacci);

	return 0;
}

int pot(int b, int e) {
	int p;
	if (e > 0) {	// Condicao terminal (teste para interromper recursao)
		// Chamada recursiva (funcao chamando a si mesma)
		p = b * pot(b, e-1);
	}
	else {
		// Nao ha recursividade
		p = 1;
	}
	return p;
}

int fat(int n) {
	if (n == 0) {
		return 1;
	}
	return n * fat(n-1);
}

int fib(int N) {
	if (N <= 1) {
		return N;
	}
	return fib(N-1) + fib(N-2);
}

