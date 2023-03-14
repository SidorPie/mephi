#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Item {
    char c;
    struct Item *next;
} Item;

//Ввод ѝтроки-ѝпиѝка
int getList(Item **);

//Вывод ѝтроки-ѝпиѝка
void putList(const char *, Item *);

//Оѝвобождение памѝти
Item *deleteList(Item *);

//Формирование новой ѝтроки-ѝпиѝка
Item *newString(Item *);

int IsCorrectSequence (Item *p);
//Удаление пробелов из ѝтроки-ѝпиѝка
Item *delSpace(Item *);

//Пропуѝк ѝлова в ѝтроке-ѝпиѝке
Item *skipWord(Item *);

//Удаление ѝлова из ѝтроки-ѝпиѝка
Item *delWord(Item *);

int Execute();