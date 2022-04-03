#include <stdlib.h>
#include <stdio.h>
#include <model.h>

struct RowNode *CreateRow(int length) {
    int input, counter;
    struct RowNode **p;
    struct RowNode *f;

    counter = length;

    for (p = &f; counter-- > 0; p = &(*p)->pNextValue) {
        printf("Enter value %d:\n", length - counter);
        scanf("%d", &input);
        *p = malloc(sizeof(struct RowNode));
        (*p)->value = input;
    }

    *p = NULL;

    return f;
}

void DisplayRow(struct RowNode *pList) {
    int i;
    for (i = 1; pList; i++, pList = pList->pNextValue) {
        printf("%d%c", pList->value, (pList->pNextValue == NULL) ? '\n' : ' ');
    }
}

struct MatrixNode *CreateMatrix() {
    int dimensionCount, counter;
    struct MatrixNode **pNextRow;
    struct MatrixNode *pMatrixHead;

    printf("Enter dimension count:\n");
    scanf("%d", &dimensionCount);

    if (dimensionCount <= 0 || dimensionCount > 20)
        return NULL;

    counter = dimensionCount;

    for (pNextRow = &pMatrixHead; counter-- > 0; pNextRow = &(*pNextRow)->pNextRow) {
        *pNextRow = malloc(sizeof(struct MatrixNode));
        (*pNextRow)->row = CreateRow(dimensionCount);
    }

    *pNextRow = NULL;

    return pMatrixHead;
}

void DisplayMatrix(struct MatrixNode *pMatrix) {
    int i;
    struct RowNode *pCurrentMatrixRow;

    for (i = 1; pMatrix; i++, pMatrix = pMatrix->pNextRow) {
        pCurrentMatrixRow = pMatrix->row;

        DisplayRow(pCurrentMatrixRow);

        if (pMatrix->pNextRow == NULL)
            return;
    }
}

void DisposeMatrix(struct MatrixNode *pMatrix) {
    if (pMatrix) {
        DisposeMatrix(pMatrix->pNextRow);
        free(pMatrix);
    }
}

void SortRow(struct RowNode *pListHead) {
    int f, tmp;
    struct RowNode *q;

    for (f = 1; f;) {
        for (f = 0, q = pListHead; q && q->pNextValue; q = q->pNextValue) {
            if (q->value > q->pNextValue->value) {
                tmp = q->value;
                q->value = q->pNextValue->value;
                q->pNextValue->value = tmp;
                f = 1;
            }
        }
    }
}

int GetRowSum(struct RowNode *pRow) {
    if (pRow->pNextValue == NULL) {
        return pRow->value;
    }

    return (pRow->value + GetRowSum(pRow->pNextValue));
}

struct RowNode *GetMaxRow(struct MatrixNode *pMatrix) {
    struct RowNode *pMaxSumRow;
    int maxSumValue = 0;
    int counter;

    if (pMatrix) {
        for (counter = 0; pMatrix; counter++, pMatrix = pMatrix->pNextRow) {
            int rowSum = GetRowSum(pMatrix->row);

            if (maxSumValue < rowSum) {
                maxSumValue = rowSum;
                pMaxSumRow = pMatrix->row;
            }
        }
        return pMaxSumRow;
    }
}