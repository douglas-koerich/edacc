#include <stdlib.h>
#include <stdio.h>
#include "tad.h"

int main() {
    complexo *c, *d, *e;

    c = inicia(5, -3);  // 5 - 3i
    printf("c = "); imprime(c); putchar('\n');

    d = duplica(c);
    printf("d = "); imprime(d); putchar('\n');

    e = soma(c, d);
    printf("e = "); imprime(e); putchar('\n');

    conjugado(d);   // altera 'd' para seu valor conjugado
    printf("d = "); imprime(d); putchar('\n');

    libera(e);      // libera 'e' aqui pra que possa apontar para um novo retornado pela soma()
                    // (do contrario, a proxima linha substituiria o endereco antigo em 'e' por
                    //  um novo, "esquecendo-se" onde estava a variavel anterior tornando-a
                    //  impossivel de ser alcancada para chamar um free())

    e = soma(c, d);
    printf("e = "); imprime(e); putchar('\n');

    /*
    free(c);        // deixa a cargo do programa a liberacao do dado
                    // (perigoso e requer uma DOCUMENTACAO do TAD muito clara pro usuario!)
    */
    libera(c);
    libera(d);
    libera(e);

    return EXIT_SUCCESS;
}
