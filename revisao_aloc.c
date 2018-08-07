#include <stdlib.h>		// para malloc e free
#include <stdio.h>
#include <string.h>		// para strlen e strcmp
#include <ctype.h>		// para toupper
#include <stdio_ext.h>	// para __fpurge
#include "revisao.h"

int main() {
	paciente* banco_de_dados;	// Banco de dados alocado dinamicamente com o tamanho justo pedido pelo usuario
	paciente* banco_de_doadores;// Deve ter o mesmo tamanho para o caso de TODOS serem doadores

	size_t numero;
	printf("Quantos pacientes vai cadastrar? ");
	scanf("%u", &numero);

	// Alocacao dinamica dos vetores de acordo com o tamanho (em numero de elementos) solicitado
	// pelo usuario
	banco_de_dados = (paciente*) malloc(numero*sizeof(paciente)); // malloc conhece bytes, nao paciente
	banco_de_doadores = (paciente*) malloc(numero*sizeof(paciente));

	// Chama a funcao para preencher o cadastro
	cadastraPacientes(banco_de_dados, numero);	// passa o endereco inicial do "vetor"

	// Percorre o vetor/banco de dados para conferencia
	size_t indice;
	puts("LISTA GERAL:");
	paciente* paux;
	for (indice = 0, paux = banco_de_dados; indice < numero; ++indice, ++paux) {
		printf("%20s %c %2d %-3s %c\n",
			   (*paux).nome, paux->sexo, paux->idade, paux->sangue,
			   (paux->doador? 'S': 'N'));
	}

	// Chama a funcao para selecionar os doadores
	size_t doadores = selecionaDoadores(banco_de_dados, banco_de_doadores, numero, numero);

	// Percorre o vetor/banco de dados de doadores para conferencia
	puts("LISTA DE DOADORES:");
	for (indice = 0, paux = banco_de_doadores; indice < doadores; ++indice) {
		printf("%20s %c %2d %-3s %c\n",
			   (paux+indice)->nome, (paux+indice)->sexo, (paux+indice)->idade,
			   (paux+indice)->sangue, ((*(paux+indice)).doador? 'S': 'N'));
	}
	// Libera a area de memoria alocada
	free(banco_de_doadores);
	free(banco_de_dados);

	// PARA CASA: Como ficam as strings-nomes que eu aloquei durante o cadastro???

	return 0;
}

void cadastraPacientes(paciente* lista_pacientes,	// Inicio do "vetor" de pacientes que vai ser preenchido
					   size_t num) {				// Numero de posicoes para preencher
	size_t ind;
	for (ind = 0; ind < num; ++ind) {
		printf("Dados do paciente #%d\n", ind+1);

		char rascunho[1000];
		printf("Nome? ");
		__fpurge(stdin);	// Limpa o buffer do teclado (Linux-only)
		gets(rascunho);

		lista_pacientes[ind].nome = 	// <=> (*(lista_pacientes+ind)).nome
			malloc(sizeof(char)*(strlen(rascunho)+1));	// +1 para o terminador nulo da string-nome
		/*
		strcpy(lista_pacientes[ind].nome, rascunho);

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
		*/
		strcpy((lista_pacientes+ind)->nome, rascunho);	// se v eh do tipo struct*, entao (*v[ind]). <=> (v+ind)->

		do {
			printf("Sexo (M/F)? ");
			__fpurge(stdin);
			(lista_pacientes+ind)->sexo = toupper(getchar());
		} while ((lista_pacientes+ind)->sexo != 'M' && (lista_pacientes+ind)->sexo != 'F');

		printf("Idade? ");
		scanf("%d", &((lista_pacientes+ind)->idade));

		printf("Tipo sanguineo (A/B/O/AB)? ");
		__fpurge(stdin);
		gets((lista_pacientes+ind)->sangue);

		char opcao;
		do {
			printf("Doador de orgaos (S/N)? ");
			__fpurge(stdin);
			opcao = toupper(getchar());
		} while (opcao != 'S' && opcao != 'N');
		(lista_pacientes+ind)->doador = (opcao == 'S');	// armazena o resultado logico da comparacao
	}
}

size_t selecionaDoadores(	// Retorna o numero de pacientes copiados para o segundo vetor (<= max_doadores)
						 const paciente* lista_geral, 	// Vetor com pacientes ja cadastrados
					     paciente* lista_doadores,		// Vetor preenchido com pacientes doadores
					     size_t tam_geral,				// Tamanho do vetor/cadastro a ser percorrido/analisado
					     size_t max_doadores) {			// Numero maximo de pacientes que podem ser armazenados no segundo vetor
	size_t indEntrada = 0, indSaida = 0;
	while (indEntrada < tam_geral) {
		if (lista_geral->doador &&	// <=> (*lista_geral).doador
			strcmp(lista_geral->sangue, "O") == 0) {
			*lista_doadores = *lista_geral;		// copia campo a campo, a partir do endereco em cada "lista"
			++indSaida, ++lista_doadores;	// lista_doadores passa a ter o endereco do PROXIMO elemento na memoria
		}
		++indEntrada, ++lista_geral;
	}
	return indSaida;	// O indice foi atualizado com o numero de copias que foram feitas
}

