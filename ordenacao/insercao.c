#include "ordenacao.h"

void ordena(R vetor[], size_t n) {
    int j;
    for (j = 1; j < n; ++j) { // percurso pelos numeros ainda nao ordenados
        int i;
        R copia;
        memcpy(&copia, vetor+j, sizeof(R));
        for (i = j-1; i >= 0 && vetor[i].chave > copia.chave; --i) {
            memcpy(vetor+i+1, vetor+i, sizeof(R)); // desloca o registro maior pra frente
        }
        memcpy(vetor+i+1, &copia, sizeof(R));
    }
}
