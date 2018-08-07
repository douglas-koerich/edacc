#include "algord.h"

void ordBolha(Registro_Exemplo vetor[], int n) {
    int v;
    for (v=0; v<n-1; ++v) {
        int i;
        for (i=n-1; i>v; --i) {
            if (vetor[i].chave_ordenacao < vetor[i-1].chave_ordenacao) {
                Registro_Exemplo aux = vetor[i];
                vetor[i] = vetor[i-1];
                vetor[i-1] = aux;
            }
        }
    }
}

void ordSelecao(Registro_Exemplo vetor[], int n) {
    int i;
    for (i=0; i<n-1; ++i) {
        Registro_Exemplo aux;
        int j, menor = i;
        for (j=i+1; j<n; ++j) {
            if (vetor[j].chave_ordenacao < vetor[menor].chave_ordenacao) {
                menor = j;
            }
        }
        aux = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = aux;
    }
}

void ordInsercao(Registro_Exemplo vetor[], int n) {
    int desord;
    for (desord=1; desord<n; ++desord) {
        int orden;
        Registro_Exemplo aux = vetor[desord];
        for (orden=desord-1; orden>=0 && aux.chave_ordenacao < vetor[orden].chave_ordenacao; --orden) {
             vetor[orden+1] = vetor[orden];
        }
        vetor[orden+1] = aux;
    }
}

