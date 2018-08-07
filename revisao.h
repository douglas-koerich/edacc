#ifndef REVISAO_H
#define REVISAO_H

#include <stdbool.h>

#define MAX_NOME	80

struct paciente {			// Nome do tipo-registro
	char nome[MAX_NOME];	// Campo: nome do paciente
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

void cadastraPacientes(paciente [*], size_t);
size_t selecionaDoadores(paciente [*], paciente [*], size_t, size_t);

#endif

