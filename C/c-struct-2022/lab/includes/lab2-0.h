#ifndef MAIN_C_LAB2_0_H
#define MAIN_C_LAB2_0_H

#endif //MAIN_C_LAB2_0_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Item {
    char c;
    struct Item *next;
} Item;

int getList(Item **);

void putList(const char *, Item *);

Item *deleteList(Item *);

Item *newString(Item *, int fl);

Item *delSpace(Item *);

Item *skipWord(Item *);

Item *delWord(Item *);

Item * GetLastChar(Item *p);
int Execute();