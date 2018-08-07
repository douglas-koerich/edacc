#include <stdio.h>

#define NOME_ARQUIVO	"desenho.odg"

int main() {
	FILE* original = fopen(NOME_ARQUIVO, "rb");
	if (original == NULL) {
		// Quando voce poe duas CONSTANTES strings juntas ("coladas") o
		// compilador funde-as numa soh
		perror("Nao pude abrir o arquivo "NOME_ARQUIVO);
		return -1;
	}
	FILE* copia = fopen(NOME_ARQUIVO".copia", "wb");
	if (copia == NULL) {
		perror("Nao pude criar o arquivo de copia");

		// Vou deixar para o SO a tarefa de fechar os meus arquivos
		return -1;
	}
	// Como vou copiar byte a byte, posso usar as funcoes fgetc e fputc
	// mesmo se o byte nao for um ASCII
	while (!feof(original)) {
		// DEVO sempre definir o tipo de byte a ser lido/escrito no
		// arquivo BINARIO como unsigned char (para nao ter efeitos cola-
		// terais na interpretacao do bit de sinal)
		unsigned char byte = fgetc(original);
		if (byte == EOF) {
			if (ferror(original)) {
				perror("Nao pude ler do arquivo original "NOME_ARQUIVO);
				return -1;
			}
		}
		else {
			if (fputc(byte, copia) == EOF) {
				perror("Nao pude escrever no arquivo de copia");
				return -1;
			}
		}
	}
	fclose(copia);
	fclose(original);
	return 0;
}

