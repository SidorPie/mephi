#include <stdio.h>
#include "lab3.h"

#define MAXLEN 100

int main(void) {
    int errFlag = 0;
    int v[MAXLEN];
    int n;
    int i;

    printf("Укажите желаемое количество элементов:");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        if (scanf("%d", &v[i]) == 1) {}
        else {
            errFlag = -1;
        }
        if (errFlag == -1) {
            printf("Введены неверные данные");
        }
    }

    shellsort(v, n);

    for (i = 0; i < n; i++)
        printf("%d ", v[i]);

    printf("\n");
    return 0;
}










