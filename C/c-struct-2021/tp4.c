#include <stdio.h>
#include <string.h>
int main () {
    char orig[100], sorted[100], *p, *wp[26];
    int i, j, l, wq, wl[26];
    while (printf("Введите строку, для выхода нажмите ctrl+d\n"), gets(orig)){
        for (p=orig, strcpy(sorted, ""); *(p+=strspn(p," \t")); p+=l) {
            l=strcspn(p, " \t");
            if (*p==*(p+l-1)) strncat(sorted, p, l), strcat(sorted, " ");
        }
        printf("Исходная строка %s\n", orig);
        printf("Результат %s\n", sorted);
    }
    return 0;
}

