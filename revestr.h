#ifndef REVESTR_H
#define REVESTR_H

#define MAX_DESC	200
#define MAX_CLIENTE	100

struct data {
	int dia, mes, ano;
};

struct ordem_de_servico {
	int numero_OS;
	struct data data_OS;
	float valor;
	char descricao[MAX_DESC], cliente[MAX_CLIENTE];
};

/*
struct ordem_de_servico {
	int numero_OS;
	struct {	// estrutura aninhada e anonima
		int dia, mes, ano;
	} data_OS;	// nome do campo, nao da estrutura!!!
	float valor;
	char descricao[MAX_DESC];
	char cliente[MAX_CLIENTE];
};
*/

#endif