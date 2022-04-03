struct MatrixNode {
    struct RowNode *row;
    struct MatrixNode *pNextRow;
};

struct RowNode {
    int value;
    struct RowNode *pNextValue;
};

struct MatrixNode *CreateMatrix();

struct RowNode *GetMaxRow(struct MatrixNode *pMatrix);

void DisplayMatrix(struct MatrixNode *);

void DisposeMatrix(struct MatrixNode *);

struct RowNode *CreateRow(int length);

void DisplayRow(struct RowNode *pList);

void SortRow(struct RowNode *pListHead);

int GetRowSum(struct RowNode *pColumnValue);
