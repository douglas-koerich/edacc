#ifndef PILHA_USO_INTERNO_H_
#define PILHA_USO_INTERNO_H_

struct Pilha {
    int* vetor; // ponteiro para o vetor alocado com o tamanho pedido
    size_t tamanho; // salva o tamanho solicitado no momento da criacao
    int topo; // indice do topo da pilha dentro do vetor alocado
};

#endif // PILHA_USO_INTERNO_H_
