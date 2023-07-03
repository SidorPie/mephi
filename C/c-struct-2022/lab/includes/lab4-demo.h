#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct NFInsertStatus {
	int status;
	int a;
	int b;
} NFInsertStatus;

typedef struct BTree
{
    struct Node *root;
    int n_elems;
    int n_saves;
} BTree;

typedef struct Entry
{
    int key;
    char *data;
} Entry;

typedef struct Node
{
    int is_leaf;
    struct Entry **keys;
    struct Node **subtrees;
    struct Node *parent;
    int n_entries;
    int n_subtrees;
} Node;

// bytewise swap. stolen, probably works fine
#define byteswap(a, b, size)                \
	do {                                \
		size_t __size = (size);     \
      		char *__a = (a), *__b = (b);\
      		do {                        \
          		char __tmp = *__a;  \
          		*__a++ = *__b;      \
          		*__b++ = __tmp;     \
        	} while (--__size > 0);     \
    	} while (0)

static inline void nullcheck(void* ptr, const char* name) {
	if (NULL == ptr) {
		printf("[!] %s is null", name);
	}
}

int Execute();
int dialog(const char *msgs[], int N);
int getInt(int *a);

int D_Add(BTree *table);
int D_Find(BTree *table);
int D_FindNext(BTree *table);
int D_Remove(BTree *table);
int D_Show(BTree *table);

int btree_insert(struct Node* root, struct BTree* btree, int key, char* data);
struct BTree* btree_create();
struct Node* btree_node_create();
struct Node* btree_node_split(struct Node* current_node, struct BTree* btree);
struct Entry* btree_search(struct BTree* btree, int key);
void btree_entry_print(struct Entry* entry);

void print_btree(Node *node, int level);
void print_btree_structure(BTree *btree);

int btree_delete(struct BTree* btree, int key);
int search_index(Node *node, int key);

//void delete_entry(BTree* tree, Node* node, Entry* entry);
//void delete_key(BTree* tree, int key);