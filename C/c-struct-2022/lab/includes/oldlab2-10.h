#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Item {
    char c;
    struct Item *next;
} Item;

typedef struct DataSet {
    Item d;
    struct DataSet *next;
} DataSet;
int GetStrings (DataSet **data);
int getList(Item **);
void putList(const char *, Item *);
Item *deleteList(Item *);
Item *newString(Item *, int fl);
Item *delSpace(Item *);
Item *skipWord(Item *);
Item *delWord(Item *);
Item *GetLastChar(Item *p);

int Execute();