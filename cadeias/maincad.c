#include <stdlib.h>
#include <stdio.h>
#include "cadeia.h"

// const char* T = "os testes testam estes alunos...";
const char* T = "estes alunos sao testados por este teste...";
const char* P = "teste";

int main(void) {
    
    printf("Forca bruta encontrou P em T na posicao %d.\n", forca_bruta(T, P));
    printf("Shitf-And encontrou P em T na posicao %d.\n", shift_and(T, P));
    printf("Boyer-Moore encontrou P em T na posicao %d.\n", boyer_moore(T, P));

    return EXIT_SUCCESS;
}

