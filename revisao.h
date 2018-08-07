#ifndef _REVISAO_H_
#define _REVISAO_H_

#define MAX_NOME		80
#define MAX_ENDERECO	200

// Registro de cliente
struct Cliente {
	unsigned codigo;
	char nome[MAX_NOME],
		 endereco[MAX_ENDERECO];
	struct {
		unsigned ddd, numero;
	} fone;
};
typedef struct Cliente Cliente;

// Registro de recebimento (documento)
typedef struct Recebimento {
	unsigned numero;
	float valor;
	struct {
		unsigned dia, mes, ano;
	} emissao, vencimento;
	unsigned cliente;
} Documento;

#endif // _REVISAO_H_

