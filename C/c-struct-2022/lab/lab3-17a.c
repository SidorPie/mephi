#include <lab3-17a.h>

int Execute()
{
    const char *msgs[] = {"0. Quit", "1. Add", "2. Find exact", "3. Find all", "4. Clear table", "5. Show table"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_FindAllItems, D_ClearTable, D_Show};

    Table table = {NULL};
    int rc;

    while (rc = dialog(msgs, NMsgs))
        if (!fptr[rc](&table))
            break;
    printf("That's all. Bye!\n");

    return 0;
}

int dialog(const char *msgs[], int N)
{
    char *errmsg = "";
    int rc;
    int i, n;
    do
    {
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";

        for (i = 0; i < N; ++i)
            puts(msgs[i]);
        puts("Make your choice: --> ");
        n = getInt(&rc);
        scanf("%*c");
        if (n == 0)
            rc = 0;
    } while (rc < 0 || rc >= N);
    return rc;
}

int hash(int key)
{
    return key % SIZE;
}

// void add_item(int key, char *info)
// {
//     Item *new_item = (Item *)malloc(sizeof(Item));
//     new_item->key = key;
//     new_item->info = info;
//     new_item->release = 1;
//     new_item->next = NULL;
//     int index = hash(key);
//     if (table[index] == NULL)
//     {
//         table[index] = new_item;
//     }
//     else
//     {
//         Item *current_item = table[index];
//         while (current_item->next != NULL)
//         {
//             if (current_item->key == key)
//             {
//                 new_item->release = current_item->release + 1;
//             }
//             current_item = current_item->next;
//         }
//         if (current_item->key == key)
//         {
//             new_item->release = current_item->release + 1;
//         }
//         current_item->next = new_item;
//     }
// }

Item *find_item(Table *table, int key, int release)
{
    int index = hash(key);
    Item *current_item = table->table[index];
    while (current_item != NULL)
    {
        if (current_item->key == key && current_item->release == release)
        {
            return current_item;
        }
        current_item = current_item->next;
    }
    return NULL;
}
int GetLastRev(Item ** items)
{
    int i = 0;
    int release = 0;

    while(items[i]!=NULL)
    {
        if(items[i]->release>release)
        {
            release=items[i]->release;
        }
        i++;
    }
    return release;
}
Item **find_all_items(Table *table, int key)
{
    int index = hash(key);
    Item *current_item = table->table[index];
    int count = 0;
    while (current_item != NULL)
    {
        if (current_item->key == key)
        {
            count++;
        }
        current_item = current_item->next;
    }

    Item **items = (Item **)malloc((count + 1) * sizeof(Item *));
    current_item = table->table[index];
    int i = 0;
    while (current_item != NULL)
    {
        if (current_item->key == key)
        {
            items[i] = current_item;
            i++;
        }
        current_item = current_item->next;
    }
    items[i] = NULL;

    return items;
}

// void clear_table()
// {
//     for (int i = 0; i < SIZE; i++)
//     {
//         if (table[i] != NULL)
//         {
//             Item *current_item = table[i];
//             Item *prev_item = NULL;
//             while (current_item != NULL)
//             {
//                 if (current_item->next == NULL)
//                 {
//                     if (prev_item != NULL)
//                     {
//                         prev_item->next = NULL;
//                     }
//                     free(current_item);
//                 }
//                 else
//                 {
//                     prev_item = current_item;
//                     current_item = current_item->next;
//                 }
//             }
//             table[i] = NULL;
//         }
//     }
// }

int D_Find(Table *table)
{
    int key;
    int release;
    printf("Input key -> ");
    getInt(&key);
    scanf("%*c");
    printf("Input version -> ");
    getInt(&release);
    scanf("%*c");
    Item *item = find_item(table, key, release);
    if(item != NULL)
    {
        printf("(%d, %d, %s)\n", item->key, item->release, item->info);
    }
    else 
        printf("Not found");

    return 1;
}
int D_FindAllItems(Table *table)
{
    int key;
    printf("Input key -> ");
    getInt(&key);
    scanf("%*c");

    Item **items = find_all_items(table, key);
    for (int i = 0; items[i] != NULL; i++)
    {
        printf("(%d, %d, %s)\n", items[i]->key, items[i]->release, items[i]->info);
    }
    free(items);

    return 1;
}
int D_ClearTable(Table *table)
{
    int i;
    int key;
    for (i = 0; i < SIZE; i++)
    {
        Item *head = table->table[i];
        
        Item *current = table->table[i];
        Item *current2;
        Item *previous2 = NULL;
        while (current != NULL)
        {
            //previous = NULL;
            key = current->key;
            current2 = current->next;
            previous2 = current;
            while(current2!=NULL)
            {   
                if(current2->key == key)
                {
                    previous2->next=current2->next;
                    free(current2);
                    current2 = current2->next;
                }else
                {
                previous2 = current2;
                current2 = current2->next;}
            }
            
            current = current->next;
        }   
    }

    return 1;
}
int D_Show(Table *table)
{   
    printf("|key|rel|inf|\n");
    for (int i = 0; i < SIZE; i++)
    {
        Item *curr = table->table[i];
        printf("%d|",i);
        while (curr != NULL)
        {
            //printf("key=%d release=%d info=%s\n", curr->key, curr->release, curr->info);
            
            printf(" |%d|%d|%s|->", curr->key, curr->release, curr->info);
            curr = curr->next;
        }
        printf("\n");
    }
    return 1;
}
int D_Add(Table *table)
{
     int key;
     char *info;
     printf("Input key -> ");
     getInt(&key);
     scanf("%*c");
     printf("Input info -> ");
     info = getStr();
     int index = hash(key);
     Item *curr = table->table[index];
     Item *prev = NULL;
    
     Item **items = find_all_items(table, key);

     int release = 0;
    if (items[0]!=NULL)
    {
     release = GetLastRev(items)+1;
    }

    Item *new_item = (Item *)malloc(sizeof(Item));
    new_item->key = key;
    new_item->release = release;
    new_item->info = info;
    new_item->next = curr;
    table->table[index] = new_item;
    
    return 1;
 
    
    // if (prev == NULL && curr == NULL)
    // {
    //     Item *new_item = (Item *)malloc(sizeof(Item));
    //     new_item->key = key;
    //     new_item->release = 1;
    //     new_item->info = info;
    //     new_item->next = NULL;
    //     table->table[index] = new_item;
    //     return 1;
    // }
    // else if (prev == NULL && curr != NULL)
    // {
    //     Item *new_item = (Item *)malloc(sizeof(Item));
    //     new_item->key = key;
    //     new_item->release = curr->release + 1;
    //     new_item->info = info;
    //     new_item->next = curr;
    //     table->table[index] = new_item;
    //     return 1;
    // }
    // else if (prev != NULL && curr == NULL)
    // {
    //     Item *new_item = (Item *)malloc(sizeof(Item));
    //     new_item->key = key;
    //     new_item->release = prev->release + 1;
    //     new_item->info = info;
    //     new_item->next = NULL;
    //     prev->next = new_item;
    //     return 1;
    // }
    // else
    // {
    //     return 0;
    // }
}

int getInt(int *a)
{
    int n;
    do
    {
        n = scanf("%d", a);
        if (n < 0)
            return 0;
        if (n == 0)
        {
            printf("%s\n", "Error! Repeat input");
            scanf("%*c", 0);
        }
    } while (n == 0);
    return 1;
}

char *getStr()
{
    int flag = 1, len = 0;
    char *input = NULL;
    printf("Input your string: ");
    while (flag > 0)
    {
        char *buff = malloc(200 * sizeof(char));
        flag = scanf("%199[^\n]", buff);
        if (flag == EOF)
        {
            input = NULL;
        }
        else if (flag == 0)
        {
            scanf("%*c");
        }
        else
        {
            int buffLen = strlen(buff);
            input = realloc(input, (len + buffLen) * sizeof(char));
            for (int i = 0; i < buffLen; i++)
            {
                input[len + i] = buff[i];
            }
            len += buffLen;
        }
        free(buff);
    }
    if (flag != -1)
    {
        input = realloc(input, (len + 1) * sizeof(char));
        input[len] = '\0';
    }
    return input;
}

// void show(Table *)
// {
//     for (int i = 0; i < SIZE; i++)
//     {
//         if (table[i] != NULL)
//         {
//             Item *current_item = table[i];
//             while (current_item != NULL)
//             {
//                 printf("(%d, %d, %s)\n", current_item->key, current_item->release, current_item->info);
//                 current_item = current_item->next;
//             }
//         }
//     }
// }