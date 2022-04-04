#include <stdio.h>
#include <stdlib.h>

struct Item {
    int a;
    struct Item * next;
};
struct Item * createList();
void printList(struct Item *);
void freeList(struct Item *);
void oddevenList(struct Item*, struct Item **, struct Item **);
void sortList(struct Item *);

int main(){
    struct Item * init, * odd, * even;
    while (init=createList()) {
        oddevenList(init, & odd, & even);
        sortList(odd);
        sortList(even);
        printf("Initial list:\n");
        printList(init);
        printf("Odd numbers list:\n");
        printList(odd);
        printf("Even numbers list:\n");
        printList(even);
        freeList(init);
        freeList(odd);
        freeList(even);
    }
    return 0;
}

struct Item * createList() {
    int b, l;
    struct Item ** p, * f;
    printf("Enter number of elements in list, for exit enter 0:\n");
    scanf("%d", &l);
    if (l<=0 || l> 20) return NULL;
    for (p=&f; l-->0; p=&(*p)->next) {
        printf("Enter element value:\n");
        scanf("%d", &b);
        *p=malloc(sizeof(struct Item));
        (*p)->a=b;
    }
    *p=NULL;
    return f;
}
void printList(struct Item * p) {
   int i;
    for (i=1; p; i++, p=p->next)
        printf("%d%c", p->a, (p->next==NULL || i%5==0)?'\n':' ');
}
void freeList(struct Item * p) {
    if (p) {
        freeList(p->next);
        free(p);
    }
}
void oddevenList(struct Item * f, struct Item ** podd, struct Item ** peven) {
    struct Item *** p;
    for (; f; f=f->next) {
        if (f->a%2)
            p=&podd;
        else
            p=&peven;
        **p=malloc(sizeof(struct Item));
        (**p)->a=f->a;
        *p=&(**p)->next;
    }
    *podd=NULL;
    *peven=NULL;
}
void sortList(struct Item * p) {
    int f, tmp;
    struct Item * q;
    for (f=1; f; ) {
        for (f=0, q=p; q && q-> next; q=q->next) {
            if (q->a > q->next->a) {
                tmp=q->a;
                q->a=q->next->a;
                q->next->a=tmp;
                f=1;
            }
        }
    }
}