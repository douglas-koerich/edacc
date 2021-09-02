#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

fila* junta_filas(fila*, fila*);

int main(void) {
    int primos[] = { 1, 2, 3, 5, 7, 9, 11, 13, 17, 19, 23, 29, -1 },
        fibonacci[] = { 1, 2, 3, 5, 8, 13, 21, -1 };

    const size_t TAMANHO_FILA = 50;
    fila* fp = create(TAMANHO_FILA),
        * ff = create(TAMANHO_FILA);

    int i = 0;
    while (primos[i] >= 0) {
        insert(fp, primos[i++]);
    }
    puts("Fila de primos:");
    print(fp);
    putchar('\n');

    i = 0;
    while (fibonacci[i] >= 0) {
        insert(ff, fibonacci[i++]);
    }
    puts("Fila de Fibonacci:");
    print(ff);
    putchar('\n');

    fila* fu = junta_filas(fp, ff);
    puts("Fila unica:");
    print(fu);
    putchar('\n');

    destroy(fp);
    destroy(ff);

    // Nao pode esquecer de destruir tambem a fila unificada
    destroy(fu);

    return EXIT_SUCCESS;
}

fila* junta_filas(fila* f1, fila* f2) {
    if (f1 == NULL || f2 == NULL) {
        return NULL;
    }
    fila *f3 = create(size(f1) + size(f2)),
         *aux1 = create(size(f1)),
         *aux2 = create(size(f2));

    while (!underflow(f1) && !underflow(f2)) {
        int n1 = inspect(f1), n2 = inspect(f2);
        if (n1 < n2) {
            insert(f3, n1);
            insert(aux1, extract(f1));

            // Mantem o elemento frontal da fila f2
            // para ser comparado com o proximo da fila f1
        } else {
            insert(f3, n2);
            insert(aux2, extract(f2));
        }
    }
    while (!underflow(f1)) {
        int n1 = extract(f1);
        insert(f3, n1); // pra terminar de juntar o que restou em f1
        insert(aux1, n1); // pra manter a mesma ordem em relacao aos
                          // outros que jah tinham sido tirados de f1        
    }
    while (!underflow(f2)) {
        int n2 = extract(f2);
        insert(f3, n2);
        insert(aux2, n2);
    }
    while (!underflow(aux1)) {
        insert(f1, extract(aux1));
    }
    destroy(aux1);
    while (!underflow(aux2)) {
        insert(f2, extract(aux2));
    }
    destroy(aux2);

    return f3;
}