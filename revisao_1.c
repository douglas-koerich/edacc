/* Exemplo com vetores */
// Um programa que leh as 4 notas bimestrais de um aluno e calcula a
// sua media

#include <stdlib.h>
#include <stdio.h>
#include "revisao_1.h"

#define NUM_ALUNOS 2

int main(void) {
#if 0 // pre-processador diz: "se FALSO compile" (entao nunca vai compilar)
	// float n1, n2, n3, n4;
	// float notas[4]; <-- entre colchetes o numero de elementos
	float notas[NUM_NOTAS];

	/*
	printf("Digite a 1a. nota do aluno: ");
	// scanf("%f", &n1);
	scanf("%f", &notas[0]);
	printf("Digite a 2a. nota do aluno: ");
	// scanf("%f", &n2);
	scanf("%f", &notas[1]);
	printf("Digite a 3a. nota do aluno: ");
	// scanf("%f", &n3);
	scanf("%f", &notas[2]);
	printf("Digite a 4a. nota do aluno: ");
	// scanf("%f", &n4);
	scanf("%f", &notas[3]);
	*/
	int num;
	for (num = 1; num <= NUM_NOTAS; ++num) {
		printf("Digite a %da. nota do aluno: ", num);
		scanf("%f", &notas[num - 1]);
	}

	float media;
	// media = (n1 + n2 + n3 + n4) / 4;
	// media = (notas[0] + notas[1] + notas[2] + notas[3]) / 4;
	float soma; // variavel acumuladora
	for (num = 0, soma = 0.0; num < NUM_NOTAS; ++num) {
		soma += notas[num];
	}
	media = soma / NUM_NOTAS;

	printf("A media do aluno eh %.1f\n", media);
#endif

	/*
	struct aluno um_aluno; // usando o tipo original
	Aluno outro_aluno; // usando o tipo renomeado

	// Preenche os dados do primeiro aluno
	puts("Dados do(a) primeiro(a) aluno(a)");
	printf("Nome: ");
	gets(um_aluno.nome);

	int ind;
	for (ind = 0, um_aluno.media = 0.0; ind < NUM_NOTAS; ++ind) {
		printf("Digite a %da. nota de %s: ", ind + 1, um_aluno.nome);
		scanf("%f", &um_aluno.notas[ind]);
		um_aluno.media += um_aluno.notas[ind];
	}
	um_aluno.media /= NUM_NOTAS; // calcula a media dividindo a soma acumulada
	printf("A media de %s eh %.1f\n", um_aluno.nome, um_aluno.media);

	// Preenche os dados do segundo aluno
	puts("Dados do(a) segundo(a) aluno(a)");
	printf("Nome: ");
	fflush(stdin);
	gets(outro_aluno.nome);

	for (ind = 0, outro_aluno.media = 0.0; ind < NUM_NOTAS; ++ind) {
		printf("Digite a %da. nota de %s: ", ind + 1, outro_aluno.nome);
		scanf("%f", &outro_aluno.notas[ind]);
		outro_aluno.media += outro_aluno.notas[ind];
	}
	outro_aluno.media /= NUM_NOTAS; // calcula a media dividindo a soma acumulada
	printf("A media de %s eh %.1f\n", outro_aluno.nome, outro_aluno.media);
	*/

	Aluno turma[NUM_ALUNOS];

	// Preenche os dados de cada aluno
	int aluno;
	for (aluno = 0; aluno < NUM_ALUNOS; ++aluno) {
		puts("Dados do(a) %do.(a.) aluno(a)", aluno+1);
		printf("Nome: ");
		gets(turma[aluno].nome);

		int ind;
		for (ind = 0, turma[aluno].media = 0.0; ind < NUM_NOTAS; ++ind) {
			printf("Digite a %da. nota de %s: ", ind + 1, turma[aluno].nome);
			scanf("%f", &turma[aluno].notas[ind]);
			turma[aluno].media += turma[aluno].notas[ind];
		}
		turma[aluno].media /= NUM_NOTAS; // calcula a media dividindo a soma acumulada
		printf("A media de %s eh %.1f\n", turma[aluno].nome, turma[aluno].media);
	}
	system("pause");
	return EXIT_SUCCESS;
}