#include "labhashing.h"

#define M	1031	/* Proximo num. primo acima do tamanho da tabela */

int hashSenha(const char* senha) {
	int i, posicao, soma = 0, len = strlen(senha);
	for (i=0; i<len; ++i) {
		soma += senha[i] << (i % 8);
	}
	/* Encontra uma posicao pelo metodo direto */
	posicao = soma % M;
	
	/* Como o resto da divisao por 1031 pode ser tambem 1000, 1001, ... 1030, */
	if (posicao >= TAM_TABELA) {
		posicao %= TAM_TABELA;	/* Reduz p/ encaixar no intervalo de 0 a 999 */
	}
	return posicao;	
}

int espalhaSequencial(Item* tabela, int posicaoOriginal) {
	int posicao = posicaoOriginal;
	
	/* Procura uma posicao livre ou liberada no vetor */
	while (tabela[posicao].estado == POSICAO_OCUPADA) {
		if (++posicao >= TAM_TABELA) {
			posicao = 0;
		}
		/* Se retornou a posicao original, o vetor esta cheio */
		if (posicao == posicaoOriginal) {
			return -1;
		}
	}
	return posicao;
}

int inserir(Item* tabela, const char* senha) {
	/* Determina a posicao original por meio da funcao de hashing */
	int posicao = hashSenha(senha);
	
	/* Usa a funcao de espalhamento para tratar quaisquer colisoes que houverem
	 * nessa posicao e nas seguintes */
	posicao = espalhaSequencial(tabela, posicao);
	
	/* Se uma posicao valida for retornada (qualquer posicao), insere o registro
	 * (a senha) nessa posicao */
	if (posicao >= 0) {
		tabela[posicao].estado = POSICAO_OCUPADA;
		strcpy(tabela[posicao].senha, senha);
		return 1;
	}
	return 0;
}

int buscar(Item* tabela, const char* senha) {
	/* A busca inicia (e, espera-se, ja termina) na posicao indicada pela funcao
	 * de hashing */
	int posicaoOriginal = hashSenha(senha), posicao = posicaoOriginal;
	
	/* Confere se a senha esta mesmo na posicao retornada; se nao estiver, vai
	 * iniciar uma busca pelas posicoes seguintes */
	do {
		switch (tabela[posicao].estado) {
			case POSICAO_LIVRE:
				/* Chegou ao fim da sequencia (agrupamento) de chaves */
				return -1;
				
			case POSICAO_OCUPADA:
				/* Verifica se a senha esta aqui */
				if (strcmp(tabela[posicao].senha, senha) == 0) {
					/* Achou! */
					return posicao;
				}
				/*** Nao tem 'break' aqui! ***/
				
			case POSICAO_LIBERADA:
			default:
				/* Deve continuar procurando na proxima posicao */
				if (++posicao >= TAM_TABELA) {
					posicao = 0;
				}
				break;
			}
		}
	}
	/* Repete ate que volte a mesma posicao original; nesse caso a senha nao es-
	 * ta na tabela */
	while (posicao != posicaoOriginal);
	
	/* Retorna uma posicao invalida, ja que nao encontrou a senha */
	return -1;
}
