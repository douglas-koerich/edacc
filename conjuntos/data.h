#ifndef DATA_H
#define DATA_H

#include <stdbool.h>

struct Data;
typedef struct Data Data;

Data* aloca_data(void);
void le_data(Data*);
void imprime_data(void*);
bool compara_datas(void*, void*);

#endif // DATA_H
