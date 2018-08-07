#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "revestr.h"	// para obter/conhecer as definicoes relativas a estrutura

int main() {
	char cliente_abonado[MAX_CLIENTE] = "(desconhecido)";	// nome do cliente que executou o servico mais caro
	char descricao_mais_caro[MAX_DESC] = "";
	struct data data_mais_caro = { /*dia*/ 1, /*mes*/ 1, /*ano*/ 1970 };
	float valor_mais_caro = -1.0, media = 0.0;
	int contador_clientes = 0;

	struct ordem_de_servico entrada;

	do {
		printf("Dados de um novo cliente: Numero da OS? ");
		scanf("%d", &entrada.numero_OS);	// endereco do campo dentro do registro
		if (entrada.numero_OS > 0) {
			// Entrada de dados
			printf("Digite a data de servico (d/m/a)? ");
			scanf("%d/%d/%d", &entrada.data_OS.dia, &entrada.data_OS.mes, &entrada.data_OS.ano);
			printf("Valor cobrado (R$)? ");
			scanf("%f", &entrada.valor);
			printf("Descricao do servico: ");
			fflush(stdin);	// limpa o teclado (em Windows!)
			gets(entrada.descricao);
			printf("Nome do cliente: ");
			fflush(stdin);
			gets(entrada.cliente);

			// Atualizacao do calculo baseado na nova OS
			media += entrada.valor;
			if (entrada.valor > valor_mais_caro) {
				valor_mais_caro = entrada.valor;
				strcpy(descricao_mais_caro, entrada.descricao);
				strcpy(cliente_abonado, entrada.cliente);
				data_mais_caro = entrada.data_OS;	// quando nao ha strings nem ponteiros envolvidos!!
			}
			++contador_clientes;
		}
	} while (entrada.numero_OS > 0);

	media /= contador_clientes;
	printf("A media de valores eh %.2f\n", media);
	printf("O cliente %s pagou o maior valor pelo servico %s na data %02d/%02d/%04d\n",
		   cliente_abonado, descricao_mais_caro, data_mais_caro.dia, data_mais_caro.mes, data_mais_caro.ano);

	return EXIT_SUCCESS;
}
