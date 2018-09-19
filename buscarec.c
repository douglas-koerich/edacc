#include <stdlib.h>
#include <stdio.h>

int* busca(int*, size_t, int);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    int x = atoi(argv[1]);
    int vetor[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    size_t n = sizeof(vetor)/sizeof(int);
    if (busca(vetor, n, x) == NULL) {
        puts("Valor nao encontrado!");
    } else {
        puts("Valor encontrado no vetor-exemplo");
    }
    return EXIT_SUCCESS;
}

#ifndef RECURSAO
int* busca(int* vetor, size_t n, int x) {
    int i;
    for (i=0; i<n; ++i) {
        if (*(vetor+i) == x) {
            return vetor+i;
        }
    }
    return NULL;
}
#else
int* busca(int* vetor, size_t n, int x) {
    if (n == 0) {
        return NULL;
    } else if (*vetor == x) {
        return vetor;
    } else {
        return busca(vetor+1, n-1, x);
    }
}
#endif

