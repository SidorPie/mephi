#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Item
{
    int key;
    int offset;
    int len;
} Item;

typedef struct Table
{
    int SZ;
    int n;
    Item *first;
    FILE *fd;
} Table;

int Execute();
int save(Table *ptab);
int D_Load(Table *ptab);
int create(Table *ptab, char *fname, int sz);
int load(Table *ptab, char *fname);
char *findInfo(Table ptab, int k);
int find(Table ptab, int k);
int D_Find(Table *ptab);
int insert(Table *ptab, int k, char *str);
int D_Add(Table *ptab);
int dialog(const char *msgs[], int N);
char *getStr();
int getInt(int *);
int D_Save(Table *ptab);
int delTable(Table *ptab);