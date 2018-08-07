#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "registro.h"
#include "fila_reg.h"

#define REGS 50

void ordena(Registro [*], size_t);
// void ordena(Registro [*], int, int);

int main(void) {
    srand((unsigned) time(NULL));

    // Conjunto de registro ("base de dados") eh representado por um vetor
    Registro a[REGS];

    puts("Chaves geradas para o conjunto de registros:");
    int i;
    for (i=0; i<REGS; ++i) {
        bool primaria;
        do {
            a[i].chave = rand() % 500 + 1;
            primaria = true;
            int j = i-1;
            while (j >= 0) {
                if (a[j].chave == a[i].chave) { // se estah repetindo uma chave anterior...
                    primaria = false;
                    break;  // ... para de comparar e...
                }
                --j;
            }
        } while (primaria == false);    // ... volta pra gerar um outro valor
        printf("%u ", a[i].chave);
    }
    putchar('\n');

    ordena(a, REGS);
    // ordena(a, 0, REGS-1);

    puts("Chaves ordenadas:");
    for (i=0; i<REGS; ++i) {
        printf("%u ", a[i].chave);
    }
    putchar('\n');

    return EXIT_SUCCESS;
}

#if 1
void ordena(Registro vetor[], size_t tamanho) {
    /** Bolha
    // Eh necessario executar um numero de varreduras de comparacao igual ao
    // tamanho do vetor para garantir que todas as chaves foram deslocadas para
    // suas respectivas posicoes ordenadas
    int n;
    for (n=1; n<=tamanho; ++n) {
        // Em cada varredura/passagem pelo vetor, pega duas posicoes e compara entre si
        // Faz isso para todos os pares de posicoes, comecando do fim ("fundo") do vetor
        int m;
        for (m=tamanho-1; m>0; --m) {
            if (vetor[m].chave < vetor[m-1].chave) { // chaves estao em posicoes trocadas no par?
                // A contiguidade fisica define que TODO o registro se movimenta
                // com a chave
                Registro temp;
                memcpy(&temp, &vetor[m], sizeof(Registro));
                memcpy(&vetor[m], &vetor[m-1], sizeof(Registro));
                memcpy(&vetor[m-1], &temp, sizeof(Registro));
            }
        }
    }
    ** Fim do bolha */

    /** Selecao direta
    int inicio = 0;
    while (inicio < tamanho) {
        int menor = inicio; // comeco a procura pelo menor de onde eu estou...
        int i;
        for (i=inicio; i<tamanho; ++i) {
            if (vetor[i].chave < vetor[menor].chave) {
                menor = i;
            }
        }
        Registro temp;
        memcpy(&temp, &vetor[inicio], sizeof(Registro));
        memcpy(&vetor[inicio], &vetor[menor], sizeof(Registro));
        memcpy(&vetor[menor], &temp, sizeof(Registro));
        ++inicio;   // continua o processo para o segmento restante do vetor
    }
    ** Fim do selecao direta */

    /** Insercao direta
    int fronteira = 1;  // primeiro indice da parte nao ordenada por insercao
    while (fronteira < tamanho) {
        Registro temp;
        memcpy(&temp, &vetor[fronteira], sizeof(Registro));
        int i;
        for (i=fronteira-1; i>=0; --i) {
            if (vetor[i].chave > temp.chave) {
                memcpy(&vetor[i+1], &vetor[i], sizeof(Registro));
            }
            else {
                break;  // encontrei alguem menor do que eu, nao posso desloca-lo
            }
        }
        // A outra hipotese pra ter chego aqui eh i < 0
        // Em ambos os casos, vou trazer o valor para a posicao aberta para ele
        memcpy(&vetor[i+1], &temp, sizeof(Registro));

        ++fronteira;    // vai buscar novo valor para inserir na parte inicial do vetor
    }
    ** Fim do insercao direta */

    /** Shell ("shellsort")
    int salto = 1;
    while (salto <= tamanho) {  // calcula incremento de referencia (> tamanho)
        salto = 3 * salto + 1;
    }
    // volta para incremento anterior ao anterior
    int j = 2;
    while (j > 0 && salto > 1) {
        salto = (salto - 1) / 3;    // operacao inversa para voltar ao incremento anterior
        --j;
    }
    while (salto >= 1) {
        // Repete para todos os segmentos separados pelos saltos
        int seg;
        for (seg=0; seg<salto; ++seg) {
            // *** Algoritmo de selecao direta adaptado para saltos... ***
            int inicio = seg;   // comeca o algoritmo pelo indice inicial do SEGMENTO em questao
            while (inicio < tamanho) {
                int menor = inicio; // comeco a procura pelo menor de onde eu estou no SEGMENTO
                int i;
                for (i=inicio; i<tamanho; i+=salto) {
                    if (vetor[i].chave < vetor[menor].chave) {
                        menor = i;
                    }
                }
                Registro temp;
                memcpy(&temp, &vetor[inicio], sizeof(Registro));
                memcpy(&vetor[inicio], &vetor[menor], sizeof(Registro));
                memcpy(&vetor[menor], &temp, sizeof(Registro));
                inicio += salto;    // continua do proximo elemento dentro do mesmo SEGMENTO
            }
        }
        salto = (salto - 1) / 3;    // repete para o incremento anterior na serie
    }
    ** Fim do shellsort */

    // Radixsort
    int maior_chave = vetor[0].chave;
    int i;
    for (i=0; i<tamanho; ++i) {
        if (vetor[i].chave > maior_chave) {
            maior_chave = vetor[i].chave;
        }
    }
    // Cria filas dos simbolos usados nas chaves
    Fila_reg* filas[10];
    int f;
    for (f=0; f<10; ++f) {
        filas[f] = cria();
    }
    // Numero de passos do algoritmo eh o numero de algarismos da maior chave
    int p, passos = log10(maior_chave) + 1;
    for (p=0; p<passos; ++p) {
        // Percorre o vetor, colocando cada registro na fila correspondente ao
        // algarismo da chave DA VEZ (unidade, dezena, centena, etc.)
        for (i=0; i<tamanho; ++i) {
            int numero = vetor[i].chave / pow(10, p);   // descarta os algarismos a direita do passo
            int digito = numero % 10;   // algarismo a ser considerado nesse passo
            enqueue(filas[digito], vetor+i);
        }
        // Uma vez que todos os registros foram parar nas respectivas filas, eh
        // hora de devolver ao vetor na ordem das filas
        i=0;
        for (f=0; f<10; ++f) {
            while (!underflow(filas[f])) {
                memcpy(&vetor[i++], dequeue(filas[f]), sizeof(Registro));
            }
        }
    }
    // Destroi as filas de apoio
    for (f=0; f<10; ++f) {
        destroi(filas[f]);
    }
}
#else
void ordena(Registro vetor[], int inferior, int superior) {
    /** Mergesort
    if (inferior >= superior) {
        return;
    }
    int meio = (inferior + superior) / 2;
    ordena(vetor, inferior, meio);
    ordena(vetor, meio+1, superior);

    int tamanho = superior - inferior + 1;
    Registro* auxiliar = (Registro*) malloc(sizeof(Registro)*tamanho); // para intercalacao
    int indice_aux = 0;         // indice da proxima posicao a ser escrita no auxiliar, vindo
                                // da comparacao entre dois elementos das metades
    int esquerdo = inferior,    // inicio da metade inferior
        direito = meio + 1;     // inicio da metade superior
    while (esquerdo <= meio && direito <= superior) {
        if (vetor[esquerdo].chave < vetor[direito].chave) {
            memcpy(&auxiliar[indice_aux], &vetor[esquerdo], sizeof(Registro));
            ++esquerdo;
        }
        else {
            memcpy(&auxiliar[indice_aux], &vetor[direito], sizeof(Registro));
            ++direito;
        }
        ++indice_aux;
    }
    while (esquerdo <= meio) {
        memcpy(&auxiliar[indice_aux++], &vetor[esquerdo++], sizeof(Registro));
    }
    while (direito <= superior) {
        memcpy(&auxiliar[indice_aux++], &vetor[direito++], sizeof(Registro));
    }
    memcpy(&vetor[inferior], auxiliar, sizeof(Registro)*tamanho);
    free(auxiliar);
    ** Fim do mergesort */

    // Quicksort
    if (inferior >= superior) {
        return;
    }
    int indice_pivo = (inferior + superior) / 2;
    int valor_pivo = vetor[indice_pivo].chave;  // valor de referencia para comparacoes
    int esquerdo = inferior, direito = superior;
    while (esquerdo <= direito) {
        while (vetor[esquerdo].chave < valor_pivo) ++esquerdo;
        while (vetor[direito].chave > valor_pivo) --direito;
        if (esquerdo <= direito) {
            Registro temp;
            memcpy(&temp, &vetor[esquerdo], sizeof(Registro));
            memcpy(&vetor[esquerdo], &vetor[direito], sizeof(Registro));
            memcpy(&vetor[direito], &temp, sizeof(Registro));
            ++esquerdo, --direito;
        }
    }
    ordena(vetor, inferior, direito);   // parte "de baixo" do vetor
    ordena(vetor, esquerdo, superior);  // parte "de cima"
}
#endif

/*
// Analise dos algoritmos

// BOLHA
void ordena(Registro vetor[], size_t tamanho) {                     // t = 0
    int n;                                                          // t = 0
    for (n=1; n<=tamanho; ++n) {                                    // t = A.n + B
        int m;                                                      // t = 0
        for (m=tamanho-1; m>0; --m) {                               // t = (C.n + D).n
            if (vetor[m].chave < vetor[m-1].chave) {                // t = E.n²
                Registro temp;                                      // t = 0
                memcpy(&temp, &vetor[m], sizeof(Registro));         // t = X.n²
                memcpy(&vetor[m], &vetor[m-1], sizeof(Registro));   // t = Y.n²
                memcpy(&vetor[m-1], &temp, sizeof(Registro));       // t = Z.n²
            }
        }
    }
}
T(n) = (C + E + X + Y + Z).n² + (A + D).n + B ==> O(n²)

// MERGESORT
void ordena(Registro vetor[], int inferior, int superior) {                     // t = 0
    if (inferior >= superior) {                                                 // t = A
        return;                                                                 // t = B
    }
    int meio = (inferior + superior) / 2;                                       // t = C
    ordena(vetor, inferior, meio);                                              // t = T(n/2) + D
    ordena(vetor, meio+1, superior);                                            // t = T(n/2) + E

    int tamanho = superior - inferior + 1;                                      // t = F
    Registro* auxiliar = (Registro*) malloc(sizeof(Registro)*tamanho);          // t = G
    int indice_aux = 0;                                                         // t = H
    int esquerdo = inferior, direito = meio + 1;                                // t = I
    while (esquerdo <= meio && direito <= superior) {                           // t = J.n/2
        if (vetor[esquerdo].chave < vetor[direito].chave) {                     // t = K.n/2
            memcpy(&auxiliar[indice_aux], &vetor[esquerdo], sizeof(Registro));  // nunca vai entrar no 'if'
            ++esquerdo;                                                         // porque no pior caso todos
        }                                                                       // os menores estarao do direito
        else {                                                                  // t = 0.n/2
            memcpy(&auxiliar[indice_aux], &vetor[direito], sizeof(Registro));   // t = L.n/2
            ++direito;                                                          // t = M.n/2
        }                                                                       // t = 0
        ++indice_aux;                                                           // t = N.n/2
    }                                                                           // t = 0
    while (esquerdo <= meio) {                                                  // t = O.n/2
        memcpy(&auxiliar[indice_aux++], &vetor[esquerdo++], sizeof(Registro));  // t = P.n/2
    }                                                                           // t = 0
    while (direito <= superior) {                                               // t = Q (uma comparacao)
        memcpy(&auxiliar[indice_aux++], &vetor[direito++], sizeof(Registro));   // foi feito no primeiro while
    }                                                                           // t = 0
    memcpy(&vetor[inferior], auxiliar, sizeof(Registro)*tamanho);               // t = R
    free(auxiliar);                                                             // t = S
}                                                                               // t = 0

T(n) = A + B, se n = 1
       2T(n/2) + (J + K + ... + O + P).n/2 + (A + C + D + ... + Q + R + S), se n > 1

Reescrevendo:
T(n) = X, se n = 1
       2T(n/2) + Y.n/2 + Z, se n > 2

Desenvolvimento no documento: Analise do mergesort.pdf...
*/
