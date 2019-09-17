#include <stdio.h>
#include <stdlib.h>

int somatorio(int, int);

int main(void)
{
    printf("Digite o limite inferior da soma: ");
    int limite;
    scanf("%d", &limite);

    printf("Digite o numero de de termos do somatorio: ");
    int termos;
    scanf("%d", &termos);

    int s = somatorio(limite, termos);

    printf("A soma dos %d primeiros numeros maiores que %d eh %d.\n", termos,
           limite, s);

    return EXIT_SUCCESS;
}
