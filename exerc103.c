#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <ctype.h>

// Definicao da estrutura que modela (tipifica) um habitante
struct habitante {
	int idade;
	char sexo;
	float salario;
	int filhos;
};	// lembrar de terminar a definicao da struct com ponto-e-virgula!

// Para facilitar a digitacao excluindo a palavra 'struct' da frente,
// vamos dar para a estrutura acima um "apelido"
typedef struct habitante habitante;	// pode ser o mesmo nome

/* OBS: Estas variaveis NAO FAZEM PARTE DO EXERCICIO, aproveitamos para
 * exemplificar a inicializacao de estruturas
// Exemplo de inicializacao de alguns registros (variaveis) globais
struct habitante o_cara = { 69, 'M', 150.00, 3 };
habitante populacao_timbuctu[2] = {
	{ 46, 'M', 900.00, 0 },
	{ 39, 'F', 0.00, 2 }
};
*/

void realizaCenso(habitante* povo, int n) {
	int h;
	puts("Iniciando censo da populacao...");
	for (h=0; h<n; ++h) {
		// 1o. jeito: usamos uma variavel-registro auxiliar para ler os
		// dados de um habitante (depois copiamos esses dados para o vetor)
		habitante anonimo;
		do {
			printf("Digite a idade do %do. habitante: ", h+1);
			scanf("%d", &anonimo.idade);
		} while (anonimo.idade < 0 || anonimo.idade > 119);
		do {
			printf("Qual o sexo dele(a)? ");
			__fpurge(stdin);
			anonimo.sexo = toupper(getchar());
		} while (anonimo.sexo != 'M' && anonimo.sexo != 'F');
		do {
			printf("Quanto eh o seu salario (R$)? ");
			scanf("%f", &anonimo.salario);
		} while (anonimo.salario < 0.0 || anonimo.salario > 6000000.0);
		do {
			printf("Quantos filhos possui? ");
			scanf("%d", &anonimo.filhos);
		} while (anonimo.filhos < 0 && anonimo.filhos > 20);

		// 1a. forma de copiar da variavel temporaria para o elemento no
		// vetor: campo a campo
		povo[h].idade = anonimo.idade;
		povo[h].sexo = anonimo.sexo;
		povo[h].salario = anonimo.salario;
		povo[h].filhos = anonimo.filhos;

		// 2a. forma, valida quando nao ha strings nem ponteiros envolvidos:
		// nesse caso, existe uma copia binaria dos valores
		povo[h] = anonimo;

		// 3a. forma, usando a biblioteca-padrao
		// memcpy(&povo[h], &anonimo, sizeof(habitante));
		memcpy(povo+h, &anonimo, sizeof(habitante));
	}
	/* 2o. jeito: direto para o vetor atraves de um ponteiro que caminha
	 * com o indice...
	habitante* hab = povo;
	for (h=0; h<n; ++h, ++hab) {
		do {
			printf("Digite a idade do %do. habitante: ", h+1);
			scanf("%d", &hab->idade);
		} while (hab->idade < 0 || hab->idade > 119);
		do {
			printf("Qual o sexo dele(a)? ");
			__fpurge(stdin);
			hab->sexo = toupper(getchar());
		} while (hab->sexo != 'M' && hab->sexo != 'F');
		do {
			printf("Quanto eh o seu salario (R$)? ");
			scanf("%f", &hab->salario);
		} while (hab->salario < 0.0 || hab->salario > 6000000.0);
		do {
			printf("Quantos filhos possui? ");
			scanf("%d", &hab->filhos);
		} while (hab->filhos < 0 && hab->filhos > 20);
	}
	*/
	puts("Fim do censo!");
}

float calculaMedia(habitante povo[], int n) {
	float media = 0.0;
	int h;
	for (h=0; h<n; ++h) {
		media += povo[h].salario;
	}
	media /= n;
	return media;
}

// Como esta funcao precisa "retornar" dois valores, precisa ser atraves de
// ponteiro(s)
void encontraExtremos(habitante* povo, int n, int* menor, int* maior) {
	int h;
	for (h=0; h<n; ++h) {
		if (h == 0) {
			*maior = *menor = povo->idade;
		}
		else {
			if (*menor > (povo+h)->idade) {
				*menor = (povo+h)->idade;
			}
			if (*maior < (povo+h)->idade) {
				*maior = (povo+h)->idade;
			}
		}
	}
}

int mulh3filhos500(habitante* povo, int n) {
	int muieh = 0, h;
	for (h=0; h<n; ++h) {
		if (povo[h].sexo == 'F' && povo[h].filhos == 3 &&
			povo[h].salario < 500.0) {
			++muieh;
		}
	}
	return muieh;
}

int main() {
	int n;
	printf("Quantos habitantes serao entrevistados? ");
	scanf("%d", &n);

	// Vamos alocar dinamicamente o vetor da populacao a ser entrevistada
	habitante* populacao = (habitante*) malloc(n * sizeof(habitante));

	// Vamos chamar a funcao para preencher o vetor que acabou de ser
	// alocado
	realizaCenso(populacao, n);

	// Agora, vamos publicar as estatisticas do censo
	printf("Media dos salarios: %.2f\n", calculaMedia(populacao, n));
	int maior, menor;
	encontraExtremos(populacao, n, &menor, &maior);
	printf("Maior e menor idades: %d e %d\n", maior, menor);
	printf("Numero de mulheres com 3 filhos e salario inf. 500: %d\n",
		   mulh3filhos500(populacao, n));

	// Antes de encerrar o programa, nao podemos deixar lixo na memoria!
	free(populacao);

	return 0;
}

