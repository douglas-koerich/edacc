#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilha.h"
#include "fila.h"

void inverteFila(Fila* f) {
	// Usa uma pilha como estrutura auxiliar do processo de inversao
	// (lembre-se: a pilha eh uma LIFO!)
	Pilha auxiliar;
	p_inicia(&auxiliar, f_tamanho(f));	// mesmo tamanho da fila

	// Traz todos os elementos da fila para a pilha
	while (!f_underflow(f)) {
		int num;
		dequeue(f, &num);
		push(&auxiliar, num);
	}
	// Devolve todos os elementos para a fila
	while (!p_underflow(&auxiliar)) {
		int num;
		pop(&auxiliar, &num);
		enqueue(f, num);
	}
	p_finaliza(&auxiliar);
}

int main() {
	size_t tamFila;
	printf("Qual o tamanho maximo da fila? ");
	scanf("%u", &tamFila);

	// Cria a fila que sera usada para testar a funcao inverteFila()
	Fila a_Fila;
	f_inicia(&a_Fila, tamFila);

	// Preenche metade da fila com numeros aleatorios (randomicos)
	srand((unsigned) time(0));
	size_t i;
	for (i=0; i<tamFila/2; ++i) {
		int num = rand() % 100;	// numeros de 0 a 99
		if (!enqueue(&a_Fila, num)) {
			puts("Erro ao inserir na fila de teste!");
			f_finaliza(&a_Fila);	// previne memory leak!
			return -1;
		}
	}
	// Imprime a fila como ficou
	printf("Antes da inversao: ");
	f_imprime(&a_Fila);

	// Chama a funcao que inverte a fila
	inverteFila(&a_Fila);

	// Imprime a fila apos a inversao
	printf("Depois da inversao: ");
	f_imprime(&a_Fila);

	f_finaliza(&a_Fila);
	return 0;
}
