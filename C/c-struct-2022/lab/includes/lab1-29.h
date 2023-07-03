#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Line {
    int n;
    int *a;
} Line;

typedef struct Matrix {
    int lines; 
    Line *matr;
} Matrix;

int Execute();
int input(Matrix *a);
int getInt(int *);
void erase(Matrix *a);
void output(const char *msg, Matrix a);
void RefineMatrix(Matrix a, Matrix *rm);
int GetAvgDigitsCount(int *p, int l);
int GetDigitsCount(int val);
