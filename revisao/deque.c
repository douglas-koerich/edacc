#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

struct IDeque {
    int* vetor;
    size_t max;
    int inicio, fim;
};

IDeque* d_cria(size_t max) {
    IDeque* nova = (IDeque*) malloc(sizeof(IDeque));
    nova->max = max;
    nova->vetor = (int*) malloc(sizeof(int) * nova->max);
    nova->inicio = nova->fim = nova->max-1;
    return nova;
}

void d_destroi(IDeque* deque) {
    free(deque->vetor);
    free(deque);
}

bool d_underflow(const IDeque* deque) {
    return deque->inicio == deque->fim;
}

bool d_overflow(const IDeque* deque) {
    return deque->fim == (deque->inicio? deque->inicio-1: deque->max-1);
}

void d_enqueue(IDeque* deque, int numero, Lado lado) {
    if (d_overflow(deque)) {
        return;
    }
    if (lado == FIM) {
        deque->fim = deque->fim == deque->max-1? 0: deque->fim + 1;
        deque->vetor[deque->fim] = numero;
    }
    else {
        deque->vetor[deque->inicio] = numero;
        deque->inicio = deque->inicio == 0? deque->max-1: deque->inicio - 1;
    }
}

int d_dequeue(IDeque* deque, Lado lado) {
    if (d_underflow(deque)) {
        return -1;  // erro
    }
    if (lado == INICIO) {
        deque->inicio = deque->inicio == deque->max-1? 0: deque->inicio + 1;
        return deque->vetor[deque->inicio];
    }
    else {
        int i = deque->vetor[deque->fim];
        deque->fim = deque->fim == 0? deque->max-1: deque->fim - 1;
        return i;
    }
}

void d_print(const IDeque* deque) {
	if (d_underflow(deque)) {
		printf("(vazio)");
		return;
	}
    printf("(Inicio) ");
	int i = deque->inicio == deque->max-1? 0: deque->inicio + 1;
    do {
		printf("%d ", deque->vetor[i]);
        i = i == deque->max-1? 0: i + 1;
	} while (i != deque->fim);
    printf("%d ", deque->vetor[i]);  // imprime o elemento no fim
	printf("(Fim)");
}

