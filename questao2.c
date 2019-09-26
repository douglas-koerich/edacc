#include "fila.h"

void mantem_exclusivos(Fila* f1, Fila* f2) {
    if (f1 == NULL || f2 == NULL) {
        return;
    }
    char v, w;
    Fila* aux1 = cria(); // para armazenar o que for removido da (e depois
                         // devolvido para) fila f1
    Fila* aux2 = cria(); // o mesmo para suportar a fila f2
    while (!underflow(f1)) {
        dequeue(f1, &v); // retira o proximo elemento de f1 para comparar
        bool achou = false;
        while(!underflow(f2)) { // deve comparar com TODA a fila f2
            dequeue(f2, &w);
            enqueue(aux2, w); // salva o que tirou de f2 pra devolver depois
            if (w == v) {
                achou = true;
                // Nao pode parar aqui soh porque achou um nao-exclusivo,
                // porque nao ha como devolver "parte" de f2 sem mudar a
                // sua ordem
            }
        }
        // Ao terminar de inspecionar a fila f2, volta seus elementos
        // na mesma ordem em que estavam
        while (!underflow(aux2)) {
            dequeue(aux2, &w);
            enqueue(f2, w);
        }
        if (achou == false) { // o que tirei de f1 NAO existia em f2?
            enqueue(aux1, v); // esse valor pode ser salvo (vai voltar
                              // depois pra f1)
        }
    }
    while (!underflow(aux1)) {
        dequeue(aux1, &v);
        enqueue(f1, v);
    }
    destroi(aux1);
    destroi(aux2);
}

