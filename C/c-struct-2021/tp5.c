#include <stdio.h>
char* skipspace(char*);
int skipword(char*);
int main () {
    char orig[100], sorted[100], *po, *ps;
    int i, j, l;
    while (printf("Введите строку, для выхода нажмите ctrl+d\n"), gets(orig)){
        for (po=orig, ps=sorted, sorted[0]='\0'; *(po=skipspace(po));) {
            l=skipword(po);
            if (*po==*(po+l-1)) {
                for (i=0; i<l; i++) *ps++=*po++;
                *ps++=' ';
            }
            else po+=l;
        }
        *ps='\0';
        printf("Исходная строка %s\n", orig);
        printf("Результат %s\n", sorted);
    }
    return 0;
}
char* skipspace(char* p) {
    for(; *p==' '||*p=='\t'; p++);
    return p;
}
int skipword(char* p) {
    int i;
    for (i=0; *p&&*p!=' '&&*p!='\t'; i++, p++);
    return i;
}
