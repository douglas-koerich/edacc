#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NUM 5

struct Demo {
    int i;
    char c;
    float f;
    int v[NUM];
};

int main(void) {
    struct Demo d = { 15, '?', 3.15 };
    int j;
    for (j=0; j<NUM; ++j) {
        d.v[j] = rand() % 100;
    }
    printf("Tamanho da estrutura na memoria: %ld\n", sizeof(d));
    printf("A estrutura na memoria estah armazenada no endereco %p\n", &d);

    struct Demo* p = &d;
    printf("A estrutura na memoria estah indicada pelo ponteiro p=%p\n", p);

    float* pf = &d.f;
    printf("O numero de ponto flutuante da estrutura estah no endereco %p\n", pf);

    *pf = -1.5F;    // Altera o float da estrutura em 'd' atraves do ponteiro direto
    (*p).f = 1.5F;  // Recupera o conteudo no endereco armazenado em 'p' (o registro)
                    // Tendo o conteudo recuperado, aplica o operador . sobre o registro
    p->f = -2.25F;  // Mais agradavel do que a expressao anterior

    int* pi = d.v; // int* pi = &d.v[0];    &v[0] = v
    for (j=0; j<NUM; ++j) {
        printf("Valor armazenado no indice %d do vetor: %d\n", j, *pi);
        ++pi;   // Lembrar que esse incremento "unitario" na verdade eh de um valor igual
                // ao tamanho do tipo (no caso, int) em bytes (no caso, 4)
    }

    // Alocacao dinamica de duas estruturas consecutivas (um vetor!) na memoria
    struct Demo* din = (struct Demo*) malloc(2 * sizeof(struct Demo));
    din->i = d.i;
    din->c = '#';
    din->f = log10(d.f);
    for (j=0; j<NUM; ++j) {
        din->v[j] = d.v[j];
    }
    // Passo para a estrutura seguinte
    // NAO FACA ++din, pois voce perdera o endereco retornado pelo malloc() e que
    // DEVE ser usado no free()
    (din+1)->i = 10;        // din[1].i = 10;
    (din+1)->c = '$';       // din[1].c = '$';
    (din+1)->f = abs(d.f);

    // Toda alocacao tem que ter a liberacao
    free(din);

    return EXIT_SUCCESS;
}
