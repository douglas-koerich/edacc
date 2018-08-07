#include <stdlib.h>
#include <stdio.h>

int mult_ite(int, int);
int mult_rec(int, int);

int main(int argc, char* argv[]) {
    if (argc < 3) {
        puts("Numero invalido de argumentos");
        return EXIT_FAILURE;
    }
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    printf("A multiplicacao iterativa de %d por %d resulta %d\n",
           x, y, mult_ite(x, y));
    printf("A multiplicacao recursiva de %d por %d resulta %d\n",
           x, y, mult_rec(x, y));

    return EXIT_SUCCESS;
}

int mult_ite(int x, int y) {
    int p, i;
    for (p=0, i=1; i<=y; ++i) {
        p += x;
    }
    return p;
}

int mult_rec(int x, int y) {
    int p;
    if (y == 1) {
        p = x;
    }
    else {
        p = x + mult_rec(x, y-1);
    }
    return p;
}

