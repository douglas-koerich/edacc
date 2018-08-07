#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Arquivos de matrizes usados no teste
#define MATRIZ_A1 "./matriz_a1.csv"
#define MATRIZ_B1 "./matriz_b1.csv"
#define MATRIZ_A2 "./matriz_a2.csv"
#define MATRIZ_B2 "./matriz_b2.csv"

// Definicao opaca do TAD: matriz esparsa
typedef struct Esparsa Esparsa;

// Prototipos das operacoes do TAD
void imprimir(const Esparsa* A);
void ler(Esparsa* A, FILE* X);
// void inverter(Esparsa* I, const Esparsa* A); /* FORA DE ESCOPO */
void transpor(Esparsa* T, const Esparsa* A);
void somar(Esparsa* S, const Esparsa* A, const Esparsa* B);
void multiplicar(Esparsa* M, const Esparsa* A, const Esparsa* B);

#ifdef TESTE
void imprimir(const Esparsa* A) {}
void ler(Esparsa* A, FILE* X) {}
void transpor(Esparsa* T, const Esparsa* A) {}
void somar(Esparsa* S, const Esparsa* A, const Esparsa* B) {}
void multiplicar(Esparsa* M, const Esparsa* A, const Esparsa* B) {}

void imprimir2(const char* str, FILE* X) {
    puts(str);
    rewind(X);
    while (!feof(X)) {
        static const int TAM_LINHA = 1024;
        char linha[TAM_LINHA];
        if (fgets(linha, TAM_LINHA, X) == NULL) {
            if (ferror(X)) {
                perror("Erro ao ler conteudo do arquivo");
                exit(EXIT_FAILURE);
            }
        } else {
            static const char tokens[] = ";\r\n";
            char* proximo = strtok(linha, tokens);
            while (proximo != NULL) {
                printf("%8s ", proximo);
                proximo = strtok(NULL, tokens);
            }
            putchar('\n');
        }
    }
    rewind(X);
    putchar('\n');
}
#else
void imprimir2(const char* str, FILE* X) {}
#endif

FILE* abrir(const char* nome) {
    FILE* X = fopen(nome, "rb");
    if (X == NULL) {
        char msg[128] = "Falha na abertura do arquivo ";
        strcat(msg, nome);
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return X;
}

int main(int argc, char* argv[]) {
    // Testes de leitura a partir de arquivo e impressao do TAD
    FILE* X = abrir(MATRIZ_A1);
    imprimir2(MATRIZ_A1, X);

    Esparsa* A1;
    ler(A1, X);
    fclose(X);
    imprimir(A1);
    putchar('\n');

    X = abrir(MATRIZ_B1);
    imprimir2(MATRIZ_B1, X);

    Esparsa* B1;
    ler(B1, X);
    fclose(X);
    imprimir(B1);
    putchar('\n');

    // Testes de transposicao
    Esparsa* T1;
    transpor(T1, A1);
    puts("TRANSPOSTA DE A1:");
    imprimir(T1);
    putchar('\n');

    Esparsa* T2;
    transpor(T2, B1);
    puts("TRANSPOSTA DE B1:");
    imprimir(T2);
    putchar('\n');

    // Testes de soma
    X = abrir(MATRIZ_A2);
    imprimir2(MATRIZ_A2, X);

    Esparsa* A2;
    ler(A2, X);
    fclose(X);
    imprimir(A2);
    putchar('\n');

    Esparsa* S1;
    somar(S1, A1, A2);
    puts("A1 + A2:");
    imprimir(S1);
    putchar('\n');

    X = abrir(MATRIZ_B2);
    imprimir2(MATRIZ_B2, X);

    Esparsa* B2;
    ler(B2, X);
    fclose(X);
    imprimir(B2);
    putchar('\n');

    Esparsa* S2;
    somar(S2, B1, B2);
    puts("B1 + B2:");
    imprimir(S2);
    putchar('\n');

    // Testes de multiplicacao
    Esparsa* M1;
    multiplicar(M1, A1, B1);
    puts("A1 x B1:");
    imprimir(M1);
    putchar('\n');

    Esparsa* M2;
    multiplicar(M2, A2, B2);
    puts("A2 x B2:");
    imprimir(M2);
    putchar('\n');

    return EXIT_SUCCESS;
}

