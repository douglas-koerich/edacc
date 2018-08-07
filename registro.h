#ifndef REGISTRO_H
#define REGISTRO_H

#define MAX_STRING	10

// Nossa estrutura de registro usada como exemplo no processo de ordenacao
// e busca
struct Registro {
	int chave;						// chave (unica/"primaria") de ordenacao e busca
	char descricao[MAX_STRING+1];	// campos ilustrativos, nao vamos preenche-los
	float valor;
};
typedef struct Registro Registro;	// para nao digitar 'struct' no codigo-fonte

#endif // REGISTRO_H

