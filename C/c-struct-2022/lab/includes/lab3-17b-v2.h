#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

typedef struct Item {
    int key;                          
    int release;                      
    char *info;
    int len;                       
    struct Item *next;         
} Item;

typedef struct Table {
    //int n;
    Item *table[SIZE];    
} Table;
int Execute();
int D_Add(Table *table);
int D_Find(Table *table);
int D_FindAllItems(Table *table);
int D_ClearTable(Table *table);
int D_Show(Table *table);
int hash(int key);                   
int dialog(const char *msgs[], int N);
int getInt(int *a);
char *getStr();
Item *find_item(Table *table,int key, int release);   
Item **find_all_items(Table *table,int key);       
int D_Save(Table *table);
int D_Load(Table *table);
int insertElement(Table *table, int key, char *info);
