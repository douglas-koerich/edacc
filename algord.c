#include <string.h>	// memcpy()
#include "algord.h"
#include "filaR.h"	// fila auxiliar usada por radixsort()

// Uma funcao declarada como 'static' nao pode ser vista de outro arquivo-fonte
// (i.e. de outro *.c)
static void troca(Registro* r1, Registro* r2) {
	Registro aux;
	// Na contiguidade fisica TODO o registro eh copiado/movido junto com a chave
	memcpy(&aux, r1, sizeof(Registro));	// memcpy copia todos os bytes de r1
	memcpy(r1, r2, sizeof(Registro));
	memcpy(r2, &aux, sizeof(Registro));
}

void bubblesort(Registro banco_de_dados[], size_t tamanho) {
	int r, v;
	// Vamos ordenar de forma crescente
	// Um laco externo fara 'N' varreduras no vetor, onde 'N' eh o tamanho do mesmo
	for (v=1; v<=tamanho; ++v) {
		for (r=tamanho-1; r>0; --r) {	// varredura do vetor de tras para frente
										// (nao faz r=0 por causa do 'r-1' abaixo)
			if (banco_de_dados[r].chave < banco_de_dados[r-1].chave) {
				troca(&banco_de_dados[r], &banco_de_dados[r-1]);
			}
		}
	}
}

void selectsort(Registro banco_de_dados[], size_t tamanho) {
	int i;
	for (i=0; i<tamanho; ++i) {	// 'i' marca a posicao onde sera colocado o
								// menor elemento da vez
		int j, menor = i;	// 'menor': posicao do menor encontrado nesta varredura
		for (j=i+1; j<tamanho; ++j) {
			if (banco_de_dados[j].chave < banco_de_dados[menor].chave) {
				menor = j;
			}
		}
		// No fim desse laco, 'menor' tem a posicao que deve trocar com 'i'
		troca(banco_de_dados+i, banco_de_dados+menor);	// aritmetica de ponteiro
	}
}

void insertsort(Registro banco_de_dados[], size_t tamanho) {
	int fim_segmento_ordenados;
	for (fim_segmento_ordenados=0; fim_segmento_ordenados<tamanho-1;
		 ++fim_segmento_ordenados) {	// 'tamanho-1' pq vai verificar o proximo
		int inicio_segmento_nao_ordenados = fim_segmento_ordenados+1;

		// Salva o registro em outro lugar porque esta posicao sera ocupada pelo
		// deslocamento dos registros anteriores durante a insercao
		Registro backup_reg_nao_ordenado = banco_de_dados[inicio_segmento_nao_ordenados];
		int r;
		// Procura a posicao onde vai inserir o registro ainda nao ordenado
		for (r=fim_segmento_ordenados;	// comeca varredura pelo fim do segmento ordenado
			 r>=0 && banco_de_dados[r].chave > backup_reg_nao_ordenado.chave;
			 // pahra se chegou no extremo inicial do vetor OU se a chave dessa posicao eh menor do que a chave que se traz do segmento nao ordenado (salva no backup)
			 --r) {
			troca(banco_de_dados+r+1, banco_de_dados+r);
		}
		memcpy(banco_de_dados+r+1, &backup_reg_nao_ordenado, sizeof(Registro));
	}
}

void shellsort(Registro banco_de_dados[], size_t tamanho) {
	// Vamos usar a serie de Shell
	int serie[20], k = 1, i;
	for (i=0; i<20 && k < tamanho; ++i) {
		serie[i] = k;
		k = 3*k + 1;
	}
	// O primeiro k serah anterior ao ultimo gerado
	// Como i foi incrementado antes do teste, ele indica uma posicao ainda nao preenchida;
	// para obtermos o valor anterior ao ultimo (ou seja, o penultimo), temos que diminuir
	// i de 2 posicoes
	for (i-=2; i>=0; --i) {
		k = serie[i];

		// O numero de segmentos (e, portanto, de execucoes do algoritmo simples) eh
		// igual ao incremento
		int s;
		for (s=0; s<k; ++s) {
			// Vamos transportar o algoritmo de selecao direta para ca
			int i;
			for (i=s; i<tamanho; i+=k) {
				int j, menor = i;
				for (j=i+k; j<tamanho; j+=k) {
					if (banco_de_dados[j].chave < banco_de_dados[menor].chave) {
						menor = j;
					}
				}
				troca(banco_de_dados+i, banco_de_dados+menor);
			}
		}
	}
}

static void merge(Registro banco_de_dados[], int indInf, int indMeio, int indSup) {
	// Onde vamos colocar os valores/registros ordenados temporariamente
	int tamanho = indSup - indInf + 1;
	Registro* rascunho = (Registro*) malloc(sizeof(Registro)*tamanho);

	// Indices de percurso nas 'metades'
	int indRasc = 0, indEsq = indInf, indDir = indMeio+1;

	// Enquanto as duas 'metades' ainda deve ser percorridas
	while (indEsq <= indMeio && indDir <= indSup) {
		if (banco_de_dados[indEsq].chave < banco_de_dados[indDir].chave) {
			memcpy(rascunho+indRasc, banco_de_dados+indEsq, sizeof(Registro));
			++indEsq;
		}
		else {
			memcpy(rascunho+indRasc, banco_de_dados+indDir, sizeof(Registro));
			++indDir;
		}
		++indRasc;
	}
	// Continua copiando para rascunho o restante da metade maior...
	while (indEsq <= indMeio) {
		memcpy(rascunho+indRasc, banco_de_dados+indEsq, sizeof(Registro));
		++indEsq, ++indRasc;
	}
	while (indDir <= indSup) {
		memcpy(rascunho+indRasc, banco_de_dados+indDir, sizeof(Registro));
		++indDir, ++indRasc;
	}
	// Retorna para o vetor original o conteudo ordenado presente no rascunho
	memcpy(banco_de_dados+indInf, rascunho, sizeof(Registro)*tamanho);
	free(rascunho);
}

void mergesort(Registro banco_de_dados[], int indInf, int indSup) {
	if (indInf < indSup) {
		int indMeio = (indInf+indSup)/2;
		mergesort(banco_de_dados, indInf, indMeio);
		mergesort(banco_de_dados, indMeio+1, indSup);
		merge(banco_de_dados, indInf, indMeio, indSup);
	}
}

void quicksort(Registro banco_de_dados[], int indInf, int indSup) {
	if (indInf < indSup) {
		int pivo = banco_de_dados[(indInf+indSup)/2].chave;
		int indEsq = indInf, indDir = indSup;
		while (indEsq <= indDir) {
			while (banco_de_dados[indEsq].chave < pivo) ++indEsq;
			while (banco_de_dados[indDir].chave > pivo) --indDir;
			if (indEsq <= indDir) {
				troca(banco_de_dados+indEsq, banco_de_dados+indDir);
				++indEsq, --indDir;
			}
		}
		quicksort(banco_de_dados, indInf, indDir);
		quicksort(banco_de_dados, indEsq, indSup);
	}
}

void radixsort(Registro banco_de_dados[], size_t tamanho) {
	// Como a chave eh um 'int' e esse valor tem, no maximo, 9 digitos
	// (max = 2 bilhoes e ...), vamos limitar a varredura de "casas" decimais
	// no algoritmo
	const MAX_DIGITOS_CHAVE = 9;
	int dig, peso;
	for (dig = peso = 1 /* "casa" das unidades da chave */;
		 dig <= MAX_DIGITOS_CHAVE; ++dig, peso *= 10) {	// cada digito tem peso x 10
		// Criamos 10 filas, uma para cada digito
		struct Fila* aux[10];
		int f;
		for (f=0; f<10; ++f) {
			aux[f] = criar();
		}
		// Varre todos os elementos do banco de dados/vetor, determinando o valor
		// do digito na posicao atual de interesse
		int i, digito;
		for (i=0; i<tamanho; ++i) {
			digito = (banco_de_dados[i].chave / peso) % 10;	// extrai o digito

			// Armazena o registro na fila correspondente ao digito determinado
			enqueue(aux[digito], banco_de_dados+i);
		}
		// Agora que todos os registros foram separados por seus digitos nas filas
		// correspondentes, recupero fila por fila (desde a 0 ateh a 9) para o vetor
		for (i=f=0; f<10; ++f) {
			while (!underflow(aux[f])) {
				dequeue(aux[f], banco_de_dados+i);
				++i;
			}
		}
		// Remove filas auxiliares da memoria
		for (f=0; f<10; ++f) {
			destruir(aux[f]);
		}
	}
}

