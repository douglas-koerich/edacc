#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct ponto {
    float x, y;
};
typedef struct ponto Ponto;

void funcao(int*);
// void maius(char [*]);
void maius(char*);
void espelho(const Ponto*); // prefira o uso de ponteiro para passar estruturas para funcoes

float perim_triang(const Ponto*); // recebe um "vetor" de pontos que formam o triangulo

int main(void) {
    int var;
    char word[50];
    Ponto pto = { 3.5, 4.5 };
    Ponto* triangulo = malloc(3 * sizeof(Ponto)); // aloca um "vetor" de tres pontos no "monte"

    float perimetro = perim_triang(triangulo);

    Ponto* pt = &pto;
    espelho(pt);
    
    printf("Digite um valor: ");
    scanf("%d", &var);

    printf("Digite uma palavra (sem espacos): ");
    scanf(" %s", word); // todo nome de vetor eh o "ponteiro" do seu inicio

    printf("O valor de var eh %d e a palavra eh %s.\n", var, word);

    maius(word);
    printf("A versao maiuscula da palavra eh %s.\n", word);
    
    int* pont; // endereco aleatorio presente aqui eh potencialmente perigoso
    pont = &var; // salva em 'pont' o ENDERECO (na memoria) da variavel 'var'
    printf("O endereco de var eh %p.\n", pont);

    printf("Digite um novo valor: ");
    scanf("%d", pont); // altera o valor de 'var' de forma indireta (por endereco)

    funcao(pont); // ou funcao(&var);

    printf("O novo de valor de var eh %d.\n", var);

    free(triangulo); // ao menos antes de sair deve liberar a memoria reservada pelo S.O.

    return EXIT_SUCCESS;
}

void funcao(int* x) {
    printf("O valor passado pra funcao eh %d.\n", *x);
    *x = *x * 2;
    printf("O novo valor eh %d.\n", *x);
}

// void maius(char string[]) {
void maius(char* string) {
    // int i = 0;
    // while (string[i] != '\0') {
    //     string[i] = toupper(string[i]);
    while (*string != '\0') {
        *string = toupper(*string);
        // ++i;
        ++string;
    }
}

void espelho(const Ponto* p) { // 'const' impede que 'p' seja usado para alterar
                               // a variavel recebida
    Ponto p1, p2, p3;
    p1.x = p->x; // Note que p1 continua usando _._ (o operador de acesso ao campo)
    p1.y = -p->y;
    p2.x = -p->x;
    p2.y = p->y;
    p3.x = -p->x;
    p3.y = -p->y;

    printf("Os espelhos de p{%.1f,%.1f} sao:\n", p->x, p->y);
    printf("p1{%.1f,%.1f}\n", p1.x, p1.y);
    printf("p2{%.1f,%.1f}\n", p2.x, p2.y);
    printf("p3{%.1f,%.1f}\n", p3.x, p3.y);
}

float dist_pontos(const Ponto* p1, const Ponto* p2) {
    // ...
    return 0.0;
}

float perim_triang(const Ponto* triang) {
    const Ponto* aux = triang; // inicia no primeiro ponto do vetor de pontos
    float perimetro = dist_pontos(aux, aux+1);
    perimetro += dist_pontos(aux+1, aux+2);
    perimetro += dist_pontos(aux+2, aux);
    return perimetro;
}
