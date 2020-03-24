#include "pilha.h" // O exercicio eh um "usuario" do TAD pilha

void transfere(Pilha* S2, Pilha* S1) {
    // Se transferir diretamente de S1 pra S2, a disposicao dos elementos
    // em S2 vai ficar *invertida* em relacao a S1; entao, precisamos de
    // "algo" (;-)) que inverta o que vem invertido (X-D)
    Pilha* aux = cria(1000); // aqui precisei atribuir um valor alto por
                             // seguranca; o ideal era ter uma operacao no
                             // TAD pilha que calculasse o tamanho do seu
                             // conteudo --> eh o que pede o exercicio #1!
    while (!underflow(S1)) {
        push(aux, pop(S1));
    }
    while (!underflow(aux)) {
        push(S2, pop(aux));
    }
    destroi(aux); // destroi apenas aquela criada aqui dentro da funcao!
}

