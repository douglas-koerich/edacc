#include <stdio.h>
#include <stdio_ext.h>
#include <ctype.h>
#include "tadfila.h"

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
	destroi(f);
	return 0;
}
