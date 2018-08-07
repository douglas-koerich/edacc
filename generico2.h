#ifndef GENERICO2_H
#define GENERICO2_H

typedef struct generico {
    void* coisa;
    void (*imprime)(void*);
    int (*compara)(void*, void*);
} generico;

#endif
