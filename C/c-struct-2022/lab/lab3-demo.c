#include <lab3-demo.h>

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
        if (n == 0)
            rc = 0;
    } while (rc < 0 || rc >= N);
    return rc;
}

int Execute()
{
    const char *msgs[] = {"0. Quit", "1. Add","2. Find", "3. Load"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
    
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Load};
    
    Table table = {0, 0, NULL, NULL};
    int rc;

    if (D_Load(&table) == 0)
        return 1;
    
    while (rc = dialog(msgs, NMsgs))
        if (!fptr[rc](&table))
            break;
    D_Save(&table);
    printf("That's all. Bye!\n");
    delTable(&table);
    return 0;
}

int D_Add(Table *ptab)
{
    int k, rc, n;
    char *info = NULL;
    printf("Enter key: -->");
    n = getInt(&k);
    if (n == 0)
        return 0;
    printf("Enter info:\n");
    info = getStr();
    if (info == NULL)
        return 0;
    rc = insert(ptab, k, info);
    free(info);
    printf("%s: %d\n", "errmsgs[rc]", k);
    return 1;
}

int insert(Table *ptab, int k, char *str)
{
    if (find(*ptab, k) >= 0)
        return 1;
    if (ptab->n >= ptab->SZ)
        return 2;
    ptab->first[ptab->n].key = k;
    ptab->first[ptab->n].len = strlen(str) + 1;
    fseek(ptab->fd, 0, SEEK_END);
    ptab->first[ptab->n].offset = ftell(ptab->fd);
    fwrite(str, sizeof(char), ptab->first[ptab->n].len, ptab->fd);
    ++(ptab->n);
    return 0;
}

int D_Find(Table *ptab)
{
    char *info = NULL;
    int k, n, i;
    puts("Enter key: -->");
    n = getInt(&k);
    if (n == 0)
        return 0;
    info = findInfo(*ptab, k);
    if (info)
    {
        printf("key = %d, info = \"%s\"\n", k, info);
        free(info);
    }
    else
        printf("Item %d was not found\n", k);
    return 1;
}

int find(Table ptab, int k)
{
    int i = 0;
    for (; i < ptab.n; ++i)
        if (ptab.first[i].key == k)
            return i;
    return -1;
}

char *findInfo(Table ptab, int k)
{
    char *info = NULL;
    int i = find(ptab, k);
    if (i >= 0)
    {
        info = (char *)malloc(ptab.first[i].len);
        fseek(ptab.fd, ptab.first[i].offset, SEEK_SET);
        fread(info, sizeof(char), ptab.first[i].len, ptab.fd);
    }
    return info;
}

int load(Table *ptab, char *fname)
{
    fopen(fname, "r+b");
    if (ptab->fd == NULL)
        return 0;
    fread(&ptab->SZ, sizeof(int), 1, ptab->fd);
    ptab->first = (Item *)calloc(ptab->SZ, sizeof(Item));
    fread(&ptab->n, sizeof(int), 1, ptab->fd);
    fread(ptab->first, sizeof(Item), ptab->n, ptab->fd);
    return 1;
}

int create(Table *ptab, char *fname, int sz)
{
    ptab->SZ = sz;
    ptab->n = 0;
    if (fopen(fname, "w+b") != 0)
    {
        ptab->first = NULL;
        return 0;
    }

    ptab->first = (Item *)calloc(ptab->SZ, sizeof(Item));

    fwrite(&ptab->SZ, sizeof(int), 1, ptab->fd);

    fwrite(&ptab->n, sizeof(int), 1, ptab->fd);

    fwrite(ptab->first, sizeof(Item), ptab->SZ, ptab->fd);
    return 1;
}

int D_Load(Table *ptab)
{
    int SZ;
    char *fname = NULL;
    printf("Enter file name: --> ");
    fname = getStr();
    if (fname == NULL)
        return 0;
    if (load(ptab, fname) == 0)
    {
        printf("Enter possible vector size: -->");
        if (getInt(&SZ) == 0)
            return 0;
        create(ptab, fname, SZ);
    }
    free(fname);
    return 1;
}

int save(Table *ptab)
{
    fseek(ptab->fd, sizeof(int), SEEK_SET);
    fwrite(&ptab->n, sizeof(int), 1, ptab->fd);
    fwrite(ptab->first, sizeof(Item), ptab->n, ptab->fd);
    fclose(ptab->fd);
    ptab->fd = NULL;
    return 1;
}

int getInt(int *a)
{
    int n;
    do {
        n = scanf("%d", a);
        if (n < 0)
            return 0;
        if (n == 0) {
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
    while (flag > 0){
        char *buff = malloc(200 * sizeof(char));
        flag = scanf("%199[^\n]", buff);
        if (flag == EOF) {
            input = NULL;
        } else if (flag == 0) {
            scanf("%*c");
        } else {
            int buffLen = strlen(buff);
            input = realloc(input, (len + buffLen) * sizeof(char));
            for (int i = 0; i < buffLen; i++) {
                input[len + i] = buff[i];
            }
            len += buffLen;
        }
        free(buff);
    }
    if (flag != - 1) {
        input = realloc(input, (len + 1) * sizeof(char));
        input[len] = '\0';
    }
    return input;
}

int delTable(Table *ptab)
{
    return 1;
}

int D_Save(Table *ptab)
{
    return 1;
}