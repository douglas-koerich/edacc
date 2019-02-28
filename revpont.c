#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct ponto3d {
    double x, y, z;
};
typedef struct ponto3d Ponto3D;

#define TAM 5

void muda_valores(char*, int*);
// void muda_vetor(int [*], size_t);
void muda_vetor(int*, size_t);
void imprime_ponto(const struct ponto3d*);
void monta_poligono(Ponto3D*, size_t);

int main(void) {
    char c = 'a';
    int i = 20;

    int vetor[TAM] = { -1, [2] = 3, 8, 5 }; // [1] fica 0
    struct ponto3d pto = {
        .x = 1.5,
        .z = -3.9
    }; // .y = 0.0;

    printf("Quantos pontos formam o poligono? ");
    size_t num_pontos;
    scanf("%zd", &num_pontos);
    // Ponto3D poligono[num_pontos];
    Ponto3D *poligono = malloc(num_pontos * sizeof(Ponto3D));

    char *pc = &c; // pc guarda o endereco (numerico) de c na memoria
    int *pi = &i; // idem para pi em relacao a i

    muda_valores(&c, &i);
    imprime_ponto(&pto);

    printf("c = %c, i = %d\n", *pc, *pi);

    muda_vetor(vetor, TAM);

    i = 0;
    pi = vetor; // pi = &vetor[0];
    printf("vetor = ");
    while (i < TAM) {
        // printf("%d ", vetor[i]); <=> printf("%d ", *(vetor + i));
        /*
        printf("%d ", *pi);
        ++pi; 
        */
        printf("%d ", *(pi + i)); // printf("%d ", pi[i]);
        ++i;
    }
    putchar('\n');

    monta_poligono(poligono, num_pontos);
    for (i=0; i<num_pontos; ++i) {
        imprime_ponto(&poligono[i]);
    }

    free(poligono);

    return EXIT_SUCCESS;
}

void muda_valores(char* a, int* b) {
    *a = 'z';
    *b = -1;
}

void muda_vetor(int* v, size_t t) {
    srand(time(NULL));
    int i;
    for (i=0; i<t; ++i) {
        *v = rand() % 10;
        ++v;
    }
}

void imprime_ponto(const struct ponto3d* p) {
    printf("Ponto = <%.1lf, %.1lf, %.1lf>\n",
           p->x, p->y, p->z);
}

void monta_poligono(Ponto3D* plg, size_t num) {
    srand(time(NULL));
    int i;
    for (i=0; i<num; ++i) {
        /* Poder-se-ia ateh fazer plg++ dentro deste laco, uma
         * vez que plg eh uma COPIA do ponteiro original poligono
         * que (ele, sim) tem a obrigacao de nao perder o endereco
         * retornado pelo malloc() */
        (plg + i)->x = ((double) (rand() % 1000)) / (rand() % 1000);
        (*(plg + i)).y = ((double) (rand() % 1000)) / (rand() % 1000);
        plg[i].z = ((double) (rand() % 1000)) / (rand() % 1000);
    }
}

