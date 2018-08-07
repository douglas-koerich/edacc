#include <stdio.h>
#include "convbase.h"

//--- Inicio da implementacao do TAD ---
void inicia(Pilha* p) {
	p->topo = -1;
}

bool overflow(Pilha* p) {
	return p->topo == MAX_PILHA-1;
}

bool underflow(Pilha* p) {
	return p->topo == -1;
}

bool push(Pilha* p, int dig) {
	if (overflow(p)) {
		return false;
	}
	p->digitos[++p->topo] = dig;
	return true;
}

bool pop(Pilha* p, int* dig) {
	if (underflow(p)) {
		return false;
	}
	*dig = p->digitos[p->topo--];
	return true;
}
//--- Fim da implementacao do TAD ---

int main() {
	// Vai imprimir na tela os digitos binarios correspondentes
	// ao numero decimal fornecido como entrada
	unsigned numero;

	printf("Digite um numero: ");
	scanf("%u", &numero);

	// Vamos usar uma pilha como estrutura de dados auxiliar; eh
	// preciso declarar essa pilha
	Pilha auxiliar;
	inicia(&auxiliar);

	// Armazena na pilha cada um dos restos obtidos pela divisao
	// sucessiva por 2 (metodo da divisao para conversao de base)
	while (numero > 0) {
		int resto = numero % 2;
		if (push(&auxiliar, resto) == false) {
			puts("Estouro da pilha, abortando...");
			return -1;
		}
		numero = numero / 2;	// numero /= 2;
	}
	// Para imprimir o numero binario, basta retirar cada digito
	// da pilha e imprimir na tela
	printf("Convertido para binario: ");
	while (underflow(&auxiliar) == false) { // enquanto pilha NAO vazia...
		int d;
		if (pop(&auxiliar, &d) == false) {	// teste adicional, na verdade nao
											// teria entrado no while se estivesse
											// vazia (underflow seria true)
			puts("Algo errado aconteceu, encontrei o fim da pilha!...");
			return -1;
		}
		putchar(d + '0');	// aquele "macete" da tabela ASCII... :-)
	}
	putchar('\n');
	return 0;
}

