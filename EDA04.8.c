#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int busca_maior(int*, int, int);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <tamanho do vetor>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t tamanho = atoi(argv[1]);
    int i, vetor[tamanho];

    srand(time(NULL));
    printf("Vetor gerado: ");
    for (i=0; i<tamanho; ++i) {
        vetor[i] = rand() % 100;
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    int maior = busca_maior(vetor, 0, tamanho-1);
    printf("O maior valor no conjunto eh %d\n", maior);

    return EXIT_SUCCESS;
}

int busca_maior(int* vetor, int indice_inferior, int indice_superior) {
    if (indice_inferior == indice_superior) {
        return vetor[indice_inferior]; // O maior eh o unico! :-)
    }
    int indice_meio = (indice_inferior + indice_superior) / 2;
    int maior_metade_inferior = busca_maior(vetor, indice_inferior, indice_meio);
    int maior_metade_superior = busca_maior(vetor, indice_meio+1, indice_superior);
    if (maior_metade_inferior > maior_metade_superior) {
        return maior_metade_inferior;
    } else {
        return maior_metade_superior;
    }
}

