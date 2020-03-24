#include "fila.h"

void elimina_valor(Fila* f, int x) {
    // Pra eliminar *todas* as ocorrencias de 'x' da fila, vou precisar
    // esvazia-la; porem, ao devolver pra ela os valores remanescentes,
    // eh necessario que os mesmos sejam inseridos na *mesma* ordem relativa
    // que tinham entre si.
    // Assim, uma outra fila (e nao uma pilha, que inverteria!) eh usada
    // como estrutura auxiliar
    Fila* aux = cria(1000); // de novo (como no exerc. 1), uma operacao do TAD
                            // que informasse o tamanho da fila (f, no caso)
                            // seria bastante util --> exercicio 6!!
    while (!underflow(f)) {
        int num = retira(f);
        if (num != x) {
            insere(aux, num);
        }
    }
    while (!underflow(aux)) {
        insere(f, retira(aux));
    }
    destroi(aux);
}
