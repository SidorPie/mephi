#include "lab2-10.h"

int getList(Item **pptr)
{
    char buf[21], *str;
    Item head = {'*', NULL};
    Item *last = &head;
    int n, rc = 1;

    do
    {
        n = scanf("%20[^\n]", buf);
        if (n < 0)
        {
            deleteList(head.next);
            head.next = NULL;
            rc = 0;
            continue;
        }
        if (n > 0)
        {
            for (str = buf; *str != '\0'; ++str)
            {
                last->next = (Item *)malloc(sizeof(Item));
                last = last->next;
                last->c = *str;
            }
            last->next = NULL;
        }
        else
            scanf("%*c");
    } while (n > 0);
    *pptr = head.next;
    return rc;
}

void putList(const char *msg, Item *ptr)
{
    printf("%s: \"", msg);
    for (; ptr != NULL; ptr = ptr->next)
        printf("%c", ptr->c);
    printf("\"\n");
}

Item *deleteList(Item *ptr)
{
    Item *tmp = NULL;
    while (ptr != NULL)
    {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    return ptr;
}

Item *newString(Item *p)
{
    Item head = {'*', p};
    Item *cur = &head, *prev = &head;
    int fl = 0;

    while (cur && (cur->next = delSpace(cur->next)))
    {
        fl = !IsCorrectSequence(cur);
        if (fl)
        {
            cur = skipWord(cur->next);
            prev = cur;
            cur = cur->next;
            if (cur)
            {
                cur->c = ' ';
            }
        }
        else
            cur->next = delWord(cur->next);
    }

    if (prev->next)
    {
        free(prev->next);
        prev->next = NULL;
    }
    return head.next;
}

int IsCorrectSequence(Item *p)
{
    int ret = 0;
    Item *tmp = p;
    char tmp1, tmp2;
    int a, b;

    while (p->next && p->next->c != ' ' && p->next->c != '\t')
    {
        tmp1 = p->c;
        tmp2 = p->next->c;
        a = tmp1 - '0';
        b = tmp2 - '0';
        if (a > b)
        {
            ret = 1;
        }
        if ((9 < b) || (b < 0))
        {
            ret = 1;
        }
        // if ((0 > a) || (0 > b))
        // {
        //     ret = 1;
        // }

        p = p->next;
    }
    return ret;
}

Item *delSpace(Item *p)
{
    Item *tmp;
    while (p && (p->c == ' ' || p->c == '\t'))
    {
        tmp = p;
        p = p->next;
        free(tmp);
    }
    return p;
}

Item *skipWord(Item *p)
{
    while (p->next && p->next->c != ' ' && p->next->c != '\t')
        p = p->next;
    return p;
}

Item *delWord(Item *p)
{
    Item *tmp;
    while (p && p->c != ' ' && p->c != '\t')
    {
        tmp = p;
        p = p->next;
        free(tmp);
    }
    return p;
}

int Execute()
{
    Item *ptr = NULL;
    while (puts("enter string"), getList(&ptr))
    {
        putList("Entered string", ptr);
        ptr = newString(ptr);
        putList("Result string", ptr);
        ptr = deleteList(ptr);
    }
    return 0;
}