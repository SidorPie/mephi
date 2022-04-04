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
double minmax(Matrix a); //функция вычисления главного результата
double max(double a[], int m);//вычисление максимального элемента вектора
double min(double a[], int m);//вычисление минимального элемента вектора

int Execute(); //функция аналог main
int GetLineSum(struct Line *pLine);
struct Line *GetMaxLine(struct Matrix pMatrix);
struct Line *SortLine(struct Line *pLineHead);
void bubbleSort(double *a, int n, char isAsc);

