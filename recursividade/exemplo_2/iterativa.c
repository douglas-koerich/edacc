#include <stdlib.h>

size_t maiores(int* vetor, size_t tamanho, int referencia) {
    int ind;
    size_t contador;
    for (ind = 0, contador = 0; ind < tamanho; ++ind) {
        if (vetor[ind] > referencia) {
            ++contador;
        }
    }
    return contador;
}
