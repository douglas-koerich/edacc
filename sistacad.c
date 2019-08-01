/* Elabore um programa que monte um cadastro de alunos de uma turma com
 * as seguintes informacoes: numero de matricula, nome, curso, notas (2)
 * na disciplina, e media final (aritmetica). Apos o cadastro ter sido
 * efetuado (concluindo com um numero de matricula nulo), calcule a
 * media de cada aluno armazenando-a no registro. Ao final, imprima um
 * pequeno relatorio da turma. */

#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>
#include "reg_aluno.h"

#define NUM_MAX_ALUNOS  100 // necessario pois o enunciado nao delimita uma
                            // quantidade de alunos na turma (no cadastro)

void imprime(Aluno [*], size_t); // toda passagem de vetor pra funcao precisa
                                 // ser acompanhada do seu tamanho (util)

int main(void) {
    Aluno turma[NUM_MAX_ALUNOS]; // vetor de registros/estruturas

    // Preenchimento do cadastro
    int matricula, i, n = 0; // n = numero de alunos (jah) cadastrados
    do {
        printf("Digite o numero de matricula do aluno: ");
        scanf("%d", &matricula);
        if (matricula != 0) { // continua o cadastro do aluno se matricula!=0
            turma[n].matricula = matricula;
            printf("Digite o nome do aluno: ");
            __fpurge(stdin); // "limpa" o buffer de entrada quando numa segunda leitura
            gets(turma[n].nome);
            printf("Curso: ");
            scanf("%d", &turma[n].curso); // & na frente de todo o nome da variavel+campo
            for (i=0; i<NUM_NOTAS; ++i) {
                printf("Digite a %da. nota: ", i+1);
                scanf("%f", &turma[n].nota[i]);
            }

            ++n; // incrementa o numero de alunos (e o indice da prox.repeticao)
        }
    } while (matricula != 0 && n < NUM_MAX_ALUNOS); // cuida para nao "estourar" o vetor

    // Completa o cadastro com o calculo da media pra cada aluno
    for (i=0; i<n; ++i) {
        int j;
        turma[i].media = 0.0;
        for (j=0; j<NUM_NOTAS; ++j) {
            turma[i].media += turma[i].nota[j];
        }
        turma[i].media /= NUM_NOTAS;
    }

    // Funcao que imprime o relatorio da turma
    imprime(turma, n);

    return EXIT_SUCCESS;
}

void imprime(Aluno vetor[], size_t tamanho) {
    puts("Matr. Nome---------------- Curso Nota-1 Nota-2 Media");
    int i;
    for (i=0; i<tamanho; ++i) {
        printf("%5d %20s %5d %6.1f %6.1f %5.1f\n",
               vetor[i].matricula,
               vetor[i].nome,
               vetor[i].curso,
               vetor[i].nota[0],
               vetor[i].nota[1],
               vetor[i].media);
    }
    puts("----------------------------------------------------");
}

