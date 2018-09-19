#include <stdlib.h>
#include <stdio.h>

int fatorial(int);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    printf("%d\n", fatorial(n));
    return EXIT_SUCCESS;
}

#ifndef RECURSAO
int fatorial(int n) {
    int f, x;
    for (f=1, x=n; x>=1; --x) {
        f *= x;
    }
    return f;
}
#else
int fatorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * fatorial(n-1);
    }
}
#endif

