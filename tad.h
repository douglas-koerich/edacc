#ifndef TAD_H
#define TAD_H

// Este arquivo eh disponibilizado para o usuario do TAD de tal forma a ser
// compilado com o codigo-fonte dele(a)

// Definicao estrutural do tipo (TAD) eh oculta ao usuario
struct complexo;
typedef struct complexo complexo;

// Definicao funcional, ou seja, as operacoes validas/possiveis do tipo sao
// prototipadas aqui nesse cabecalho
complexo* inicia(int a, int b); // para fazer a + bi (chame libera() ou faca o free por conta)
void libera(complexo* c); // a operacao correta do TAD para liberar a memoria usada por ele
complexo* duplica(const complexo* c); // duplica o valor em outra variavel na memoria (const => nao mexe em c)
void conjugado(complexo* c);    // altera o valor atual (nao tem const => mexe em c!!)
complexo* soma(const complexo* i1, const complexo* i2);  // devolve o valor de um inteiro
void imprime(const complexo* c); // imprime na forma a + bi

#endif // TAD_H
