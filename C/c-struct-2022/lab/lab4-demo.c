#include <lab4-demo.h>

#define MIN_ENTRIES = 1

struct NFInsertStatus btree_nonfull_insert(struct Node *current_node, struct Entry *new_entry)
{
	struct NFInsertStatus status = {-1, 0, 0};
	// int status = -1;
	if (current_node->n_entries == 3)
	{
		// msg_error("Using internal insert with full node!");
		exit(1);
	}
	if (current_node->n_entries == 0)
	{
		// no entries so far - insert in first place
		current_node->keys[0] = new_entry;
		// TODO: should i allocate subtrees here?
		// only when we are inserting in non leaf...
		// there should be a check present uh
		// index, size
		status.a = 0;
		status.b = 1;
	}
	else if (current_node->n_entries == 1)
	{
		current_node->keys[1] = new_entry;
		if (current_node->keys[0]->key == new_entry->key)
		{
			return status;
		}
		if (current_node->keys[0]->key > new_entry->key)
		{
			byteswap((void *)current_node->keys[0], (void *)current_node->keys[1], sizeof(struct Entry *));
			status.a = 0;
		}
		else
		{
			status.a = 1;
		}
		status.b = 2;
	}
	else
	{
		// there are only two nodes
		if (current_node->keys[1]->key == new_entry->key)
		{
			return status;
		}
		if (current_node->keys[0]->key == new_entry->key)
		{
			return status;
		}
		current_node->keys[2] = new_entry;
		if (current_node->keys[1]->key > new_entry->key)
		{
			byteswap((void *)current_node->keys[1], (void *)current_node->keys[2], sizeof(struct Entry *));
			if (current_node->keys[0]->key > current_node->keys[1]->key)
			{
				byteswap((void *)current_node->keys[0], (void *)current_node->keys[1], sizeof(struct Entry *));
				status.a = 0;
			}
			else
			{
				status.a = 1;
			}
		}
		else
		{
			status.a = 2;
		}
		status.b = 3;
	}
	current_node->n_entries++;
	// this should return
	// {Success, Index, Size}
	status.status = 1;
	return status;
}

int Execute()
{
	const char *msgs[] = {"0. Quit", "1. Add", "2. Find ", "3. Find next node", "4. Remove elem", "5. Show table"};
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

	int (*fptr[])(BTree *) = {NULL, D_Add, D_Find, D_FindNext, D_Remove, D_Show};

	struct BTree *btree = btree_create();

	int rc;
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](btree))
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

int D_Add(BTree *btree)
{
	int keys[] = {12, 32, 45, 20, 24, 84, 96, 29, 35, 50, 63};
	// int keys[] = {12,32,45,20,24,84,96,29,35,50,39};
	for (int i = 0; i < 10; ++i)
	{
		// if (i == 158
		// || i == 65
		// || i == 112
		// || i == 58
		// || i == 68
		// || i == 120
		// || i == 183
		// || i == 211
		// || i == 249
		// || i == 160
		// || i == 190
		// || i == 215
		// || i == 220
		// || i == 238
		// || i == 258
		// || i == 288
		// || i == 240
		// || i == 241
		// || i == 250
		// if (i == 12
		//|| i == 32
		//|| i == 45
		//|| i == 20
		//  || i == 68
		//  || i == 120
		//  || i == 183
		//)

		char *data = malloc(10);
		strcpy(data, "testLine");
		int index = keys[i];
		btree_insert(btree->root, btree, index, data);
		printf("Inserted %d\n", index);
	}
	return 1;
}
int D_Find(BTree *btree)
{
	int i = 5;
	struct Entry *entry = btree_search(btree, i);
	if (NULL != entry)
	{
		btree_entry_print(entry);
	}
	else
	{
		printf("%d not found\n", i);
	}
	return 1;
}
int D_FindNext(BTree *table)
{
	return 1;
}
int D_Remove(BTree *btree)
{
	btree_delete(btree, 84);
	// delete_entry(btree,240);
	// remove_entry(btree, 190);
	// delete_element(btree,190);
	// delete_entry(btree, 240);
	// delete_key(btree,240);
	return 1;
}
int D_Show(BTree *btree)
{
	// for (int i = 0; i < 100; ++i) {
	// 	struct Entry* entry = btree_search(btree, i);
	// 	if (NULL != entry) {
	// 		btree_entry_print(entry);
	// 	} else {
	// 		printf("%d not found\n", i);
	// 	}
	// }
	print_btree_structure(btree);
	return 1;
}

struct BTree *btree_create()
{
	// struct BTree* btree = mknew(struct BTree);
	struct BTree *btree = ((struct BTree *)calloc(1, sizeof(struct BTree)));
	struct Node *root = btree_node_create();
	root->is_leaf = 1;
	root->parent = NULL;
	btree->root = root;
	btree->n_elems = 0;
	btree->n_saves = 0;
	return btree;
}
struct Node *btree_node_create()
{
	// struct Node* node = mknew(struct Node);
	struct Node *node = ((struct Node *)calloc(1, sizeof(struct Node)));
	node->keys = calloc(3, sizeof(struct Entry *));
	node->subtrees = calloc(4, sizeof(struct Node *));
	node->n_entries = 0;
	return node;
}

int btree_insert(struct Node *root, struct BTree *btree, int key, char *data)
{
	// struct Entry* new_entry = mknew(struct Entry);
	struct Entry *new_entry = ((struct Entry *)calloc(1, sizeof(struct Entry)));
	new_entry->key = key;
	new_entry->data = data;

	struct Node *current_node = root;

	while (!current_node->is_leaf || current_node->n_entries == 3)
	{
		// splitting while going down
		while (current_node->n_entries == 3)
		{
			current_node = btree_node_split(current_node, btree);
		}

		// searching
		if (current_node->n_entries == 1)
		{
			if (current_node->keys[0]->key == key)
			{
				// free_z(data);
				do
				{
					if (data)
					{
						free(data);
						(data) = 0;
					}
				} while (0);
				// free_z(new_entry);
				do
				{
					if (new_entry)
					{
						free(new_entry);
						(new_entry) = 0;
					}
				} while (0);
				return -1;
			}
			// TODO: null checks
			// can null be here? didn't we create needed subtrees during splitting?
			// null in subtree can be in leaf only and if it is a leaf
			// we do not enter this loop
			if (current_node->keys[0]->key > key)
			{
				nullcheck(current_node->subtrees[0], "subtree[0]");
				current_node = current_node->subtrees[0];
			}
			else
			{
				nullcheck(current_node->subtrees[1], "subtree[1]");
				current_node = current_node->subtrees[1];
			}
		}
		else if (current_node->n_entries == 2)
		{
			if (current_node->keys[0]->key > key)
			{
				nullcheck(current_node->subtrees[0], "subtree[0]");
				current_node = current_node->subtrees[0];
			}
			else if (current_node->keys[0]->key == key)
			{
				// free_z(data);
				// free_z(new_entry);
				do
				{
					if (data)
					{
						free(data);
						(data) = 0;
					}
				} while (0);
				do
				{
					if (new_entry)
					{
						free(new_entry);
						(new_entry) = 0;
					}
				} while (0);

				return -1;
			}
			else if (current_node->keys[1]->key > key)
			{
				nullcheck(current_node->subtrees[1], "subtree[1]");
				current_node = current_node->subtrees[1];
			}
			else if (current_node->keys[1]->key == key)
			{
				// free_z(data);
				// free_z(new_entry);
				do
				{
					if (data)
					{
						free(data);
						(data) = 0;
					}
				} while (0);
				do
				{
					if (new_entry)
					{
						free(new_entry);
						(new_entry) = 0;
					}
				} while (0);
				return -1;
			}
			else
			{
				nullcheck(current_node->subtrees[2], "subtree[2]");
				current_node = current_node->subtrees[2];
			}
		}
		else
		{
			// msg_error("Found unsplit node where should not!");
			// print_debug("n_entries: %d\n", current_node->n_entries);
			exit(1);
		}
	}
	// we found the leaf and it is current_node
	// we didn't split the leaf, we have to do it here
	//
	// 04.04, 3 AM: actually no, i need to split leaf in
	// while loop so there will be no need to reimplement
	// searching the actual leaf
	btree_nonfull_insert(current_node, new_entry);
	btree->n_elems++;
	return 1;
}

struct Node *btree_node_split(struct Node *current_node, struct BTree *btree)
{
	if (current_node->n_entries != 3)
	{
		// msg_error("Trying to split not full node");
		exit(1);
	}
	struct Entry *median = current_node->keys[1];
	if (NULL != current_node->parent)
	{
		// splitting non-parent node
		//
		// darn i'm using nonfull_insert routine to split.. should i make it
		// generic or create new one?
		//
		// cannot make it generic, will be too verbose for no reason for this usage
		// should nonfull_insert return something that
		// will help me to sort pointers?
		struct NFInsertStatus status = btree_nonfull_insert(current_node->parent, median);

		if (status.status == -1)
		{
			// msg_error("SameKey in split, this should not happen");
			exit(1);
		}
		int index = status.a;
		int size = status.b;

		struct Node *left = btree_node_create();
		struct Node *right = btree_node_create();

		left->is_leaf = current_node->is_leaf;
		right->is_leaf = current_node->is_leaf;

		left->subtrees[0] = current_node->subtrees[0];
		if (NULL == left->subtrees[0])
		{
			left->subtrees[0] = btree_node_create();
		}
		left->subtrees[0]->parent = left;

		left->subtrees[1] = current_node->subtrees[1];
		if (NULL == left->subtrees[1])
		{
			left->subtrees[1] = btree_node_create();
		}
		left->subtrees[1]->parent = left;

		left->n_subtrees = 2;

		right->subtrees[0] = current_node->subtrees[2];
		if (NULL == right->subtrees[0])
		{
			right->subtrees[0] = btree_node_create();
		}
		right->subtrees[0]->parent = right;

		right->subtrees[1] = current_node->subtrees[3];
		if (NULL == right->subtrees[1])
		{
			right->subtrees[1] = btree_node_create();
		}
		right->subtrees[1]->parent = right;

		right->n_subtrees = 2;

		// inserting in empty nodes
		btree_nonfull_insert(left, current_node->keys[0]);
		btree_nonfull_insert(right, current_node->keys[2]);

		// now we have two pointers that we need to insert in current_node->parent
		// btree_nonfull_insert should return index of insertion and the amount of elements
		// and lots of if elses.. i dunno how to make this more efficient, duh
		// this should be rewritten TODO, but currently I do not understand how
		struct Node *parent = current_node->parent;
		left->parent = parent;
		right->parent = parent;
		if (size == 3)
		{
			if (index == 0)
			{
				// inserted in the beginning
				parent->subtrees[3] = parent->subtrees[2];
				parent->subtrees[2] = parent->subtrees[1];
				parent->subtrees[1] = right;
				parent->subtrees[0] = left;
				parent->n_subtrees = 4;
			}
			else if (index == 1)
			{
				// inserted in the middle
				parent->subtrees[3] = parent->subtrees[2];
				parent->subtrees[2] = right;
				parent->subtrees[1] = left;
				parent->n_subtrees = 4;
			}
			else if (index == 2)
			{
				// inserted in the end
				parent->subtrees[3] = right;
				parent->subtrees[2] = left;
				parent->n_subtrees = 4;
			}
			else
			{
				// msg_error("Cannot handle such an index!");
				exit(1);
			}
			// yep i see the pattern, still dunno how to write it less verbose
		}
		else if (size == 2)
		{
			if (index == 0)
			{
				// inserted in the beginning
				parent->subtrees[2] = parent->subtrees[1];
				parent->subtrees[1] = right;
				parent->subtrees[0] = left;
				parent->n_subtrees = 3;
			}
			else if (index == 1)
			{
				parent->subtrees[2] = right;
				parent->subtrees[1] = left;
				parent->n_subtrees = 3;
			}
			else
			{
				// msg_error("Could not handle such index!");
				exit(1);
			}
		}
		else if (size == 1)
		{
			if (index != 0)
			{
				// msg_error("Could not handle such index!");
				exit(1);
			}
			parent->subtrees[0] = left;
			parent->subtrees[1] = right;
			parent->n_subtrees = 2;
		}
		else
		{
			// msg_error("Cannot handle this size! node_split");
			exit(1);
		}
		return parent;
	}
	else
	{
		// Not-so-obvious idea from CLRS - we just overwriting root node in tree strucutre,
		// assigning new root as a parent of previous one
		// and call split again inside. cool.
		struct Node *new_root = btree_node_create();
		btree->root = new_root;
		new_root->subtrees[0] = current_node;
		new_root->n_subtrees = 1;
		current_node->parent = new_root;
		struct Node *parent = btree_node_split(current_node, btree);
		return parent;
	}
	// TODO: memory is definitely leaking, we are not freeing splitted Node
}

struct Entry *btree_search(struct BTree *btree, int key)
{
	struct Node *current_node = btree->root;
	// rolling while true; continuing on new subtree, breaking
	// on find not found
	while (1)
	{
		int flag = 0;
		for (int i = 0; i < current_node->n_entries; ++i)
		{
			// print_debug("%s", "i < current_node->n_entries");
			if (current_node->keys[i]->key > key)
			{
				// new subtree
				if (current_node->is_leaf)
				{
					// there is no such key
					return NULL;
				}
				current_node = current_node->subtrees[i];
				flag = 1;
				break;
			}
			if (current_node->keys[i]->key == key)
			{
				// found
				return current_node->keys[i];
			}
		}
		if (!flag)
		{
			current_node = current_node->subtrees[current_node->n_entries];
			if (NULL == current_node)
			{
				return NULL;
			}
		}
	}
}

void btree_entry_print(struct Entry *entry)
{
	printf("Key: %d, data: %s\n", entry->key, entry->data);
}

void print_btree(Node *node, int level)
{
	if (node == NULL)
	{
		return;
	}

	for (int i = node->n_entries - 1; i >= 0; i--)
	{ // Изменим цикл для обратного порядка вывода
		if (!node->is_leaf)
		{
			print_btree(node->subtrees[i + 1], level + 1); // Изменим индекс для рекурсивного вызова
		}

		for (int j = 0; j < level; j++)
		{
			printf("\t");
		}
		printf("%d\n", node->keys[i]->key);
	}

	if (!node->is_leaf)
	{
		print_btree(node->subtrees[0], level + 1); // Изменим индекс для рекурсивного вызова
	}
}

void print_btree_structure(BTree *btree)
{
	printf("B-дерево структура:\n");
	print_btree(btree->root, 0);
}

int btree_delete(struct BTree *btree, int key)
{
	// step 1 - find the entry to delete
	// step 2 - if it is a leaf with n_entries >= 2, just delete the elem
	// step 3 - element is internal node, if left child has at least 2 keys, replace with
	// inorder predecessor. if right child has at least 2 keys, replace with inorder successor
	// both children has 2 keys - we merge
	// we also merging nodes that are 1<-1->1 on our way down using is_able_to_merge routine

	// travesing the tree searching for node
	struct Node *current_node = btree->root;
	int entry_index = -1;
	while (1)
	{
		if (current_node->n_entries == 0)
		{
			return -1;
		}

		if (current_node->keys[0]->key > key)
		{
			current_node = current_node->subtrees[0];
		}
		else if (current_node->keys[0]->key == key)
		{
			entry_index = 0;
			break;
		}
		else if (current_node->n_subtrees > 1 && current_node->keys[1]->key > key)
		{
			current_node = current_node->subtrees[1];
		}
		else if (current_node->n_subtrees > 1 && current_node->keys[1]->key == key)
		{
			entry_index = 1;
			break;
		}
		else if (current_node->n_subtrees > 2 && current_node->keys[2]->key > key)
		{
			current_node = current_node->subtrees[2];
		}
		else if (current_node->n_subtrees > 2 && current_node->keys[2]->key == key)
		{
			entry_index = 2;
			break;
		}
		else
		{
			current_node = current_node->subtrees[3];
		}
	}

	// now we now that at index index in current_node we have our elem. lets implement our logic
	if (current_node->is_leaf)
	{
		// we have a leaf here, two situations. situation 1 - n_entries 2 or 3, we are just deleting entry
		// situation 2 - n_entries is 1, we need rotation/merge
		if (current_node->n_entries > 1)
		{
			// easiest situation, just deleting
			if (current_node->n_entries == 3)
			{
				if (entry_index == 0)
				{
					current_node->keys[0] = current_node->keys[1];
					current_node->keys[1] = current_node->keys[2];
				}
				else if (entry_index == 1)
				{
					current_node->keys[1] = current_node->keys[2];
				}
			}
			else if (current_node->n_entries == 2)
			{
				if (entry_index == 0)
				{
					current_node->keys[0] = current_node->keys[1];
				}
			}
			current_node->n_entries--;
		}
		else
		{
			// checking whether there are siblings with 2 or more keys
		}
	}
	else
	{
	}
	////////////////////////////////////////////
	// 	struct Node *x;
	// 	struct Node *y;
	// 	struct Node *z;
	// 	int i;
	// 	int divider;

	// 	// Обработка корня
	// 	x = btree->root;
	// 	y = x->subtrees[0];
	// 	z = x->subtrees[1];
	// 	if (x->n_entries = 1)
	// 	{
	// 		if (x->subtrees[0]->n_entries = 1 && x->subtrees[1]->n_entries = 1)
	// 		{
	// 			y->keys[1] = x->keys[0];
	// 			y->keys[2] = z->keys[0];
	// 			y->subtrees[3] = z->subtrees[0];
	// 			y->subtrees[4] = z->subtrees[1];
	// 			y->parent = NULL;
	// 			y->n_entries =3;
	// 			y->n_subtrees=3;
	// 			btree->root = y;
	// 		}
	// 	}

	// 	x = btree->root;

	// 	while (x->is_leaf != 1)
	// 	{
	// 		i = search_index(x, key);
	// 		if (i < 0)
	// 		{
	// 			// Situacia 1: x - внутренний узел дерева, ключ k отсутствует в узле x
	// 			// y = getsubtree();
	// 			// Выбираем поддерево, которое должно содержать ключ k
	// 			if (x->n_entries = 1)
	// 			{
	// 				if (key < x->keys[0])
	// 				{
	// 					y = x->subtrees[0];
	// 					z = x->subtrees[1];
	// 					divider = 0;
	// 				}
	// 				else
	// 				{
	// 					y = x->subtrees[1];
	// 					z = NULL;
	// 				}
	// 			}
	// 			if (x->n_entries = 2)
	// 			{
	// 				if (key < x->keys[0])
	// 				{
	// 					y = x->subtrees[0];
	// 					z = x->subtrees[1];
	// 					divider = 0;
	// 				}
	// 				else
	// 				{
	// 					if (key < x->keys[1])
	// 					{
	// 						y = x->subtrees[1];
	// 						z = x->subtrees[2];
	// 						divider = 1;
	// 					}
	// 					else
	// 					{
	// 						y = x->subtrees[2];
	// 						z = NULL;
	// 					}
	// 				}
	// 			}
	// 			if (x->n_entries = 3)
	// 			{
	// 				if (key < x->keys[0])
	// 				{
	// 					y = x->subtrees[0];
	// 					z = x->subtrees[1];
	// 					divider = 0;
	// 				}
	// 				else
	// 				{
	// 					if (key < x->keys[1])
	// 					{
	// 						y = x->subtrees[1];
	// 						z = x->subtrees[2];
	// 						divider = 1;
	// 					}
	// 					else
	// 					{
	// 						if (key < x->keys[2])
	// 						{
	// 							y = x->subtrees[2];
	// 							z = x->subtrees[3];
	// 							divider = 2;
	// 						}
	// 						else
	// 						{
	// 							y = x->subtrees[3];
	// 							z = NULL;
	// 						}

	// 					}
	// 				}

	// 			}

	// 			if (y->n_entries = 1)
	// 			{
	// 				if (z != NULL)
	// 				{
	// 					if(z->n_entries = 2)
	// 					{
	// 						y->keys[1] = x->keys[divider];
	// 						x->keys[divider] = z->keys[0];
	// 						y->subtrees[2] = z->subtrees[0];
	// 						y->n_entries++;
	// 						y->n_subtrees++;
	// 						z->n_entries--;
	// 						z->n_subtrees--;
	// 						z->keys[0]=z->keys[1];
	// 						z->keys[1] = NULL;
	// 						z->subtrees[0] = z->subtrees[1];
	// 						z->subtrees[1] = NULL;

	// 					}
	// 					if(z->n_entries = 3)
	// 					{
	// 						y->keys[1] = x->keys[divider];
	// 						x->keys[divider] = z->keys[0];
	// 						y->subtrees[2] = z->subtrees[0];
	// 						y->n_entries++;
	// 						y->n_subtrees++;
	// 						z->n_entries--;
	// 						z->n_subtrees--;
	// 						z->keys[0]=z->keys[1];
	// 						z->keys[1]=z->keys[2];
	// 						z->keys[2] = NULL;
	// 						z->subtrees[0] = z->subtrees[1];
	// 						z->subtrees[1] = z->subtrees[2];
	// 						z->subtrees[2] = NULL;

	// 					}
	// 				}

	// 			}
	// 			else if()

	// 		}
	// 		else
	// 		{
	// 			// Situacia 2
	// 		}
	// 	}

	// 	if (x->is_leaf = 1)
	// 	{
	// 		i = search_index(x, key);
	// 		if (i > 0)
	// 		{
	// 			delete_entry_from_node(x, key);
	// 		}
	// 		else
	// 		{
	// 			return -1;
	// 		}
	// 	}

	// 	return 1;
	// }
	// int search_index(Node *node, int key)
	// {
	// 	int i = 0;
	// 	while (i < node->n_entries && key > node->keys[i]->key)
	// 	{
	// 		i++;
	// 	}
	// 	return i;
}

// void delete_entry_from_node(Node *node, int key)
// {
// 	int i = 0;
// 	while (i < node->n_entries && node->keys[i]->key < key)
// 	{
// 		i++;
// 	}

// 	if (i < node->n_entries && node->keys[i]->key == key)
// 	{
// 		free(node->keys[i]->data);
// 		free(node->keys[i]);

// 		for (int j = i; j < node->n_entries - 1; j++)
// 		{
// 			node->keys[j] = node->keys[j + 1];
// 		}

// 		node->n_entries--;
// 	}
// }

//_______________

