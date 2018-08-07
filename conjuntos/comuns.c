#include <stdio.h>
#include "comuns.h"

void imprime_char(void* c) {
    printf("\'%c\'", *(char*) c);
}
bool compara_char(void* c1, void* c2) {
    return *(char*) c1 == * (char*) c2;
}
void imprime_int(void* i) {
    printf("%i", *(int*) i);
}
bool compara_int(void* i1, void* i2) {
    return *(int*) i1 == * (int*) i2;
}
void imprime_float(void* f) {
    printf("%f", *(float*) f);
}
bool compara_float(void* f1, void* f2) {
    return *(float*) f1 == * (float*) f2;
}
void imprime_double(void* d) {
    printf("%lf", *(double*) d);
}
bool compara_double(void* d1, void* d2) {
    return *(double*) d1 == * (double*) d2;
}

