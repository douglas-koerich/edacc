#include <stdio.h>
#include "dicionario.h"

#define MEU_NUM_PALAVRAS	5
#define MEU_TAM_PALAVRA		10

int main() {
	// Crio um dicionario usando a interface do TAD
	struct Dicionario* dicionario = cria(MEU_NUM_PALAVRAS);
	if (dicionario == NULL) { // Retornou nulo, entao nao criou
		return -1;
	}
	// Pede todas as palavras esperadas via teclado
	int p;
	for (p = 1; p <= MEU_NUM_PALAVRAS; ++p) {
		char palavra[MEU_TAM_PALAVRA+1];
		printf("Digite uma nova palavra: ");
		scanf(" %s", palavra);

		// Se a palavra comeca com vogal, insere no inicio, senao
		// insere no fim
		char inicial = toupper(palavra[0]);
		bool inseriu;
		if (inicial == 'A' || inicial == 'E' || inicial == 'I' ||
			inicial == 'O' || inicial == 'U' || inicial == 'Y') {
			inseriu = insereInicio(dicionario, palavra);
		}
		else {
			inseriu = insereFim(dicionario, palavra);
		}
		if (!inseriu) {
			destroi(dicionario);
			return -1;
		}
	}
	// Imprime a lista para conferencia
	imprime(dicionario);

	// Remove uma palavra do inicio e outra do fim
	removeInicio(dicionario);
	removeFim(dicionario);

	// Imprime novamente para conferencia
	imprime(dicionario);

	// Destroi a lista para sair
	destroi(dicionario);

	return 0;
}

