#include "lab11.h"

int getInt(int *a) {
    int n;
    do {
        n = scanf_s("%d", a, sizeof(int));
        if (n < 0)
            return 0;
        if (n == 0) {
            printf("%s\n", "Error! Repeat input");
            scanf_s("%*c", 0);
        }
    } while (n == 0);
    return 1;
}

int getDouble(double *a) {
    int n;
    do {
        n = scanf_s("%lf", a, sizeof(double));
        if (n < 0)
            return 0;
        if (n == 0) {
            printf("%s\n", "Error! Repeat input");
            scanf_s("%*c", 0);
        }
    } while (n == 0);
    return 1;
}

int input(Matrix *rm) {
    const char *pr = "";
    int m;
    int i, j;
    double *p;
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
        p = (double *) malloc(sizeof(double) * m);
        rm->matr[i].a = p;
        printf("Enter items for matrix line #%d:\n", i + 1);
        for (j = 0; j < m; ++j, ++p)
            if (getDouble(p) == 0) {
                rm->lines = i + 1;
                erase(rm);
                return 0;
            }
    }
    return 1;
}

void output(const char *msg, Matrix a) {
    int i, j;
    double *p;
    printf("%s:\n", msg);
    for (i = 0; i < a.lines; ++i) {
        p = a.matr[i].a;
        for (j = 0; j < a.matr[i].n; ++j, ++p)
            printf("%10lf ", *p);
        printf("\n");
    }
}

void erase(Matrix *a) {
    int i;
    for (i = 0; i < a->lines; ++i)
        free(a->matr[i].a);
    free(a->matr);
    a->lines = 0;
    a->matr = NULL;
}

double minmax(Matrix pm) {
    double *s = (double *) malloc(
            sizeof(double) * pm.lines); // Вектор для получения мах элементов в строке - по строкам
    double res;
    double *p = s;
    int i;

    for (i = 0; i < pm.lines; ++i)
        *p++ = max(pm.matr[i].a, pm.matr[i].n); // s[i] = mm(pm.matr[i].a,    pm.matr[i].n, 1);

    res = min(s, pm.lines); //res = mm(s, pm.lines, -1);

    free(s);

    return res;
}

double max(double a[], int m) {
    double res = *a;
    for (; m-- > 0; ++a)
        if (*a > res)
            res = *a;
    return res;
}

double min(double a[], int m) {
    double res = *a;
    for (; m-- > 0; ++a)
        if (*a < res)
            res = *a;
    return res;
}

int GetLineSum(struct Line *pLine) {
    double result = 0;

    for (int i = 0; i < pLine->n; ++i) {
        result = result + pLine->a[i];
    }
    return result;
}

struct Line* GetMaxLine(struct Matrix pMatrix) {
    
    struct Line pMaxSumLine;// = (Line *) malloc(sizeof(struct Line));;
    int maxSumValue = 0;

    if (&pMatrix) {

        for (int i = 0; i < (pMatrix.lines); ++i) {
            int rowSum = GetLineSum(&pMatrix.matr[i]);

            if (maxSumValue < rowSum) {
                maxSumValue = rowSum;
                pMaxSumLine = pMatrix.matr[i];
            }
        }

        return &pMaxSumLine;
    }
}

void SortLine(struct Line *pLine) {

    //double *q = (double *) malloc(sizeof(double) * pLine.n);
    //double *q;
    //q = pLine.a;
    bubbleSort(pLine->a,pLine->n,0);
    //return q; 
}

void bubbleSort(double *a, int n, char isAsc) {
    if (isAsc == 0) {
        int i, j;
        for (i = 0; i < n - 1; i++) //Цикл сравнения 
        {
            for (j = 0; j < n - i - 1; j++) {
                if (a[j] > a[j + 1]) //Если порядок не правильный, меняем их местами
                {
                    double tmp2 = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = tmp2;
                }
            }
        }
    } else if (isAsc == 1) {
        int i, j;
        for (i = 0; i < n - 1; i++) //Цикл сравнения 
        {
            for (j = 0; j < n - i - 1; j++) {

                if (a[j] < a[j + 1]) //Если порядок не правильный, меняем их местами
                {
                    double tmp2 = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = tmp2;
                }
            }
        }
    }
}


int Execute() {
    
    Matrix matr = {0, NULL};
    double res;
    
    if (input(&matr) == 0) {
        printf("%s\n", "End of file occured");
        return 1;
    }
    
    res = minmax(matr);
    
    Line *maxLine = GetMaxLine(matr);
    
    SortLine(maxLine);
    
    for (int i = 0; i < &maxLine->n; ++i) 
    {
        printf("%i",&maxLine->a[i]);    
    }
    
    output("Source matrix", matr);
    printf("Result: %f\n", res);
    erase(&matr);
   
    return 0;
}
