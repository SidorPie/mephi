#ifndef LAB1_LAB11_H
#define LAB1_LAB11_H

#endif //LAB1_LAB11_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

//структура для задания строки матрицы
typedef struct Line {
    int n; //количество элементов в строке матрицы
    double *a; //массив элементов
} Line;

//структура для задания самой матрицы
typedef struct Matrix {
    int lines; //количество строк матрицы
    Line *matr;//массив строк матрицы
} Matrix;

//Прототипы
int getInt(int *); //Ввод целого числа
int getDouble(double *); //Ввод вещественного числа
int input(Matrix *a);//Ввод матрицы
void output(const char *msg, Matrix a); //Вывод матрицы
void erase(Matrix *a); //освобождение памяти
int GetLineSum(struct Line *pLine);

struct Line *GetMaxLine(struct Matrix *pMatrix);

struct Line *SortLine(struct Line *pLine);

void bubbleSort(double *a, int n, char isAsc);

int Execute(); //функция для использования в main

