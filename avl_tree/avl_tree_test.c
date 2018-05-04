#include "avl_tree.h"

node_t *search(node_t *root, int key)
{
	node_t *x = root;

	while (x != NULL) {
		if (x->key == key) {
			return x;
		} else if (x->key < key) {
			x = x->right;
		} else {
			x = x->left;
		}
	}

	return x;
}

void insert(node_t **root, int key)
{
	node_t *z = malloc(sizeof(node_t));

	z->key = key;
	avl_insert(root, z);
}

void delete(node_t **root, int key)
{
}

void insert_test()
{
	node_t *root = NULL;

	insert(&root, 11);
#if 0
	insert(&root, 2);
	insert(&root, 14);
	insert(&root, 1);
	insert(&root, 7);
	insert(&root, 5);
	insert(&root, 8);
	insert(&root, 15);
	insert(&root, 4);
#endif
	preorder_walk(root);
	printf("\n");
}

void delete_test()
{
}

int main()
{
	insert_test();	
	delete_test();	
	return 0;
}
