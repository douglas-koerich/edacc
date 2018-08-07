#include <stdlib.h> // funcoes de alocacao dinamica
#include <stdio.h>

struct exemplo {
    char c;
    int i;
    float f;
};
typedef struct exemplo exemplo;

void imprime_caractere(void* caractere) {
    char* ponteiro_char = caractere;
    printf("O char eh %c.\n", *ponteiro_char);
}

void imprime_inteiro(void* inteiro) {
    int* ponteiro_int = inteiro;
    printf("O int eh %d.\n", *ponteiro_int);
}

struct item_generico {
    void* coisa;                            // ponteiro generico
    void (*funcao_imprimir_coisa)(void*);   // ponteiro pra funcao do tipo 'void func(void*)'
};
typedef struct item_generico generico;

int main(void) {
    printf("Digite o numero de elementos que vai cadastrar: ");
    size_t num;
    scanf("%lu", &num);

    // Vetor de estruturas alocadas dinamicamente
    size_t tamanho_total_bytes = num * sizeof(exemplo);
    exemplo* ponteiro_vetor = malloc(tamanho_total_bytes);

    // Outro vetor de ponteiros genericos, com o mesmo numero de elementos
    generico* vetor_generico = malloc(num * sizeof(generico));

    // Preenche a primeira estrutura na memoria aqui mesmo
    ponteiro_vetor->c = 'A';
    ponteiro_vetor->i = 10;
    ponteiro_vetor->f = 10.0;

    // No primeiro item generico, guardo o endereco do caracter da primeira estrutura
    vetor_generico->coisa = &ponteiro_vetor->c; // (void*) = (char*)
    vetor_generico->funcao_imprimir_coisa = &imprime_caractere;

    // Pede ao usuario para preencher a proxima estrutura
    (ponteiro_vetor+1)->c = 'B';
    exemplo* ponteiro_aux = ponteiro_vetor; // ponteiro_aux tambem tem o endereco da PRIMEIRA estrutura
    ++ponteiro_aux; // soma ao endereco original (da PRIMEIRA) o numero de bytes do tamanho da estrutura
                    // (agora ponteiro_aux 'aponta' para a segunda estrutura na memoria alocada)
    ponteiro_aux->i = 20;   // agora na segunda estrutura (apos o ++ acima)!
    ponteiro_aux->f = 20.0;

    // No segundo item generico, vou guardar o endereco do inteiro da segunda estrutura
    (vetor_generico+1)->coisa = &ponteiro_aux->i; // (void*) = (int*)
    (vetor_generico+1)->funcao_imprimir_coisa = &imprime_inteiro;

    // Imprime as 'coisas' (parece C++! E nao eh que veio daqui o conceito de metodo da classe?!)
    vetor_generico->funcao_imprimir_coisa(vetor_generico->coisa);
    (vetor_generico+1)->funcao_imprimir_coisa((vetor_generico+1)->coisa);
    
    free(ponteiro_vetor);   // tem que usar o valor original que o malloc retornou
    free(vetor_generico);

    return EXIT_SUCCESS;
}
