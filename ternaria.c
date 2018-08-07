#include "registro.h"

int buscaTernaria(Registro banco_de_dados[], int chave_busca, int inf, int sup) {
	if (inf > sup) {
		return -1;
	}
	int terco_1 = (inf+sup)/3;
	int terco_2 = 2*(inf+sup)/3;

	if (banco_de_dados[terco_1].chave == chave_busca) {
		return terco_1;
	}
	if (banco_de_dados[terco_2].chave == chave_busca) {
		return terco_2;
	}
	if (banco_de_dados[terco_1].chave > chave_busca) {
		return buscaTernaria(banco_de_dados, chave_busca, inf, terco_1-1);
	}
	else if (banco_de_dados[terco_2].chave < chave_busca) {
		return buscaTernaria(banco_de_dados, chave_busca, terco_2+1, sup);
	}
	else {
		return buscaTernaria(banco_de_dados, chave_busca, terco_1+1, terco_2-1);
	}
}

