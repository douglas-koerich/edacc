#ifndef REVISAO_1_H
#define REVISAO_1_H

#define NUM_NOTAS 4
#define MAX_NOME 80 // incluindo o '\0' (terminador nulo)

// Definicao de um novo tipo de dado para ser "reconhecido"
// pelo compilador
struct aluno {
	// Campos da estrutura
	char nome[MAX_NOME]; // Nome
	float notas[NUM_NOTAS]; // 4 notas
	float media; // Media
};
// Renomeacao de tipo para evitar o uso da palavra-chave 'struct'
typedef struct aluno Aluno; // poderia ser com 'a' minusculo tambem :-)

#endif // REVISAO_1_H