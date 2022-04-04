#ifndef LAB1_LAB1_DEMO_H
#define LAB1_LAB1_DEMO_H

#endif //LAB1_LAB1_DEMO_H

#include <stdio.h>
#include <malloc.h>

int ExecuteMain();

typedef struct Line {
    int n;
    double *a;
} Line;

typedef struct Matrix {
    int lines;
    Line *matr;
} Matrix;

int getInt(int *);

int getDouble(double *);

int input(Matrix *a);

void output(const char *msg, Matrix a);

void erase(Matrix *a);

double minmax(Matrix a);

double max(double a[], int m);

double min(double a[], int m);

double mm(double a[], int m, int flag);