#include <stdio.h>
#include <stdio_ext.h>
#include "aluno.h"

#define NUM_ALUNOS 5

int main() {
	aluno turma[NUM_ALUNOS];
	int a;

	for (a=0; a<NUM_ALUNOS; ++a) {
		printf("Dados do aluno #%d:\n", a+1);
		printf("Nome? "); __fpurge(stdin); gets(turma[a].nome);
		printf("Media? "); scanf("%f", &turma[a].media);
	}
	aluno* p;
	float maior;
	int indmaior;
	for (a=0, p=turma; a<NUM_ALUNOS; ++a, ++p) {
		if (a == 0) {
			maior = p->media;
			indmaior = 0;
		}
		else {
			if (p->media > maior) {
				maior = p->media;
				indmaior = a;
			}
		}
	}
	printf("O aluno com maior media eh %s\n", turma[indmaior].nome);
	return 0;
}

