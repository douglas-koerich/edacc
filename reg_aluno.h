#ifndef REG_ALUNO_H
#define REG_ALUNO_H

#define MAX_NOME 80
#define NUM_NOTAS 2

struct aluno { // DEFINICAO do registro (nao eh uma variavel aqui!)
    int matricula;
    char nome[MAX_NOME];
    int curso;
    float nota[NUM_NOTAS], media;
}; // novo tipo de dado/variavel a ser reconhecido pelo compilador

typedef struct aluno Aluno; // Aluno: nome do tipo sem precisar usar 'struct'

#endif // REG_ALUNO_H
