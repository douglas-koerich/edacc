#include <stdlib.h>
#include <stdio.h>
#include <string.h>		// para strcmp
#include <ctype.h>		// para toupper
#include <stdio_ext.h>	// para __fpurge
#include "revisao.h"

#define MAX_PACIENTES	10

int main() {
	paciente banco_de_dados[MAX_PACIENTES];		// Banco de dados eh uma variavel-vetor de registros em memoria
	paciente banco_de_doadores[MAX_PACIENTES];	// Deve ter o mesmo tamanho para o caso de TODOS serem doadores

	size_t numero;
	do {
		printf("Quantos pacientes vai cadastrar? ");
		scanf("%u", &numero);
	} while (numero > MAX_PACIENTES);	// Testa se nao ultrapassa a capacidade do vetor

	// Chama a funcao para preencher o cadastro
	cadastraPacientes(banco_de_dados, numero);

	// Percorre o vetor/banco de dados para conferencia
	size_t indice;
	puts("LISTA GERAL:");
	for (indice = 0; indice < numero; ++indice) {
		printf("%20s %c %2d %-3s %c\n",
			   banco_de_dados[indice].nome,
			   banco_de_dados[indice].sexo,
			   banco_de_dados[indice].idade,
			   banco_de_dados[indice].sangue,
			   (banco_de_dados[indice].doador? 'S': 'N'));
	}

	// Chama a funcao para selecionar os doadores
	size_t doadores = selecionaDoadores(banco_de_dados, banco_de_doadores, numero, MAX_PACIENTES);

	// Percorre o vetor/banco de dados de doadores para conferencia
	puts("LISTA DE DOADORES:");
	for (indice = 0; indice < doadores; ++indice) {
		printf("%20s %c %2d %-3s %c\n",
			   banco_de_doadores[indice].nome,
			   banco_de_doadores[indice].sexo,
			   banco_de_doadores[indice].idade,
			   banco_de_doadores[indice].sangue,
			   (banco_de_doadores[indice].doador? 'S': 'N'));
	}
	return 0;
}

void cadastraPacientes(paciente lista_pacientes[],	// Vetor de pacientes que vai ser preenchido
					   size_t num) {				// Numero de posicoes para preencher
	size_t ind;
	for (ind = 0; ind < num; ++ind) {
		printf("Dados do paciente #%d\n", ind+1);
		printf("Nome? ");
		__fpurge(stdin);	// Limpa o buffer do teclado (Linux-only)
		gets(lista_pacientes[ind].nome);

		do {
			printf("Sexo (M/F)? ");
			__fpurge(stdin);
			lista_pacientes[ind].sexo = toupper(getchar());
		} while (lista_pacientes[ind].sexo != 'M' && lista_pacientes[ind].sexo != 'F');

		printf("Idade? ");
		scanf("%d", &lista_pacientes[ind].idade);

		printf("Tipo sanguineo (A/B/O/AB)? ");
		__fpurge(stdin);
		gets(lista_pacientes[ind].sangue);

		char opcao;
		do {
			printf("Doador de orgaos (S/N)? ");
			__fpurge(stdin);
			opcao = toupper(getchar());
		} while (opcao != 'S' && opcao != 'N');
		lista_pacientes[ind].doador = (opcao == 'S');	// armazena o resultado logico da comparacao
	}
}

size_t selecionaDoadores(	// Retorna o numero de pacientes copiados para o segundo vetor (<= max_doadores)
						 paciente lista_geral[], 	// Vetor com pacientes ja cadastrados
					     paciente lista_doadores[],	// Vetor preenchido com pacientes doadores
					     size_t tam_geral,			// Tamanho do vetor/cadastro a ser percorrido/analisado
					     size_t max_doadores) {		// Numero maximo de pacientes que podem ser armazenados no segundo vetor
	size_t indEntrada = 0, indSaida = 0;
	while (indEntrada < tam_geral) {
		if (lista_geral[indEntrada].doador &&
			strcmp(lista_geral[indEntrada].sangue, "O") == 0) {
			lista_doadores[indSaida] = lista_geral[indEntrada];		// copia campo a campo
			++indSaida;
		}
		++indEntrada;
	}
	return indSaida;	// O indice foi atualizado com o numero de copias que foram feitas
}
