#include <stdlib.h>
#include <stdio.h>

size_t maiores(int*, size_t, int); // prototipo das versoes: iterativa e recursiva-1
size_t maiores2(int*, int, int); // prototipo da versao recursiva-2

#define TAM_VETOR 5

int main(void) {
    int vetor[TAM_VETOR] = { 2, 11, 8, 4, 10 };
    //size_t m = maiores(vetor, TAM_VETOR, 6); // deve retornar 3 (maiores que 6)
    size_t m = maiores2(vetor, 0, TAM_VETOR-1); // passa indices das extremidades
                                                // (isto eh, toda a extensao do vetor)
    printf("%zd\n", m);
    return EXIT_SUCCESS;
}

