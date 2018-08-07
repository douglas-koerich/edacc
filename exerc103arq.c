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

void realizaCenso(FILE* povo, FILE* pbin, int n) {
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

		fprintf(povo, "%d;%c;%.2f;%d\n", anonimo.idade, anonimo.sexo,
				anonimo.salario, anonimo.filhos);
		fwrite(&anonimo, sizeof(habitante), 1, pbin);
	}
	puts("Fim do censo!");
}

float calculaMedia(FILE* povo) {
	rewind(povo);	// Volta a fita!!!
	float media = 0.0, n = 0;
	while (!feof(povo)) {
		int idade_nao_usa, filhos_nao_usa;
		char sexo_nao_usa;
		float salario;
		if (fscanf(povo, "%d;%c;%f;%d\n", &idade_nao_usa, &sexo_nao_usa,
				   &salario, &filhos_nao_usa) == EOF) {
			if (ferror(povo)) {
				perror("Nao pude ler do arquivo");
				return 0;
			}
		}
		else {
			media += salario;
			++n;
		}
	}
	media /= n;
	return media;
}

int mulh3filhos500(FILE* povo) {
	rewind(povo);
	int muieh = 0;
	while (!feof(povo)) {
		habitante sujeito;
		if (fscanf(povo, "%d;%c;%f;%d\n", &sujeito.idade, &sujeito.sexo,
				   &sujeito.salario, &sujeito.filhos) == EOF) {
			if (ferror(povo)) {
				perror("Nao pude ler do arquivo");
				return 0;
			}
		}
		else {
			if (sujeito.sexo == 'F' && sujeito.filhos == 3 &&
				sujeito.salario < 500.0) {
				++muieh;
			}
		}
	}
	return muieh;
}

int main() {
	int n;
	printf("Quantos habitantes serao entrevistados? ");
	scanf("%d", &n);

	FILE* populacao = fopen("censo.txt", "w+t");
	if (populacao == NULL) {
		perror("Nao pude criar o arquivo-texto de censo");
		return -1;
	}
	FILE* popbin = fopen("censo.bin", "w+b");
	if (popbin == NULL) {
		perror("Nao pude criar o arquivo-binario de censo");
		return -1;
	}
	// Vamos chamar a funcao para preencher o arquivo que acabou de ser
	// criado
	realizaCenso(populacao, popbin, n);

	// Agora, vamos publicar as estatisticas do censo
	printf("Media dos salarios: %.2f\n", calculaMedia(populacao));
	printf("Numero de mulheres com 3 filhos e salario inf. 500: %d\n",
		   mulh3filhos500(populacao));

	// Posiciona o cursor de leitura no inicio do 2o. registro do arquivo
	// binario (isso eh possivel porque sabemos qual eh o tamanho do
	// registro)
	fseek(popbin, sizeof(habitante), SEEK_SET);
	habitante habbin;
	fread(&habbin, sizeof(habitante), 1, popbin);
	printf("Habitante: %d anos, sexo %s, R$%.2f, %d filhos\n",
		   habbin.idade, habbin.sexo=='M'? "masculino": "feminino",
		   habbin.salario, habbin.filhos);

	fclose(populacao);
	fclose(popbin);
	return 0;
}

