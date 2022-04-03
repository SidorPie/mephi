// Из входного потока вводится непрямоугольная матрица целых чисел
// [Aij]  i = 1, ..., M,  j = 1, ..., Ni.
// Значения M и Ni заранее не известны и вводятся из входного потока.
// Сформировать вектор, упорядочив по возрастанию значения той строки матрицы, в которой
// сумма элементов максимальна. Если таких строк несколько, упорядочить одну (любую) строку.
// В дополнительных функциях доступ к элементам массивов реализовать с помощью указателей.
// Исходную и полученную матрицы вывести в выходной поток с необходимыми комментариями.

#include <stdio.h>
#include <stdlib.h>

struct MatrixNode
{
    struct ListNode* data;
    struct MatrixNode* pNext;
    struct MatrixNode* pPrevious;
};

struct ListNode
{
    int value;
    struct ListNode* pNext;
};

struct ListNode* CreateList();
void DisplayList(struct ListNode*);
void DisposeList(struct ListNode*);
void SortList(struct ListNode*);

struct MatrixNode* CreateMatrix();
void DisplayMatrix(struct MatrixNode*);

int main()
{
    //struct ListNode* pHead;
    //pHead = CreateList();
    //printf("Initial:\n");
    //DisplayList(pHead);
    struct MatrixNode* pMatrixHead;
    pMatrixHead = CreateMatrix();

    return 0;
}

struct ListNode* CreateList(int length)
{
    int input, counter;
    struct ListNode **p;
    struct ListNode  *f; //struct ListNode **p, *f;

    //printf("Enter dimension count, for exit type 0\n");
    //scanf("%d", &dimensionCount);
    //    if (dimensionCount <= 0 || dimensionCount > 20)
    //        return NULL;
    //counter = dimensionCount;
    counter = length;

    for ( p = &f; counter-- > 0; p = &(*p)->pNext )
    {
        printf("Enter value %d:\n", length - counter);
        scanf("%d", &input);
        *p = malloc(sizeof(struct ListNode));
        (*p)->value = input;
    }

    *p = NULL;

    return f;
}

void DisplayList(struct ListNode* pList)
{
    int i;
    for (i = 1; pList ; i++, pList = pList -> pNext )
    {
        printf("%d%c", pList -> value,
               (pList -> pNext == NULL /*|| i%5 == 0*/) ? '\n' : ' ');
    }
}

struct MatrixNode* CreateMatrix()
{
    int dimensionCount, counter;
    struct MatrixNode **pNextNode;
    struct MatrixNode *pHeadNode;

    printf("Enter dimension count, for exit type 0\n");
    scanf("%d", &dimensionCount);

    if (dimensionCount <= 0 || dimensionCount > 20)
        return NULL;

    counter=dimensionCount;

    for ( pNextNode = &pHeadNode; counter-- > 0; pNextNode = &(*pNextNode)->pNext )
    {
        *pNextNode = malloc(sizeof(struct MatrixNode));
        (*pNextNode)->data = CreateList(dimensionCount);
        (*pNextNode)->pPrevious = *pNextNode;
    }

    *pNextNode = NULL;
    (*pHeadNode).pPrevious = NULL;

    return pHeadNode;
}

void disposeList(struct ListNode* pListHead)
{
        if(pListHead)
        {
            disposeList(pListHead->pNext);
            free(pListHead);
        }
}

void sortList(struct ListNode* pListHead)
{
    int f, tmp;
    struct ListNode* q;

    for ( f = 1; f; )
    {
        for (f = 0, q = pListHead ; q&&q->pNext; q = q->pNext)
        {
            if( q->value > q->pNext->value )
            {
                tmp = q->value;
                q->value = q->pNext->value;
                q->pNext->value=tmp;
                f=1;
            }
        }
    }
}