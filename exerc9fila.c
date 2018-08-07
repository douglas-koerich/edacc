#include <stdio.h>
#include <stdio_ext.h>
#include <ctype.h>
#include "tadfila.h"

void tiraMenores(struct Fila*, int);

int main() {
	struct Fila* f = cria(10);

	bool chega = false;
	while (!chega) {
		print(f);
		char opcao;
		do {
			printf("Digite 'i' para inserir, 'r' para remover, 'z' para sair: ");
			__fpurge(stdin);
			opcao = toupper(getchar());
		} while (opcao != 'I' && opcao != 'R' && opcao != 'Z');
		if (opcao == 'Z') {
			chega = true;
			continue;	// volta imediatamente para o while()
		}
		int num;
		if (opcao == 'I') {
			printf("Digite um novo numero: ");
			scanf("%d", &num);
			if (!enqueue(f, num)) {
				puts("Erro ao por na fila!");
			}
		}
		else {
			if (!dequeue(f, &num)) {
				puts("Erro ao tirar da fila!");
			}
		}
	}
	int valor;
	printf("Digite o valor de comparacao: ");
	scanf("%d", &valor);
	tiraMenores(f, valor);
	print(f);
	destroi(f);
	return 0;
}

void tiraMenores(struct Fila* f, int referencia) {
	struct Fila* aux = cria(100);
	int num;

	// Remove todos os elementos da fila (se deixar algum,
	// quando os outros voltarem a ordem tera sido alterada)
	while (!underflow(f)) {
		dequeue(f, &num);
		// So leva para a outra fila os valores maiores ou
		// iguais a referencia
		if (num >= referencia) {
			if (!enqueue(aux, num)) {
				puts("Erro ao por na fila auxiliar!");
				destroi(aux);	// nao esquecer, senao vai ficar lixo na memoria!
				return;
			}
		}
	}
	// Quando a fila de interesse ficar vazia, terao sido transferidos para a fila
	// auxiliar apenas os valores maiores ou iguais a referencia; agora temos que
	// volta-los para a fila original
	while (!underflow(aux)) {
		dequeue(aux, &num);
		enqueue(f, num);
	}
	destroi(aux);
}
