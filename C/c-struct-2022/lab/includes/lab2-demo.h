#ifndef MAIN_C_LAB2_DEMO_H
#define MAIN_C_LAB2_DEMO_H

#endif //MAIN_C_LAB2_DEMO_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Item {
    char c;
    struct Item *next;
} Item;

//Ввод строки-списка
int getList(Item **);

//Вывод строки-списка
void putList(const char *, Item *);

//Освобождение памяти
Item *deleteList(Item *);

//Формирование новой строки-списка
Item *newString(Item *);

//Удаление пробелов из строки-списка
Item *delSpace(Item *);

//Пропуск слова в строке-списке
Item *skipWord(Item *);

//Удаление слова из строки-списка
Item *delWord(Item *);

int Execute();