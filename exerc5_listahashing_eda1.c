#include <stdlib.h>

/* Escreva as funções de inserção, remoção e busca de uma chave numérica em uma tabela hashing com tratamento de colisões pelo método do encadeamento exterior (lista encadeada). */

/*
 * O tipo de registro a ser armazenado na tabela hashing
 */
typedef struct Reg {
	int chave;
} Reg;

/*
 * TAD: Tabela hashing com encadeamento externo
 */

// No encadeamento externo, cada registro/chave eh armazenado em um noh da
// lista encadeada de chaves "sinonimas" (com mesmo hash)
typedef struct NoChave {
	Reg* registro;
	struct NoChave* proximo;
} NoChave;

// Cada entrada da tabela hashing (ou seja, cada elemento do vetor - v.
// abaixo) eh um noh cabecalho da lista encadeada acima
typedef struct NoCabecalho {
	NoChave* cabeca;
	unsigned chavesSinonimas;
} NoCabecalho;

#define TAMANHO_TABELA	1024
#define QUOCIENTE		1031

// A estrutura da tabela hashing: um vetor de nos cabecalhos como definido
// acima
typedef struct TabelaHashing {
	NoCabecalho* vetor;
	size_t tamanho;
} TabelaHashing;

// As operacoes da tabela hashing:
// A funcao de hashing, usada para encontrar a posicao do vetor a qual
// corresponde uma chave
int h(int, size_t);

// Outras funcoes para usar a tabela como armazenamento de registros
void h_criar(TabelaHashing*, size_t);
void h_destruir(TabelaHashing*);
Reg* h_buscar(const TabelaHashing*, int);
int h_inserir(TabelaHashing*, Reg*);
int h_remover(TabelaHashing*, Reg**, int);

/*
 * Fim da definicao do TAD: Tabela hashing
 */

int h(int chave, size_t tamanho) {
	const unsigned quociente = QUOCIENTE;	// Na pratica, procuraria pelo
											// 1o. primo > tamanho
	int pos = chave;

	do {
		pos %= QUOCIENTE;	// Metodo da divisao (ou resto)
	} while (pos >= tamanho);

	return pos;
}

void h_criar(TabelaHashing* tab, size_t tamanho) {
	size_t i = 0;
	if (!tab) {
		return;
	}
	if (tab->vetor) {
		h_destruir(tab);
	}
	tab->tamanho = tamanho;
	tab->vetor = (NoCabecalho*) malloc(sizeof(NoCabecalho)*tamanho);
	while (i < tamanho) {
		(tab->vetor+i)->cabeca = NULL;	// listas encadeadas vazias
		(tab->vetor+i)->chavesSinonimas = 0;
		++i;
	}
}

void h_destruir(TabelaHashing* tab) {
	size_t i = 0;
	if (!tab || !tab->vetor) {
		return;
	}
	while (i < tab->tamanho) {
		while ((tab->vetor+i)->cabeca) { // enquanto houver registros...
			NoChave* noh = (tab->vetor+i)->cabeca;
			(tab->vetor+i)->cabeca = noh->proximo;
			free(noh);
		}
		++i;
	}
	free(tab->vetor);
	tab->tamanho = 0;
}

Reg* h_buscar(const TabelaHashing* tab, int chaveBusca) {
	int hash;
	NoCabecalho* pos;
	NoChave* noh;
	if (!tab || !tab->vetor) {
		return NULL;
	}
	hash = h(chaveBusca, tab->tamanho);
	pos = tab->vetor + hash;
	noh = pos->cabeca;
	while (noh) {
		if (noh->registro->chave == chaveBusca) {
			return noh->registro;
		}
		noh = noh->proximo;
	}
	return NULL;
}

int h_inserir(TabelaHashing* tab, Reg* novo) {
	int hash;
	NoCabecalho* pos;
	NoChave* noh, ** ref;
	if (!tab || !tab->vetor) {
		return 0;
	}
	hash = h(novo->chave, tab->tamanho);
	pos = tab->vetor + hash;
	noh = pos->cabeca;
	ref = &pos->cabeca;
	while (noh) {
		if (noh->registro->chave == novo->chave) {
			noh->registro = novo;
			return 1;
		}
		ref = &noh->proximo;
		noh = noh->proximo;
	}
	noh = (NoChave*) malloc(sizeof(NoChave));
	if (!noh) {
		return 0;
	}
	noh->registro = novo;
	noh->proximo = NULL;
	*ref = noh;
	++pos->chavesSinonimas;
	return 1;
}

int h_remover(TabelaHashing* tab, Reg** rem, int chaveRemover) {
	int hash;
	NoCabecalho* pos;
	NoChave* noh, ** ref;
	if (!tab || !tab->vetor) {
		*rem = NULL;
		return 0;
	}
	hash = h(chaveRemover, tab->tamanho);
	pos = tab->vetor + hash;
	noh = pos->cabeca;
	ref = &pos->cabeca;
	while (noh) {
		if (noh->registro->chave == chaveRemover) {
			*rem = noh->registro;
			*ref = noh->proximo;
			free(noh);
			--pos->chavesSinonimas;
			return 1;
		}
		ref = &noh->proximo;
		noh = noh->proximo;
	}
	*rem = NULL;
	return 0;
}

