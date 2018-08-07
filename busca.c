#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "busca.h"

unsigned comparacoes;

bool igual(int x, int y) {
    ++comparacoes;
    return x == y;
}

void quick(Registro* base, int inf, int sup) {
    if (inf < sup) {
        int pivo = base[(inf+sup)/2].chave;
        int esq = inf, dir = sup;
        while (esq <= dir) {
            while (base[esq].chave < pivo) ++esq;
            while (base[dir].chave > pivo) --dir;
            if (esq <= dir) {
                Registro aux = base[esq];
                base[esq] = base[dir];
                base[dir] = aux;
                ++esq, --dir;
            }
        }
        quick(base, inf, dir);
        quick(base, esq, sup);
    }
}

Registro* busca_sequencial(Registro* base, size_t n, int chave) {
    int i = 0;
    Registro* r = base;
    while (i < n) {
        // if (r->chave == chave) {
        if (igual(r->chave, chave)) {
            return r;
        }
        ++i, ++r;
    }
    return NULL;
}

Registro* busca_binaria(Registro* base, int inf, int sup, int chave) {
    if (inf > sup) {
        return NULL;
    }
    int meio = (inf+sup)/2;
    // if (base[meio].chave == chave) {
    if (igual(base[meio].chave, chave)) {
        return base+meio;
    }
    if (base[meio].chave > chave) {
        return busca_binaria(base, inf, meio-1, chave);
    }
    else {
        return busca_binaria(base, meio+1, sup, chave);
    }
}

Registro* busca_interpolacao(Registro* base, int inf, int sup, int chave) {
    if (inf > sup) {
        return NULL;
    }
    int pos;
	if (inf == sup) {
		pos = inf;
	}
	else {
        int dif_chave = chave - base[inf].chave,
            dif_inf_sup = base[sup].chave - base[inf].chave;
        float dist_perc = (float) dif_chave/dif_inf_sup;
        if (dist_perc < 0.0 || dist_perc > 1.0) {
            return NULL;
        }
        int dist_pos = (sup - inf) * dist_perc;
        pos = inf + dist_pos;
	}
    // if (base[pos].chave == chave) {
    if (igual(base[pos].chave, chave)) {
        return base+pos;
    }
    if (base[pos].chave > chave) {
        return busca_interpolacao(base, inf, pos-1, chave);
    }
    else {
        return busca_interpolacao(base, pos+1, sup, chave);
    }
}

int main(void) {
    FILE* tabela = fopen("/tmp/uniforme.txt", "w");
    if (tabela == NULL) {
        perror("Erro ao criar o arquivo de tabela");
        return EXIT_FAILURE;
    }
    fputs("Tamanho;Sequencial;Binaria;Interpolacao\n", tabela);
    int tamanho16;
    for (tamanho16=1; tamanho16<=512; ++tamanho16) {
        int tamanho = tamanho16 * 16;
        fprintf(tabela, "%d;", tamanho);
        Registro* banco_dados = (Registro*) malloc(sizeof(Registro)*tamanho);
        int i, x;
        for (i=0; i<tamanho; ++i) {
            banco_dados[i].chave = i * 7;
        }
        comparacoes = 0;
        if (busca_sequencial(banco_dados, tamanho, banco_dados[tamanho*3/4].chave) == NULL) {
            printf("Erro inesperado na busca sequencial (tamanho=%d)!...\n", tamanho);
        }
        fprintf(tabela, "%d;", comparacoes);
        comparacoes = 0;
        if (busca_binaria(banco_dados, 0, tamanho-1, banco_dados[tamanho*3/4].chave) == NULL) {
            printf("Erro inesperado na busca binaria (tamanho=%d)!...\n", tamanho);
        }
        fprintf(tabela, "%d;", comparacoes);
        comparacoes = 0;
        if (busca_interpolacao(banco_dados, 0, tamanho-1, banco_dados[tamanho*3/4].chave) == NULL) {
            printf("Erro inesperado na busca por interpolacao (tamanho=%d)!...\n", tamanho);
        }
        fprintf(tabela, "%d\n", comparacoes);
        free(banco_dados);
        fflush(tabela);
    }
    fclose(tabela);
    srand((unsigned) time(0));
    tabela = fopen("/tmp/NAO_uniforme.txt", "w");
    if (tabela == NULL) {
        perror("Erro ao criar o arquivo de tabela");
        return EXIT_FAILURE;
    }
    fputs("Tamanho;Sequencial;Binaria;Interpolacao\n", tabela);
    for (tamanho16=1; tamanho16<=512; ++tamanho16) {
        int tamanho = tamanho16 * 16;
        fprintf(tabela, "%d;", tamanho);
        Registro* banco_dados = (Registro*) malloc(sizeof(Registro)*tamanho);
        int i, x;
        for (i=0; i<tamanho; ++i) {
            int r;
            do {
                r = rand() % 1000000;
            } while (r < 200000 || r > 800000 || (r > 300000 && r < 400000) || (r > 500000 && r < 600000));
            banco_dados[i].chave = r;
        }
        quick(banco_dados, 0, tamanho-1);
        comparacoes = 0;
        if (busca_sequencial(banco_dados, tamanho, banco_dados[tamanho*3/4].chave) == NULL) {
            printf("Erro inesperado na busca sequencial (tamanho=%d)!...\n", tamanho);
        }
        fprintf(tabela, "%d;", comparacoes);
        comparacoes = 0;
        if (busca_binaria(banco_dados, 0, tamanho-1, banco_dados[tamanho*3/4].chave) == NULL) {
            printf("Erro inesperado na busca binaria (tamanho=%d)!...\n", tamanho);
        }
        fprintf(tabela, "%d;", comparacoes);
        comparacoes = 0;
        if (busca_interpolacao(banco_dados, 0, tamanho-1, banco_dados[tamanho*3/4].chave) == NULL) {
            printf("Erro inesperado na busca por interpolacao (tamanho=%d)!...\n", tamanho);
        }
        fprintf(tabela, "%d\n", comparacoes);
        free(banco_dados);
        fflush(tabela);
    }
    fclose(tabela);
    return EXIT_SUCCESS;
}
