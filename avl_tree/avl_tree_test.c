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
	node_t *z = search(*root, key);

	assert(z != NULL);

	avl_delete(root, z);
}

void insert_test()
{
	node_t *root = NULL;

	insert(&root, 11);
	insert(&root, 2);
	insert(&root, 14);
	insert(&root, 1);
	insert(&root, 7);
	insert(&root, 5);
	insert(&root, 8);
	insert(&root, 15);
	insert(&root, 4);

	printf("insert_test....\n");
	printf("creating tree: ");
	preorder_walk(root);
	printf("\n");
}

void delete_test(int key)
{
	node_t *root = NULL;

	insert(&root, 11);
	insert(&root, 2);
	insert(&root, 14);
	insert(&root, 1);
	insert(&root, 7);
	insert(&root, 5);
	insert(&root, 8);
	insert(&root, 15);
	insert(&root, 4);

	printf("delete_test....\n");
	printf("original tree: ");
	preorder_walk(root);
	printf("\n");

	printf("deleting %d:   ", key);
	delete(&root, key);
	preorder_walk(root);
	printf("\n");
}

int main(int argc, void **argv)
{
	int key = (int)atoi(argv[1]);

	insert_test();
	printf("\n");
	delete_test(key);	
	return 0;
}
