#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include "agenda.h"

#define NUM_CONTATOS 5

void busca(struct contato vetor[], int tamanho, char nome[]) {
	int i;
	for (i=0; i<tamanho; ++i) {
		if (strcmp(nome, vetor[i].empresa) == 0) {	// strings iguais?
			// Se achou, imprime dados (soh o primeiro num. de telefone)
			printf("Empresa: %s, responsavel: %s, tel: %d %d.\n",
				   vetor[i].empresa, vetor[i].responsavel,
				   vetor[i].lista[0].ddd, vetor[i].lista[0].numero);
		}
	}
}

int main() {
	struct contato agenda[NUM_CONTATOS];
	int c;
	for (c=0; c<NUM_CONTATOS; ++c) {
		printf("CONTATO #%d:\n", c+1);

		printf("Nome da empresa? ");
		__fpurge(stdin);
		gets(agenda[c].empresa);

		printf("Responsavel? ");
		__fpurge(stdin);
		gets(agenda[c].responsavel);

		int t;
		for (t=0; t<MAX_FONES; ++t) {
			printf("Digite DDD e telefone separados por espaco: ");
			scanf("%d %d", &agenda[c].lista[t].ddd,
					       &agenda[c].lista[t].numero);
		}
	}
	char nome[MAX_EMPRESA+1];
	printf("Digite um nome para buscar: ");
	__fpurge(stdin);
	gets(nome);
	busca(agenda, NUM_CONTATOS, nome);
	return 0;
}

