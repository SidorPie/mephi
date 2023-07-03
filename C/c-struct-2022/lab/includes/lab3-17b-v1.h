#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

struct Item {
  int key;
  int release; 
  char *info; 
  struct Item *next;
};

typedef struct Item Item;

/* Функции работы с таблицей */
void initTable();
void clearTable();
int insertElement(int key, char *info);
Item *findElement(int key, int release);
Item **findAllElements(int key, int *count);
void deleteObsoleteElements(int key);

/* Вспомогательные функции */
int hash(int key);
int readNumber();
char *readString();
void writeTableToFile(char *filename);
void readTableFromFile(char *filename);
void printElement(Item *elem);
void printTable();
int Execute();