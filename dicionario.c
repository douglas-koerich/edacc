#include <stdio.h>		// puts()
#include <string.h>		// strlen(), strcmp(), etc.
#include "dicionario.h"	// nome da estrutura e os prototipos

#define MAX_PALAVRAS	10
#define MAX_CARACTERES	20

// Definicao da estrutura (INVISIVEL para o usuario do TAD)
struct Dicionario {
	char listaLinear[MAX_PALAVRAS][MAX_CARACTERES+1];	// espaco para o \0
	size_t max;	// tamanho maximo definido pelo usuario ao chamar cria()
	size_t num; // numero de palavras atualmente armazenadas (num <= max)
};

// Implementacao de cada operacao da interface do TAD
struct Dicionario* cria(size_t max) {
	if (max > MAX_PALAVRAS) {	// verifica se o max desejado eh possivel para o TAD
		printf("Max = %u excede o limite do dicionario (%u).\n", max, MAX_PALAVRAS);
		return NULL;			// nao pode criar o dicionario, indica isso no retorno
	}
	static struct Dicionario dicionario;	// variavel local que nao eh destruida na saida de cria()
	dicionario.max = max;
	dicionario.num = 0;	// nao ha nenhuma palavra inicialmente
	return &dicionario;
}

void destroi(struct Dicionario* dic) {
	// Esta funcao soh reseta os contadores, ja que o dicionario foi criado estaticamente
	// na memoria (nao eh uma alocacao dinamica)
	if (dic == NULL) {
		puts("Ponteiro NULO!");
		return;
	}
	dic->max = dic->num = 0;
	return;
}

// Programacao ESTRUTURADA: NAO REPITA codigo que pode ser modularizado
// Uma funcao definida como 'static' soh eh visivel neste arquivo
static bool validaIns(const struct Dicionario* dic, const char* palavra) {
	if (dic == NULL || palavra == NULL) {
		puts("Ponteiro NULO!");
		return false;
	}
	if (dic->num == dic->max) {
		puts("Lista cheia!");
		return false;
	}
	if (strlen(palavra) > MAX_CARACTERES) {
		puts("Palavra muito grande!");
		return false;
	}
	return true;
}

bool insereInicio(struct Dicionario* dic, const char* palavra) {
	if (!validaIns(dic, palavra)) {
		return false;
	}
	// Tendo espaco na lista, acrescenta na primeira posicao
	// (Deve deslocar todos os demais um indice para frente)
	int i;
	for (i=dic->num-1; i>=0; --i) {
		strcpy(dic->listaLinear[i+1], dic->listaLinear[i]);
	}
	strcpy(dic->listaLinear[0], palavra);
	++dic->num;
	return true;
}

bool insereFim(struct Dicionario* dic, const char* palavra) {
	if (!validaIns(dic, palavra)) {
		return false;
	}
	// Tendo espaco na lista, acrescenta na ultima posicao
	// (A ultima palavra atualmente na lista estah no indice num-1, entao
	// a proxima posicao livre eh do indice num)
	strcpy(dic->listaLinear[dic->num++], palavra);	// ja incrementa o contador ao inserir
	return true;
}

bool insereOrdem(struct Dicionario* dic, const char* palavra) {
	if (!validaIns(dic, palavra)) {
		return false;
	}
	// Tendo espaco na lista, procura a primeira palavra que for "maior"
	// que a palavra que estah sendo adicionada a lista
	int i = 0;
	while (i<dic->num && strcmp(dic->listaLinear[i], palavra) <= 0) {
		++i;
	}
	// 'i' parou no indice cuja palavra eh maior; para colocar a nova
	// palavra aqui, devo deslocar os proximos para frente
	int j;
	for (j=dic->num-1; j>=i; --i) {	// compare com insereInicio
		strcpy(dic->listaLinear[j+1], dic->listaLinear[j]);
	}
	strcpy(dic->listaLinear[i], palavra);
	++dic->num;
	return true;
}

static validaRem(const struct Dicionario* dic) {
	if (dic == NULL) {
		puts("Ponteiro NULO!");
		return false;
	}
	if (dic->num == 0) {
		puts("Lista vazia!");
		return false;
	}
	return true;
}

bool removeInicio(struct Dicionario* dic) {
	if (!validaRem(dic)) {
		return false;
	}
	// O segundo elemento toma o lugar do primeiro, o terceiro do segundo
	// e assim por diante...
	int i;
	for (i=0; i<dic->num-1; ++i) {
		strcpy(dic->listaLinear[i], dic->listaLinear[i+1]);
	}
	--dic->num;
	return true;
}

bool removeFim(struct Dicionario* dic) {
	if (!validaRem(dic)) {
		return false;
	}
	--dic->num;	// Nao precisa apagar o elemento da memoria, ele apenas
				// torna-se "lixo" alem do fim da lista
	return true;
}

bool removePalavra(struct Dicionario* dic, const char* palavra) {
	if (palavra == NULL) {
		puts("Ponteiro NULO!");
		return false;
	}
	if (!validaRem(dic)) {
		return false;
	}
	int i;
	for (i=0; i<dic->num; ++i) {
		if (strcmp(dic->listaLinear[i], palavra) == 0) {
			// Achou a palavra
			break;
		}
	}
	if (i < dic->num) {
		while (i < dic->num-1) {
			strcpy(dic->listaLinear[i], dic->listaLinear[i+1]);
			++i;
		}
		--dic->num;
		return true;
	}
	return false;
}

bool busca(const struct Dicionario* dic, const char* palavra) {
	if (dic == NULL || palavra == NULL) {
		puts("Ponteiro NULO!");
		return false;
	}
	int i;
	for (i=0; i<dic->num; ++i) {
		if (strcmp(dic->listaLinear[i], palavra) == 0) {
			return true;
		}
	}
	return false;
}

void imprime(const struct Dicionario* dic) {
	if (dic == NULL) {
		return;
	}
	puts("*** CONTEUDO DO DICIONARIO ***");
	size_t n = 0;
	while (n < dic->num) {
		puts(dic->listaLinear[n++]);
	}
	puts("*** (Fim da lista) ***");
}

