/* Вариант 21
Из входного потока вводитѝѝ произвольное чиѝло пар ѝтрок,
ѝоѝтоѝщих из поѝледовательноѝти ѝлов, которые могут быть
разделены одним или неѝколькими пробелами и/или знаками табулѝции.
Длина каждой ѝтроки произвольна. Конец ввода определѝетѝѝ концом файла.
При обработке каждой пары ѝтрок ѝформировать новую ѝтроку, помеѝтив в неё
нечётные ѝлова из первой и чётные из второй. Слова в образованной ѝтроке
должны быть разделены только одним пробелом. Полученную ѝтроку вывеѝти на ѝкран.
 каждаѝ ѝтрока предѝтавлена ѝпиѝком;
 первое поле ѝлемента ѝпиѝка - ѝимвол ѝтроки;
 второе - указатель на ѝледующий ѝлемент ѝпиѝка или NULL в конце ѝпиѝка;
 ѝпиѝок результата формировать, модифицируѝ иѝходный ѝпиѝок.
Примечаниѝ:
⦝ Ввод ѝтрок должен быть организован ѝ помощью функции scanf() ѝо ѝпецификациѝми длѝ ввода ѝтрок.
 Функцию getchar() или ѝпецификацию %c в scanf() не иѝпользовать!
⦝ Целеѝообразно обработку ѝтрок оформить ѝоответѝтвующей функцией, тогда в функции main должны быть ввод ѝтроки,
 вызов функции обработки, вывод результата – в цикле, пока не закончитѝѝ ввод;
 конец цикла – по доѝтижении конца файла.
⦝ Длѝ варианта c) вѝе функции должны работать ѝо ѝпиѝком;
 при вводе ѝтроки ѝледует ѝразу ѝоздавать ѝпиѝок.
 */

#include "lab2-0.h"

int getList(Item **pptr) {
    char buf[21], *str;
    Item head = {'*', NULL};
    Item *last = &head;
    int n, rc = 1;

    do {
        n = scanf("%20[^\n]", buf);
        if (n < 0) {
            deleteList(head.next);
            head.next = NULL;
            rc = 0;
            continue;
        }
        if (n > 0) {
            for (str = buf; *str != '\0'; ++str) {
                last->next = (Item *) malloc(sizeof(Item));
                last = last->next;
                last->c = *str;
            }
            last->next = NULL;
        } else
            scanf("%*c");
    } while (n > 0);
    *pptr = head.next;
    return rc;
}

void putList(const char *msg, Item *ptr) {
    printf("%s: \"", msg);
    for (; ptr != NULL; ptr = ptr->next)
        printf("%c", ptr->c);
    printf("\"\n");
}

Item *deleteList(Item *ptr) {
    Item *tmp = NULL;
    while (ptr != NULL) {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    return ptr;
}

Item *newString(Item *p, int fl) {
    Item head = {'*', p};
    Item *cur = &head;
    Item *prev = &head;
    int fl = 1;

    while (cur && (cur->next = delSpace(cur->next))) {
        if (fl) {
            cur = skipWord(cur->next);
            prev = cur;
            cur = cur->next;
            if (cur) {
                cur->c = ' ';
            }
        } else
            cur->next = delWord(cur->next);

        fl = !fl;
    }

    if (prev->next) {
        free(prev->next);
        prev->next = NULL;
    }
    return head.next;
}

//Результат - указатель на ѝлемент ѝпиѝка, ѝодержащего непробельный ѝимвол
Item *delSpace(Item *p) {
    Item *tmp;
    while (p && (p->c == ' ' || p->c == '\t')) {
        tmp = p;
        p = p->next;
        free(tmp);
    }
    return p;
}

Item *skipWord(Item *p) {
    while (p->next &&
           p->next->c != ' ' &&
           p->next->c != '\t') {
        p = p->next;
    }

    return p;
}

Item *delWord(Item *p) {
    Item *tmp;
    while (p && p->c != ' ' && p->c != '\t') {
        tmp = p;
        p = p->next;
        free(tmp);
    }
    return p;
}

Item *GetLastChar(Item *p) {
    while (p->next != NULL) {
        p = p->next;
    }
    return p;
}

int Execute() {
    Item *ptr = NULL;
    Item *ptr2 = NULL;
    Item *ptr3 = NULL;

    while (puts("enter string1"), getList(&ptr), puts("enter string2"), getList(&ptr2)) {
        putList("string1", ptr);
        putList("string2", ptr2);

        ptr = newString(ptr, 1);
        putList("Odd string", ptr);

        ptr2 = newString(ptr2, 0);
        putList("Even string", ptr2);

        if (ptr != NULL) {
            ptr3 = GetLastChar(ptr);
            ptr3->next = malloc(sizeof(Item));
            ptr3->next->c = ' ';
            ptr3->next->next = ptr2;

            putList("Result string", ptr);
        }

        ptr = deleteList(ptr);
    }

    return 0;
}