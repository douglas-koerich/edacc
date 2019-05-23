#include <math.h>
#include "ordenacao.h"
#include "filaR.h"

void ordena(R vetor[], size_t n) {
    Fila* filas[10];
    int f;
    for (f = 0; f < 10; ++f) {
        filas[f] = cria(n);
    }
    int exp;
    for (exp = 0; exp < 10; ++exp) {
        int i;
        for (i = 0; i < n; ++i) {
            int digito = (vetor[i].chave / (int) pow(10, exp)) % 10;
            enqueue(filas[digito], vetor+i);
        }
        i = 0;
        for (f = 0; f < 10; ++f) {
            while (!underflow(filas[f])) {
                dequeue(filas[f], vetor+i);
                ++i;
            }
        }
    }
    for (f = 0; f < 10; ++f) {
        destroi(filas[f]);
    }
}
