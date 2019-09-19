#include <stdlib.h>
#include <stdio.h>
#include <time.h>

size_t maiores(int*, size_t, int); // prototipo das versoes: iterativa e recursiva-1
size_t maiores2(int*, int, int, int); // prototipo da versao recursiva-2

#define TAM_VETOR 15

int main(void) {
    int i, vetor[TAM_VETOR];
    for (i = 0; i < TAM_VETOR; ++i) {
        vetor[i] = rand() % 100; // vai gerar sempre a mesma sequencia (nao usamos srand)
        printf("%d ", vetor[i]);
    }
    putchar('\n');
    int num;
    do {
        printf("Digite um numero de referencia < 100: ");
        scanf("%d", &num);
    } while (num >= 100);
    
    // size_t m = maiores(vetor, TAM_VETOR, num);
    size_t m = maiores2(vetor, 0, TAM_VETOR-1, num); // passa indices das extremidades
                                                     // (isto eh, toda a extensao do vetor)
    printf("%zd\n", m);
    return EXIT_SUCCESS;
}

