#include <stdlib.h>
#include <stdio.h>

#define NUM_ELEMENTOS 10

void imprime_vetor(float [*], size_t);
unsigned num_negativos(float [*], size_t);
float soma_positivos(float [*], size_t);

int main() {
    // Definicao da variavel-vetor (com inicializacao dos tres primeiros
    // elementos do conjunto e do sexto elemento; demais recebem 0)
    float var_vetor[NUM_ELEMENTOS] = { 0, 3, 7, [5] = 12 };

    // Imprime o vetor digitado:
    printf("Antes da digitacao: ");
    imprime_vetor(var_vetor, NUM_ELEMENTOS);

    // Preenchimento do vetor com valores:
    int pos;
    for (pos = 0; pos < NUM_ELEMENTOS; ++pos) {
        printf("Digite o elemento do indice/da posicao %d: ", pos);
        scanf("%f", &var_vetor[pos]);
    }

    // Imprime o vetor digitado:
    printf("Vetor digitado: ");
    imprime_vetor(var_vetor, NUM_ELEMENTOS);

    printf("Numero de elementos negativos: %u.\n", num_negativos(var_vetor, NUM_ELEMENTOS));
    printf("Soma dos positivos: %f.\n", soma_positivos(var_vetor, NUM_ELEMENTOS));

    return EXIT_SUCCESS;
}

void imprime_vetor(float vet[], size_t tam) {
    int pos;
    for (pos = 0; pos < tam; ++pos) {
        printf("%.1f ", vet[pos]);
    }
    putchar('\n');
}

unsigned num_negativos(float vet[], size_t tam) {
    unsigned contador = 0;
    int pos = 0;
    while (pos < tam) {
        if (vet[pos] < 0.0) {
            ++contador;
        }
        ++pos;
    }
    return contador;
}

float soma_positivos(float vet[], size_t tam) {
    float soma = 0.0;
    // Percurso no sentido inverso
    int pos;
    for (pos = tam-1; pos >= 0; --pos) {
        if (vet[pos] > 0.0) {
            soma += vet[pos];
        }
    }
    return soma;
}

