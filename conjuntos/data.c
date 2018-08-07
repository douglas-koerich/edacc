#include <stdlib.h>
#include <stdio.h>
#include "data.h"

struct Data {
    unsigned d, m, a;
};

Data* aloca_data(void) {
    return malloc(sizeof(Data));
}

void le_data(Data* data) {
    printf("Digite o dia [DD]: ");
    scanf("%u", &data->d);
    printf("Digite o mes [MM]: ");
    scanf("%u", &data->m);
    printf("Digite o ano [AAAA]: ");
    scanf("%u", &data->a);
}

void imprime_data(void* d) {
    const char* const meses[] = {
        [1] = "jan", "fev", "mar",
        "abr", "mai", "jun",
        "jul", "ago", "set",
        "out", "nov", "dez"
    };
    if (NULL == d) {
        printf("\"??-???-????\"");
        return;
    }
    Data* data = (Data*) d;
    switch (data->m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (0 == data->d || 31 < data->d) {
                printf("\"??");
            } else {
                printf("\"%02u", data->d);
            }
            printf("-%s-", meses[data->m]);
            break;

        case 4: case 6: case 9: case 11:
            if (0 == data->d || 30 < data->d) {
                printf("\"??");
            } else {
                printf("\"%02u", data->d);
            }
            printf("-%s-", meses[data->m]);
            break;

        case 2:
            if (0 == data->d || 28 < data->d) {
                printf("\"??");
            } else {
                printf("\"%02u", data->d);
            }
            printf("-%s-", meses[data->m]);
            break;

        default:
            printf("\"??-???-");
    }
    printf("%04u\"", data->a);
}

bool compara_datas(void* d1, void* d2) {
    if (NULL == d1) {
        if (NULL == d2) {
            return true;
        }
        return false;
    } else if (NULL == d2) {
        return false;
    }
    Data* data_1 = (Data*) d1;
    Data* data_2 = (Data*) d2;
    if (data_1->d == data_2->d && data_1->m == data_2->m && data_1->a == data_2->a) {
        return true;
    }
    return false;
}


