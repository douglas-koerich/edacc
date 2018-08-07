#include <stdio.h>
#include <stdio_ext.h>
#include <ctype.h>
#include "tad_deque.h"

int main() {
	struct Deque* d = cria(10);

	bool chega = false;
	while (!chega) {
		print(d);
		char operacao;
		do {
			printf("Digite 'i' para inserir, 'r' para remover, 'z' para sair: ");
			__fpurge(stdin);
			operacao = toupper(getchar());
		} while (operacao != 'I' && operacao != 'R' && operacao != 'Z');
		if (operacao == 'Z') {
			chega = true;
			continue;	// volta imediatamente para o while()
		}
		char lado;
		do {
			printf("Digite 'i' para inicio, 'f' para fim: ");
			__fpurge(stdin);
			lado = toupper(getchar());
		} while (lado != 'I' && lado != 'F');
		int num;
		if (operacao == 'I') {
			printf("Digite um novo numero: ");
			scanf("%d", &num);
			if (!inserir(d, lado=='I'? INICIO: FIM, num)) {
				puts("Erro ao por no deque!");
			}
		}
		else {
			if (!remover(d, lado=='I'? INICIO: FIM, &num)) {
				puts("Erro ao tirar do deque!");
			}
		}
	}
	destroi(d);
	return 0;
}
