/*
 * Вариант 36
 * Из входного потока вводится непрямоугольная матрица целых чисел
 * [Aij]  i = 1, ..., M,  j = 1, ..., Ni.
 * Значения M и Ni заранее не известны и вводятся из входного потока.
 * Сформировать вектор, упорядочив по возрастанию значения той строки матрицы, в которой
 * сумма элементов максимальна. Если таких строк несколько, упорядочить одну (любую) строку.
 * В дополнительных функциях доступ к элементам массивов реализовать с помощью указателей.
 * Исходную и полученную матрицы вывести в выходной поток с необходимыми комментариями.
 * */
#include <stdio.h>
#include <model.h>

int main() {
    struct MatrixNode *pMatrix;

    int exitFlag = 0;

    while (exitFlag = 'n') {
        pMatrix = CreateMatrix();
        printf("Your input is:\n");
        DisplayMatrix(pMatrix);
        SortRow(GetMaxRow(pMatrix));
        printf("Matrix sorted.\n");
        DisplayMatrix(pMatrix);
        DisposeMatrix(pMatrix);
        printf("Matrix disposed.\n");
        printf(" Quit: press 1\n");
        printf("Retry: press 0\n");
        scanf("%d", &exitFlag);

        if (exitFlag == 1)
            return 0;
        else
            exitFlag = 0;
    }

    return 0;
}

