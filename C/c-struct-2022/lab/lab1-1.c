/* Вариант 36
 * Из входного потока вводится непрямоугольная матрица целых чисел
 * [Aij]  i = 1, ..., M,  j = 1, ..., Ni.
 * Значения M и Ni заранее не известны и вводятся из входного потока.
 * Сформировать вектор, упорядочив по возрастанию значения той строки матрицы, в которой
 * сумма элементов максимальна.
 * Если таких строк несколько, упорядочить одну (любую) строку.
 * В дополнительных функциях доступ к элементам массивов реализовать с помощью указателей.
 * Исходную и полученную матрицы вывести в выходной поток с необходимыми комментариями.
 */
#include "lab1-1.h"

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
            //printf("%10lf ", *p);
            printf("%.0lf ", *p);
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

int GetLineSum(struct Line *pLine) {
    double result = 0;
    for (int i = 0; i < pLine->n; ++i) {
        result = result + pLine->a[i];
    }
    return result;
}

struct Line *GetMaxLine(struct Matrix *pMatrix) {
    struct Line *pMaxSumLine;
    int maxSumValue = 0;
    if (pMatrix) {
        for (int i = 0; i < (pMatrix->lines); ++i) {
            int rowSum = GetLineSum(&pMatrix->matr[i]);
            if (maxSumValue < rowSum) {
                maxSumValue = rowSum;
                pMaxSumLine = &pMatrix->matr[i];
            }
        }
        return pMaxSumLine;
    }
}

struct Line *SortLine(struct Line *pLine) {
    double *LineArray;
    LineArray = pLine->a;
    int n = pLine->n;
    bubbleSort(LineArray, n, 0);
    return pLine;
}

void bubbleSort(double *a, int n, char isAsc) {
    if (isAsc == 0) {
        int i, j;
        //Цикл сравнения
        for (i = 0; i < n - 1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                //Если порядок не правильный, меняем их местами
                if (a[j] > a[j + 1]) {
                    double tmp2 = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = tmp2;
                }
            }
        }
    } else if (isAsc == 1) {
        int i, j;
        //Цикл сравнения
        for (i = 0; i < n - 1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                //Если порядок не правильный, меняем их местами
                if (a[j] < a[j + 1]) {
                    double tmp2 = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = tmp2;
                }
            }
        }
    }
}

int Execute() {
    int exitFlag = 0;
    while (exitFlag = 1) {
        Matrix matr = {0, NULL};
        if (input(&matr) == 0) {
            printf("%s\n", "End of file occured");
            return 1;
        }
        output("\nSource matrix", matr);
        Line *maxLine = GetMaxLine(&matr);
        SortLine(maxLine);
        printf("Matrix sorted.\n");
        //output("\nResult matrix", matr);
        printf("Result matrix:\n");
        for (int i = 0; i < maxLine->n; ++i) {
            printf("%.0lf ", maxLine->a[i]);
        }
        erase(&matr);
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
