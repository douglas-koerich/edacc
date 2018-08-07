#include <stdio.h>
#include <stdio_ext.h>
#include "revisao.h"

#define MAX_CLIENTES	3
#define MAX_DOCUMENTOS	2

void preencheClientes(Cliente vetor[], size_t max) {
	unsigned c;

	// Para cada elemento do vetor...
	for (c=0; c<max; ++c) {
		printf("CADASTRO DO CLIENTE *%u*\n", c+1);
		printf("Codigo? "); scanf("%u", &vetor[c].codigo); __fpurge(stdin);
		printf("Nome? "); gets(vetor[c].nome); __fpurge(stdin);
		printf("Endereco? "); gets(vetor[c].endereco);
		printf("Telefone? "); scanf("%u %u", &vetor[c].fone.ddd, &vetor[c].fone.numero);
	}
}

int main() {
	// Meu "banco de dados"
	Cliente clientes[MAX_CLIENTES]; // ou struct Cliente clientes[MAX_...]
	Documento recebimentos[MAX_DOCUMENTOS]; // ou struct Recebimento recebimentos[MAX_...]

	unsigned r=0;

	// "Terceiriza" o preenchimento do vetor de clientes
	preencheClientes(clientes, MAX_CLIENTES);

	// Preenche o vetor de documentos
	while (r < MAX_DOCUMENTOS) {
		unsigned c;

		// Ponteiro para busca na "tabela" de clientes
		Cliente* cli;

		printf("CADASTRO DO %uo. DOCUMENTO\n", r+1);
		printf("Codigo do cliente? "); scanf("%u", &recebimentos[r].cliente);
		// Procura o codigo na "tabela" de clientes
		for (c=0, cli=clientes; c<MAX_CLIENTES; ++c, ++cli) {
			if (cli->codigo == recebimentos[r].cliente) {
				break;
			}
		}
		if (c == MAX_CLIENTES) {
			// Nao achou antes do fim...
			continue;	// Volta ao inicio do while(), sem incrementar r!
		}
		printf("Cliente: %s\n", cli->nome);
		printf("Numero do doc.: "); scanf("%u", &recebimentos[r].numero);
		printf("Valor: "); scanf("%f", &recebimentos[r].valor);
		printf("Emissao (d/m/a)? "); scanf("%u/%u/%u", &recebimentos[r].emissao.dia, &recebimentos[r].emissao.mes, &recebimentos[r].emissao.ano);
		printf("Vencimento (d/m/a)? "); scanf("%u/%u/%u", &recebimentos[r].vencimento.dia, &recebimentos[r].vencimento.mes, &recebimentos[r].vencimento.ano);
		++r;
	}
	return 0;
}

