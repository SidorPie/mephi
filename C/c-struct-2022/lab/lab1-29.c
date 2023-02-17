/* Ý’Ý°Ñ€Ý¸Ý°Ý½Ñ‚ 29
 * Ý˜Ý· Ý²Ñ…Ý¾Ý´Ý½Ý¾Ý³Ý¾ Ý¿Ý¾Ñ‚Ý¾ÝºÝ° Ý²Ý²Ý¾Ý´Ý¸Ñ‚Ñ�Ñ� Ý½ÝµÝ¿Ñ€Ñ�Ý¼Ý¾ÑƒÝ³Ý¾Ý»ÑŒÝ½Ý°Ñ� Ý¼Ý°Ñ‚Ñ€Ý¸Ñ†Ý° Ñ†ÝµÝ»Ñ‹Ñ… Ñ‡Ý¸Ñ�ÝµÝ»
 * [Aij]  i = 1, ..., M,  j = 1, ..., Ni.
 * Ý—Ý½Ý°Ñ‡ÝµÝ½Ý¸Ñ� M Ý¸ Ni Ý·Ý°Ñ€Ý°Ý½ÝµÝµ Ý½Ýµ Ý¸Ý·Ý²ÝµÑ�Ñ‚Ý½Ñ‹ Ý¸ Ý²Ý²Ý¾Ý´Ñ�Ñ‚Ñ�Ñ� Ý¸Ý· Ý²Ñ…Ý¾Ý´Ý½Ý¾Ý³Ý¾ Ý¿Ý¾Ñ‚Ý¾ÝºÝ°.
 * Ý¡Ñ„Ý¾Ñ€Ý¼Ý¸Ñ€Ý¾Ý²Ý°Ñ‚ÑŒ Ý½Ý¾Ý²ÑƒÑŽ Ý¼Ý°Ñ‚Ñ€Ý¸Ñ†Ñƒ, Ý¿Ý¾Ý¼ÝµÑ�Ñ‚Ý¸Ý² Ý² ÝµÝµ i-ÑŽ Ñ�Ñ‚Ñ€Ý¾ÝºÑƒ Ñ‚Ýµ Ñ�Ý»ÝµÝ¼ÝµÝ½Ñ‚Ñ‹ Ý¸Ý· 
 * i-Ý¹ Ñ�Ñ‚Ñ€Ý¾ÝºÝ¸ Ý¸Ñ�Ñ…Ý¾Ý´Ý½Ý¾Ý¹ Ý¼Ý°Ñ‚Ñ€Ý¸Ñ†Ñ‹, ÝºÝ¾Ý»Ý¸Ñ‡ÝµÑ�Ñ‚Ý²Ý¾ Ñ†Ý¸Ñ„Ñ€ Ý² Ý·Ý°Ý¿Ý¸Ñ�Ý¸ ÝºÝ¾Ñ‚Ý¾Ñ€Ñ‹Ñ… Ý¿Ñ€ÝµÝ²Ñ‹ÑˆÝ°ÝµÑ‚
 *  Ñ�Ñ€ÝµÝ´Ý½ÝµÝµ ÝºÝ¾Ý»Ý¸Ñ‡ÝµÑ�Ñ‚Ý²Ý¾ Ñ†Ý¸Ñ„Ñ€ Ý² Ý·Ý°Ý¿Ý¸Ñ�Ý¸ Ý²Ñ�ÝµÑ… Ñ�Ý»ÝµÝ¼ÝµÝ½Ñ‚Ý¾Ý² Ý´Ý°Ý½Ý½Ý¾Ý¹ Ñ�Ñ‚Ñ€Ý¾ÝºÝ¸ Ý¼Ý°Ñ‚Ñ€Ý¸Ñ†Ñ‹
 * Ý˜Ñ�Ñ…Ý¾Ý´Ý½ÑƒÑŽ Ý¸ Ý¿Ý¾Ý»ÑƒÑ‡ÝµÝ½Ý½ÑƒÑŽ Ý¼Ý°Ñ‚Ñ€Ý¸Ñ†Ñ‹ Ý²Ñ‹Ý²ÝµÑ�Ñ‚Ý¸ Ý² Ý²Ñ‹Ñ…Ý¾Ý´Ý½Ý¾Ý¹ Ý¿Ý¾Ñ‚Ý¾Ýº Ñ� Ý½ÝµÝ¾Ý±Ñ…Ý¾Ý´Ý¸Ý¼Ñ‹Ý¼Ý¸ ÝºÝ¾Ý¼Ý¼ÝµÝ½Ñ‚Ý°Ñ€Ý¸Ñ�Ý¼Ý¸.
 */
////printf("Matrix sorted.\n");
//printf("Result matrix:\n");
//for (int i = 0; i < maxLine->n; ++i) {
//printf("%.0lf ", maxLine->a[i]);
//}
#include "lab1-29.h"

int Execute() {
    int exitFlag = 0;
    while (exitFlag = 1) {
        Matrix matr = {0, NULL};
        Matrix rm ={0,NULL};

        if (input(&matr) == 0) {
            printf("%s\n", "End of file occured");
            return 1;
        }
        output("\nSource matrix", matr);
        
        RefineMatrix(matr, &rm);
        output("\nResult matrix", rm);
        
        erase(&matr);
        printf("\nMatrix disposed.\n");
        erase(&rm);
        printf("\nMatrix disposed.\n");
        printf(" Quit: press 1\n");
        printf("Retry: press 0\n");
        scanf("%d", &exitFlag);
        if (exitFlag == 1)
            return 1;
        else
            exitFlag = 0;
    }
    return 0;
}
int input(Matrix *rm) {
    const char *pr = "";
    int m;
    int i, j;
    int *p;
    do {
        printf("%s\n", pr);
        printf("Enter number of lines: --> ");
        pr = "You are wrong; repeat, please!";
        if (getInt(&m) == 0)
            return 0;
    } while (m < 1);
    rm->lines = m;
    rm->matr = (Line *) calloc(m, sizeof(Line));
    for (i = 0; i < rm->lines; ++i) {
        pr = "";
        do {
            printf("%s\n", pr);
            printf("Enter number of items in line %d: --> ", i + 1);
            pr = "You are wrong; repeat, please!";
            if (getInt(&m) == 0) {
                rm->lines = i;
                erase(rm);
                return 0;
            }
        } while (m < 1);
        rm->matr[i].n = m;
        p = (int *) malloc(sizeof(int) * m);
        rm->matr[i].a = p;
        printf("Enter items for matrix line #%d:\n", i + 1);
        for (j = 0; j < m; ++j, ++p)
            if (getInt(p) == 0) {
                rm->lines = i + 1;
                erase(rm);
                return 0;
            }
    }
    return 1;
}

int getInt(int *a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n < 0)
            return 0;
        if (n == 0) {
            printf("%s\n", "Error! Repeat input");
            scanf("%*c", 0);
        }
    } while (n == 0);
    return 1;
}

void erase(Matrix *a) {
    int i;
    for (i = 0; i < a->lines; ++i)
        free(a->matr[i].a);
    free(a->matr);
    a->lines = 0;
    a->matr = NULL;
}
void output(const char *msg, Matrix a) {
    int i, j;
    int *p;
    printf("%s:\n", msg);
    for (i = 0; i < a.lines; ++i) {
        p = a.matr[i].a;
        for (j = 0; j < a.matr[i].n; ++j, ++p)
            //printf("%10lf ", *p);
            printf("%.0d ", *p);
        printf("\n");
    }
}
void RefineMatrix(Matrix a, Matrix *rm) {
    int i, j, avg;
    int m;
    int *p;
    int *p2;
    int tmp;

    m = a.lines;
    rm->lines = m;
    rm->matr = (Line *) calloc(m, sizeof(Line));

    for (i = 0; i < a.lines; ++i) 
    {
        p = a.matr[i].a;

        avg = GetAvgDigitsCount(p, (a.matr[i].n));

        rm->matr[i].n = a.matr[i].n;
        p2 = (int *) malloc(sizeof(int) * rm->matr[i].n);
        rm->matr[i].a = p2;
        
        for (j = 0; j < a.matr[i].n; ++j, ++p) {

            if(GetDigitsCount(*p)>avg){
                tmp = *p;
                *p2 = tmp;
                ++p2;
            }
        }   
    }
}

int GetAvgDigitsCount(int *pointer, int len) {
    int j, avg=0;
    int *p;
    p = pointer;
    for (j = 0; j < len; ++j, ++p) {
        avg += GetDigitsCount(*p); 
    }

    return avg/len;
}
int GetDigitsCount(int val) {
    int len = 1;

    while((val /= 10)) len++;

    return len;
}