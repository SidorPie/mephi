#include <lab3-17b-v2.h>

int Execute()
{
    const char *msgs[] = {"0. Quit", "1. Add", "2. Find exact", "3. Find all", "4. Clear table", "5. Show table", "6. Save table","7. Load table"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_FindAllItems, D_ClearTable, D_Show, D_Save, D_Load};

    Table table = {NULL};
    int rc;

    //D_Load(&table);
        
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
    printf("?????? ???????...\n");
    int removed = 0;
    int i;
    for (i = 0; i < SIZE; i++)
    {
        struct Item *current = table->table[i];
        struct Item *previous = NULL;
        while (current != NULL)
        {
            if (current->next != NULL && current->key == current->next->key)
            {
                /* ???? ????????? ??????? ? ??????? ????? ????? ?? ????,
                 * ?? ??????? ??????? ?? ???????? ????????? ??????? ???????? ? ?????? ?????? */
                if (previous == NULL)
                {
                    table->table[i] = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                free(current->info);
                free(current);
                current = previous != NULL ? previous->next : table->table[i];
                removed++;
            }
            else
            {
                previous = current;
                current = current->next;
            }
        }
    }

    printf("??????? ?????????: %d\n", removed);

    return 1;
}
int D_Show(Table *table)
{
    for (int i = 0; i < SIZE; i++)
    {
        Item *curr = table->table[i];
        while (curr != NULL)
        {
            printf("key=%d release=%d info=%s\n", curr->key, curr->release, curr->info);
            curr = curr->next;
        }
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
    insertElement(table, key, info);
    
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

int D_Save(Table *table)
{   
    char *filename = getStr();

    // ???????? ????? ?? ??????
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("?????? ??? ???????? ????? %s\n", filename);
        return 0;
    }

    // ?????? ??????? ???????? ??????? ? ???? ????????????? ???????
    for (int i=0; i<SIZE; i++) {
      Item *elem = table->table[i];
      while (elem != NULL) {
        // ?????? ????? ? ?????? ?????? ????????
        fwrite(&(elem->key), sizeof(int), 1, file);
        fwrite(&(elem->release), sizeof(int), 1, file);

        // ?????? ?????????? ?? ????????
        int infoSize = strlen(elem->info) + 1;
        fwrite(&(infoSize), sizeof(int), 1, file);
        fwrite(elem->info, sizeof(char), infoSize, file);

        elem = elem->next;
      }
    }

    // ???????? ?????
    fclose(file);
    return 1;
}

int D_Load(Table *table)
{
    char *filename = getStr();
    // ???????? ????? ?? ??????
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("?????? ??? ???????? ????? %s\n", filename);
        return 0;
    }

    // ???????? ???? ????????? ?? ???????
    for (int i=0; i<SIZE; i++) {
      Item *elem = table->table[i];
      while (elem != NULL) {
        Item *next = elem->next;
        free(elem->info);
        free(elem);
        elem = next;
      }
      table->table[i] = NULL;
    }

    // ?????? ??????? ???????? ??????? ?? ????? ????????????? ???????
    while (1) {
        // ?????? ????? ? ?????? ?????? ????????
        int key, release;
        int n = fread(&key, sizeof(int), 1, file);
        if (n == 0) {
          break;
        }
        fread(&release, sizeof(int), 1, file);

        // ?????? ?????????? ?? ????????
        int infoSize;
        fread(&infoSize, sizeof(int), 1, file);
        char *info = (char *)malloc(sizeof(char) * infoSize);
        fread(info, sizeof(char), infoSize, file);

        // ??????? ???????? ? ???????
        insertElement(table, key, info);
    }

    // ???????? ?????
    fclose(file);
    return 1;
}

int insertElement(Table *table, int key, char *info)
{
    int index = hash(key);
    Item *curr = table->table[index];
    Item *prev = NULL;
    int release = 0;
    while (curr != NULL)
    {
        if (curr->key == key)
        {
            prev = curr;
            curr = curr->next;
        }
        else
        {
            break;
        }
    }
    if (prev == NULL && curr == NULL)
    {
        Item *new_item = (Item *)malloc(sizeof(Item));
        new_item->key = key;
        new_item->release = 1;
        new_item->info = info;
        new_item->next = NULL;
        table->table[index] = new_item;
        return 1;
    }
    else if (prev == NULL && curr != NULL)
    {
        Item *new_item = (Item *)malloc(sizeof(Item));
        new_item->key = key;
        new_item->release = curr->release + 1;
        new_item->info = info;
        new_item->next = curr;
        table->table[index] = new_item;
        return 1;
    }
    else if (prev != NULL && curr == NULL)
    {
        Item *new_item = (Item *)malloc(sizeof(Item));
        new_item->key = key;
        new_item->release = prev->release + 1;
        new_item->info = info;
        new_item->next = NULL;
        prev->next = new_item;
        return 1;
    }
    else
    {
        return 0;
    }
}