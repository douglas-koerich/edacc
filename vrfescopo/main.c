/* PROBLEMA: Escreva um programa que abra um arquivo-fonte em linguagem C qualquer
 * e retorne VERDADEIRO/FALSO se o codigo tem algum "descasamento" nos seguintes
 * delimitadores: {}, [], (). Por exemplo, a linha abaixo estah ok:
 * int c = (x + y) * (w - z);
 * enquanto as linhas a seguir nao estao corretas:
 * {
 *     int c = (x + y) * (w - z);
 * -fim do arquivo-
 * pois faltou o } antes de terminar o arquivo.
 * Utilize uma pilha como estrutura de dados de apoio para essa verificacao.
 */

