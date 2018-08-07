#include <stdlib.h>
#include <stdio.h>
#include <string.h> // memcpy
#include <time.h>   // clock
#include "registro.h"
#include "filareg.h"

#define REGISTROS 20

void imprime(R [*], size_t);
void troca(R*, R*);
void bolha(R [*], size_t);
void selecao(R [*], size_t);
void insercao(R [*], size_t);
void shell(R [*], size_t);
void radix(R [*], size_t);
void merge(R [*], int, int);
void quick(R [*], int, int);

int main() {
    FILE* tabela = fopen("/tmp/tabela.txt", "w");
    if (tabela == NULL) {
        perror("Erro ao criar o arquivo de tabela");
        return -1;
    }
    fputs("Tamanho;Bolha;Selecao;Insercao;Shell;Radix;Merge;Quick\n", tabela);
    int tamanho;
    for (tamanho=16; tamanho<=16*1024*1024; tamanho*=2) {
        fprintf(tabela, "%d;", tamanho);
        clock_t antes, depois;
        R* banco_dados = (R*) malloc(sizeof(R)*tamanho);
        R* backup = (R*) malloc(sizeof(R)*tamanho);
        int i, x;
        for (i=0, x=tamanho-1; i<tamanho; ++i, --x) {
            banco_dados[i].chave = x;
        }
        memcpy(backup, banco_dados, sizeof(R)*tamanho);

        if (tamanho <= 64*1024) {
            if (tamanho < 50) {
                // Imprime antes da ordenacao
                puts(">>>>>>>>>>>>>>>>>>>>>>>");
                imprime(banco_dados, tamanho);
            }
            // Executa o algoritmo de ordenacao
            printf("Ordenando %d elementos por bolha... ", tamanho); fflush(stdout);
            antes = clock();
            bolha(banco_dados, tamanho);
            depois = clock();
            fprintf(tabela, "%lld;", (long long) (depois-antes));
            puts("Feito!");
            if (tamanho < 50) {
                // Imprime o banco de dados ordenado
                imprime(banco_dados, tamanho);
                puts("<<<<<<<<<<<<<<<<<<<<<<<");
            }
            memcpy(banco_dados, backup, sizeof(R)*tamanho);
            if (tamanho < 50) {
                // Imprime antes da ordenacao
                puts(">>>>>>>>>>>>>>>>>>>>>>>");
                imprime(banco_dados, tamanho);
            }
            // Executa o algoritmo de ordenacao
            printf("Ordenando %d elementos por selecao... ", tamanho); fflush(stdout);
            antes = clock();
            selecao(banco_dados, tamanho);
            depois = clock();
            fprintf(tabela, "%lld;", (long long) (depois-antes));
            puts("Feito!");
            if (tamanho < 50) {
                // Imprime o banco de dados ordenado
                imprime(banco_dados, tamanho);
                puts("<<<<<<<<<<<<<<<<<<<<<<<");
            }
            memcpy(banco_dados, backup, sizeof(R)*tamanho);
            if (tamanho < 50) {
                // Imprime antes da ordenacao
                puts(">>>>>>>>>>>>>>>>>>>>>>>");
                imprime(banco_dados, tamanho);
            }
            // Executa o algoritmo de ordenacao
            printf("Ordenando %d elementos por insercao... ", tamanho); fflush(stdout);
            antes = clock();
            insercao(banco_dados, tamanho);
            depois = clock();
            fprintf(tabela, "%lld;", (long long) (depois-antes));
            puts("Feito!");
            if (tamanho < 50) {
                // Imprime o banco de dados ordenado
                imprime(banco_dados, tamanho);
                puts("<<<<<<<<<<<<<<<<<<<<<<<");
            }
            memcpy(banco_dados, backup, sizeof(R)*tamanho);
            if (tamanho < 50) {
                // Imprime antes da ordenacao
                puts(">>>>>>>>>>>>>>>>>>>>>>>");
                imprime(banco_dados, tamanho);
            }
            // Executa o algoritmo de ordenacao
            printf("Ordenando %d elementos por shell... ", tamanho); fflush(stdout);
            antes = clock();
            shell(banco_dados, tamanho);
            depois = clock();
            fprintf(tabela, "%lld;", (long long) (depois-antes));
            puts("Feito!");
            if (tamanho < 50) {
                // Imprime o banco de dados ordenado
                imprime(banco_dados, tamanho);
                puts("<<<<<<<<<<<<<<<<<<<<<<<");
            }
        }
        else {
            fprintf(tabela, "0;0;0;0;");
        }
        memcpy(banco_dados, backup, sizeof(R)*tamanho);
        if (tamanho < 50) {
            // Imprime antes da ordenacao
            puts(">>>>>>>>>>>>>>>>>>>>>>>");
            imprime(banco_dados, tamanho);
        }
        // Executa o algoritmo de ordenacao
        printf("Ordenando %d elementos por radix... ", tamanho); fflush(stdout);
        antes = clock();
        radix(banco_dados, tamanho);
        depois = clock();
        fprintf(tabela, "%lld;", (long long) (depois-antes));
        puts("Feito!");
        if (tamanho < 50) {
            // Imprime o banco de dados ordenado
            imprime(banco_dados, tamanho);
            puts("<<<<<<<<<<<<<<<<<<<<<<<");
        }
        memcpy(banco_dados, backup, sizeof(R)*tamanho);
        if (tamanho < 50) {
            // Imprime antes da ordenacao
            puts(">>>>>>>>>>>>>>>>>>>>>>>");
            imprime(banco_dados, tamanho);
        }
        // Executa o algoritmo de ordenacao
        printf("Ordenando %d elementos por merge... ", tamanho); fflush(stdout);
        antes = clock();
        merge(banco_dados, 0, tamanho-1);
        depois = clock();
        fprintf(tabela, "%lld;", (long long) (depois-antes));
        puts("Feito!");
        if (tamanho < 50) {
            // Imprime o banco de dados ordenado
            imprime(banco_dados, tamanho);
            puts("<<<<<<<<<<<<<<<<<<<<<<<");
        }
        memcpy(banco_dados, backup, sizeof(R)*tamanho);
        if (tamanho < 50) {
            // Imprime antes da ordenacao
            puts(">>>>>>>>>>>>>>>>>>>>>>>");
            imprime(banco_dados, tamanho);
        }
        // Executa o algoritmo de ordenacao
        printf("Ordenando %d elementos por quick... ", tamanho); fflush(stdout);
        antes = clock();
        quick(banco_dados, 0, tamanho-1);
        depois = clock();
        fprintf(tabela, "%lld\n", (long long) (depois-antes));
        puts("Feito!");
        if (tamanho < 50) {
            // Imprime o banco de dados ordenado
            imprime(banco_dados, tamanho);
            puts("<<<<<<<<<<<<<<<<<<<<<<<");
        }
        free(backup);
        free(banco_dados);
        fflush(tabela);
    }
    fclose(tabela);
    return 0;
}

void imprime(R v[], size_t t) {
    int i;
    for (i=0; i<t; ++i) {
        printf("%d ", v[i].chave);
    }
    putchar('\n');
}

void troca(R* r1, R* r2) {
    R temp;
    memcpy(&temp, r1, sizeof(R));
    memcpy(r1, r2, sizeof(R));
    memcpy(r2, &temp, sizeof(R));
}

void bolha(R v[], size_t t) {
    // Para o pior caso, precisa repetir a ordenacao
    // o numero de vezes igual ao comprimento do vetor
    int i;
    for (i=1; i<=t; ++i) {
        int j;
        for (j=t-1; j>0; --j) {
            if (v[j].chave < v[j-1].chave) {    // ordenacao crescente!
                troca(&v[j], &v[j-1]);
            }
        }
    }
}

void selecao(R v[], size_t t) {
    int i;
    for (i=0; i<t-1; ++i) {
        // Presumo que a menor chave estah no inicio da sequencia de
        // registros avaliados
        int indice_chave_menor = i;
        int j;
        for (j=i+1; j<t; ++j) {
            // Verifico se este registro tem uma chave ainda menor...
            if (v[j].chave < v[indice_chave_menor].chave) {
                // Em tendo uma chave menor, atualiza quem tem a menor!
                indice_chave_menor = j;
            }
        }
        // Ao fim do laco, a variavel contem o indice (posicao) do registro
        // com a menor chave, deve mover para o inicio da sequencia
        troca(&v[i], &v[indice_chave_menor]);
    }
}

void insercao(R v[], size_t t) {
    int j;  // indice do primeiro elemento nao-ordenado
    for (j=1; j<t; ++j) {
        R backup;
        memcpy(&backup, &v[j], sizeof(R));  // salva o elemento que sera inserido

        int i;  // indice do elemento ordenado
        for (i=j-1; i>=0; --i) {
            if (v[i].chave > backup.chave) {
                memcpy(&v[i+1], &v[i], sizeof(R));  // empurra para frente o registro
                                                    // com chave maior
            }
            else {
                break;  // encontrei um registro com chave menor ou
                        // com a mesma chave (como nao vou mexer nele, fica estavel)
            }
        }
        // O registro a ser inserido fica na posicao seguinte
        // ao ponto de parada (i=-1 ou i=indice do registro com chave menor ou igual)
        memcpy(&v[i+1], &backup, sizeof(R));
    }
}

void shell(R v[], size_t t) {
	// Cria a sequencia de incrementos (k's) cf. Shell
	int k[20], i, k_;
    for (i=0, k_=1;;k_=3*k_+1, ++i) {
        k[i] = k_;
        if (k[i] > t) {
            break;
        }
    }
	// Ao final do laco, o ultimo k[i] > n; esse eh o k_m.
    // Iniciamos usando como incremento o k_(m-2), portanto devemos voltar 'i'
    // em duas posicoes na serie de k's
	i -= 2;
	while (i >= 0) {	// enquanto tiver um incremento menor a ser usado
		k_ = k[i];	// incremento da vez

        int s;  // numero do segmento sendo ordenado
		for (s=1; s<=k_; ++s) { // numero total de segmentos = incremento
            // Para cada segmento ("sub-vetor"), faz a ordenacao dele pelo
            // algoritmo de insercao
            int j;  // indice do primeiro elemento nao-ordenado
			for (j=k_; j<t; j+=k_) {    // saltos nao sao unitarios, sao por k_
                R backup;
                memcpy(&backup, &v[j], sizeof(R));  // salva o elemento que sera inserido

                int i;  // indice do elemento ordenado
                        // (nao eh o mesmo i que indexa o vetor de incrementos!)
                for (i=j-k_; i>=0; i-=k_) { // saltos nao sao unitarios
                    if (v[i].chave > backup.chave) {
                        memcpy(&v[i+k_], &v[i], sizeof(R));  // empurra para frente o registro
                                                            // com chave maior
                    }
                    else {
                        break;  // encontrei um registro com chave menor ou
                                // com a mesma chave (como nao vou mexer nele, fica estavel)
                    }
                }
                // O registro a ser inserido fica na posicao seguinte
                // ao ponto de parada (i=-1 ou i=indice do registro com chave menor ou igual)
                memcpy(&v[i+k_], &backup, sizeof(R));
            }
            // Fim dos segmentos
        }
		// Usa o incremento anterior na serie (decrescente)
		--i;
	}
}

void radix(R v[], size_t t) {
    // Criamos 10 filas, uma para cada digito
    struct Fila* aux[10];
    int f;
    for (f=0; f<10; ++f) {
        aux[f] = criar();
    }
	// Como a chave eh um 'int' e esse valor tem, no maximo, 9 digitos
	// (max = 2 bilhoes e ...), vamos limitar a varredura de "casas" decimais
	// no algoritmo
	const MAX_DIGITOS_CHAVE = 9;
	int dig, peso;
	for (dig = peso = 1 /* "casa" das unidades da chave */;
		 dig <= MAX_DIGITOS_CHAVE; ++dig, peso *= 10) {	// cada digito tem peso x 10
		// Varre todos os elementos do banco de dados/vetor, determinando o valor
		// do digito na posicao atual de interesse
		int i, digito;
		for (i=0; i<t; ++i) {
			digito = (v[i].chave / peso) % 10;	// extrai o digito

			// Armazena o registro na fila correspondente ao digito determinado
			enqueue(aux[digito], v+i);
		}
		// Agora que todos os registros foram separados por seus digitos nas filas
		// correspondentes, recupero fila por fila (desde a 0 ateh a 9) para o vetor
		for (i=f=0; f<10; ++f) {
			while (!underflow(aux[f])) {
				dequeue(aux[f], v+i);
				++i;
			}
		}
	}
    // Remove filas auxiliares da memoria
    for (f=0; f<10; ++f) {
        destruir(aux[f]);
    }
}

static void intercala(R v[], int inf, int meio, int sup) {
	// Onde vamos colocar os valores/registros ordenados temporariamente
	int tamanho = sup-inf+1;
	R* r = (R*) malloc(sizeof(R)*tamanho);

	// Indices de percurso nas 'metades'
	int rasc=0, esq=inf, dir=meio+1;

	// Enquanto as duas 'metades' ainda deve ser percorridas
	while (esq <= meio && dir <= sup) {
		if (v[esq].chave < v[dir].chave) {
			memcpy(r+rasc, v+esq, sizeof(R));
			++esq;
		}
		else {
			memcpy(r+rasc, v+dir, sizeof(R));
			++dir;
		}
		++rasc;
	}
	// Continua copiando para rascunho o restante da metade maior...
	while (esq <= meio) {
		memcpy(r+rasc, v+esq, sizeof(R));
		++esq, ++rasc;
	}
	while (dir <= sup) {
		memcpy(r+rasc, v+dir, sizeof(R));
		++dir, ++rasc;
	}
	// Retorna para o vetor original o conteudo ordenado presente no rascunho
	memcpy(v+inf, r, sizeof(R)*tamanho);
	free(r);
}

void merge(R v[], int inf, int sup) {
	if (inf < sup) {
		int meio = (inf+sup)/2;
		merge(v, inf, meio);
		merge(v, meio+1, sup);
		intercala(v, inf, meio, sup);
	}
}

void quick(R v[], int inf, int sup) {
	if (inf < sup) {
		int pivo = v[(inf+sup)/2].chave;
		int esq = inf, dir = sup;
		while (esq <= dir) {
			while (v[esq].chave < pivo) ++esq;
			while (v[dir].chave > pivo) --dir;
			if (esq <= dir) {
				troca(v+esq, v+dir);
				++esq, --dir;
			}
		}
		quick(v, inf, dir);
		quick(v, esq, sup);
	}
}

