#include <stdlib.h>

size_t maiores(int* vetor, size_t tamanho, int referencia) {
    if (tamanho == 0) {
        return 0;
    }
    size_t contador = (*vetor > referencia)? 1: 0; // conta (ou nao) o valor dessa
                                                   // posicao no vetor onde estah
                                                   // a chamada recursiva
    contador += maiores(vetor + 1, tamanho - 1, referencia);
    return contador;
}

}
