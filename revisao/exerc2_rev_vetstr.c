#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "exerc2_rev_vetstr.h" // para "conhecer" 'habitante'

#define NUM_HABITANTES 20 // cf. enunciado

int main(void) {
    // "Banco de dados" da pesquisa
    habitante populacao[NUM_HABITANTES];

    // "Execucao da pesquisa"...
    int i;
    for (i=0; i<NUM_HABITANTES; ++i) {
        printf("Dados do %do. habitante:\n", i+1);
        printf("Salario > ");
        scanf("%f", &populacao[i].salario);
        printf("Idade > ");
        scanf("%u", &populacao[i].idade);
        printf("Numero de filhos > ");
        scanf("%u", &populacao[i].filhos);
        do {
            printf("Sexo > ");
            scanf(" %c", &populacao[i].sexo);

            // Converte pra maiuscula pra facilitar a comparacao depois...
            populacao[i].sexo = toupper(populacao[i].sexo);
        } while (populacao[i].sexo != 'F' && populacao[i].sexo != 'M');
    }

    // "Tratamento estatistico"...
    float media_salario = 0.0, maior_salario = populacao[0].salario;
    unsigned media_filhos = 0, num_mulheres = 0, num_mulheres_acima_1k = 0;
    for (i=0; i<NUM_HABITANTES; ++i) {
        media_salario += populacao[i].salario;
        if (populacao[i].salario > maior_salario) {
            maior_salario = populacao[i].salario;
        }
        media_filhos += populacao[i].filhos;
        if (populacao[i].sexo == 'F') {
            ++num_mulheres;
            if (populacao[i].salario > 1000.0) {
                ++num_mulheres_acima_1k;
            }
        }
    }
    media_salario = media_salario / NUM_HABITANTES; // divisao real
    media_filhos = (float) media_filhos / NUM_HABITANTES; // força divisao real!
    float perc_mulheres_acima_1k = num_mulheres_acima_1k * 100.0 / num_mulheres;

    // Apresentacao dos resultados
    printf("Maior salario: R$ %.2f\n", maior_salario);
    printf("Media salarial: R$ %.2f\n", media_salario);
    printf("Media de filhos: %u\n", media_filhos); // 1,9 filhos fica 1 (por quê?)
    printf("Percentual de mulheres que ganham acima de R$ 1k: %.1f%%\n",
           perc_mulheres_acima_1k);

    return EXIT_SUCCESS;
}

