/*
Foi encomendado um programa para o censo dos habitantes de uma localidade. Serão coletados os seguintes dados: idade, sexo, salário e número de filhos. O programa principal deve pedir ao usuário o número de registros que serão informados. Faça uma função que leia esses dados em um vetor. Faça funções diferentes que recebam esse vetor, por parâmetro, e retornem a média de salário entre os habitantes, a menor e a maior idade do grupo e a quantidade de mulheres com três filhos que recebe até R$ 500,00.
*/

#include <stdlib.h>
#include <stdio.h>
#include "revisao.h"

int main(void) {
    size_t numero_registros;
    printf("Digite o tamanho da populacao pesquisada: ");
    scanf("%zd", &numero_registros);

    // Declaracao de um vetor estatico
    // pessoa populacao[numero_registros];

    // Alocacao dinamica do "vetor" em memoria
    pessoa* populacao = malloc(numero_registros * sizeof(pessoa));
    if (populacao == NULL) {
        perror("Erro de alocacao dinamica");
        return EXIT_FAILURE;
    }

    realiza_censo(populacao, numero_registros);

    float media_salario = calcula_media(populacao, numero_registros);
    printf("A media dos salarios consultados eh %.2f\n", media_salario);

    unsigned maior_idade, menor_idade;
    encontra_maior_menor(populacao, numero_registros, &maior_idade, &menor_idade);
    printf("A maior idade eh %u e a menor %u\n", maior_idade, menor_idade);

    unsigned mulheres = conta_mulheres_3filhos_500reais(populacao, numero_registros);
    printf("Numero de mulheres com 3 filhos e ganhando ateh 500 reais eh %u\n", mulheres);

    free(populacao);

    return EXIT_SUCCESS;
}

void realiza_censo(pessoa habitantes[], size_t num_pessoas) {
    int p;
    for (p = 0; p < num_pessoas; ++p) {
        printf("*** Cadastro da %da. pessoa ***\n", p+1);
        printf("Digite a idade: "); scanf("%u", &habitantes[p].idade);
        printf("Numero de filhos: "); scanf("%u", &habitantes[p].num_filhos);
        printf("Sexo (M/F): "); scanf(" %c", &habitantes[p].genero);
        printf("Salario: "); scanf("%f", &habitantes[p].salario);
    }
}

float calcula_media(const pessoa* lista_pessoas, size_t num_pessoas) {
    float media, soma_salarios = 0.0;
    int p;
    for (p = 0; p < num_pessoas; ++p) {
        soma_salarios += lista_pessoas[p].salario;
    }
    media = soma_salarios / num_pessoas;
    return media;
}

void encontra_maior_menor(const pessoa* lista, size_t num, unsigned* pmaior, unsigned* pmenor) {
    int p;
    for (p = 0; p < num; ++p) {
        if (p == 0) {
            *pmaior = *pmenor = lista[p].idade;
        } else {
            if (lista[p].idade > *pmaior) {
                *pmaior = lista[p].idade;
            }
            if (lista[p].idade < *pmenor) {
                *pmenor = lista[p].idade;
            }
        }
    }
}

unsigned conta_mulheres_3filhos_500reais(const struct habitante* p, size_t n) {
    unsigned contador = 0;
    int i;
    for (i = 0; i < n; ++i, ++p) {
        if ((p->genero == 'f' || p->genero == 'F') && p->num_filhos == 3 &&
            p->salario <= 500.0) {
            ++contador;
        }
    }
    return contador;
}