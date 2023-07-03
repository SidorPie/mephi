#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5

typedef struct Item {
    int key;                          
    int release;                      
    char *info;                       
    struct Item *next;         
} Item;

typedef struct Table {
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
//void add_item(int key, char *info);   
Item *find_item(Table *table,int key, int release);   
Item **find_all_items(Table *table,int key); 
int GetLastRev(Item ** items);      
//void clear_table();                 
//void display_table();                

//Item *table[SIZE];