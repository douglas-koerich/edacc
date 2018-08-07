/* Definicao de um tipo novo para representar a entidade "habitante" */
struct habitante {
    char sexo; // M ou F
    float altura;
    int idade;
    char cor_olhos; // A, V ou C
};
typedef struct habitante Habitante;

/*
typedef struct {
    char sexo; // M ou F
    float altura;
    int idade;
    char cor_olhos; // A, V ou C
} Habitante;
*/

#include <stdio.h>
#include <ctype.h>

#define NUM_HABITANTES  3

int main(int argc, char* argv[]) {
    int indice, contador, maior_idade, num_fem, num_cast, total_homens;
    float media;


    /* Variavel que contem a base de dados da pesquisa */
    Habitante base_dados[NUM_HABITANTES];

    /* Ponteiro que vai indicar/apontar para um dos elementos do vetor em certo
       instante */
    Habitante* pontHab;

    /* Banco de dados eh volatil, precisa que o usuario digite o seu conteudo */
    for (indice = 0; indice < NUM_HABITANTES; ++indice) {
        printf("\n=== DADOS DO HABITANTE %d ===\n", indice+1);

        /* Preenche os campos do habitante na posicao 'indice' do vetor */
        printf("Digite o sexo (M/F): ");
        scanf(" %c", &base_dados[indice].sexo);
        printf("Digite a altura, em metros: ");
        scanf("%f", &base_dados[indice].altura);
        printf("Digite a idade, em anos: ");
        scanf("%d", &base_dados[indice].idade);
        printf("Digite a cor dos olhos (A/V/C): ");
        scanf(" %c", &base_dados[indice].cor_olhos);
    }
    media = 0.0;
    total_homens = num_fem = num_cast = 0;

    for (contador = 0, pontHab = base_dados;
         contador < NUM_HABITANTES; ++contador, ++pontHab) {
        /* item (a) */
        if (toupper(pontHab->cor_olhos) == 'C' && pontHab->altura > 1.60) {
            ++num_cast;
            media += pontHab->idade;
        }
        /* item (b) */
        if (contador == 0) {
            maior_idade = pontHab->idade;
        }
        else if (pontHab->idade > maior_idade) {
            maior_idade = pontHab->idade;
        }
        /* item (c) */
        if (toupper(pontHab->sexo) == 'F' &&
            ((pontHab->idade >= 20 && pontHab->idade <= 45) ||
            (toupper(pontHab->cor_olhos) == 'V' && pontHab->altura < 1.70))) {
            ++num_fem;
        }
        /* item (d) */
        if (toupper(pontHab->sexo) == 'M') {
            ++total_homens;
        }
    }
    puts("\n=== RESULTADOS ===\n");
    printf("Item a = %f\n", media/num_cast);
    printf("Item b = %d\n", maior_idade);
    printf("Item c = %d\n", num_fem);
    printf("Item d = %f%%\n", total_homens*100.0/NUM_HABITANTES);

    return 0;
}
