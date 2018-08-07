#ifndef REVISAO_H
#define REVISAO_H

#define MAX_NOME    100
#define MAX_PARTIDO 20

struct Candidato {              // Registro do candidato (nao eh uma variavel!)
    int numero;                 // Campos do registro
    char nome[MAX_NOME];
    char partido[MAX_PARTIDO];
    int votos;
};
typedef struct Candidato Candidato; // O segundo "Candidato" eh um apelido para
                                    // o nome da estrutura (primeiro "Candidato")

#endif
