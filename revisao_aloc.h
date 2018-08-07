#ifndef REVISAO_H
#define REVISAO_H

#include <stdbool.h>

struct paciente {			// Nome do tipo-registro
	char* nome;				// Campo: nome do paciente (endereco da string alocada dinamicamente)
	char sexo;				// Campo: sexo
	int idade;				// Campo: idade do paciente
	char sangue[3];			// Campo: tipo sanguineo "AB\0" (3 caracteres)
	bool doador;			// Campo: doador de orgaos (logico/booleano)
};
typedef struct paciente paciente;	// Para nao usar a palavra 'struct'

/* typedef struct {
 * 	...
 * } paciente;
 */

void cadastraPacientes(paciente*, size_t);
size_t selecionaDoadores(const paciente*,	// const = nao pode alterar o vetor apontado
						 paciente*,			// sem const = a funcao pode alterar o vetor apontado
						 size_t, size_t);

#endif

