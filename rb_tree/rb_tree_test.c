#include "rb_tree.h"

void insert(node_t **root, int key)
{
	node_t *z = malloc(sizeof(node_t));

	z->key = key;
	rb_insert(root, z);
}

int main()
{
	node_t *root = nil_p;

	insert(&root, 11);
	insert(&root, 2);
	insert(&root, 14);
	insert(&root, 1);
	insert(&root, 7);
	insert(&root, 5);
	insert(&root, 8);
	insert(&root, 15);
	insert(&root, 4);
	preorder_walk(root);
	printf("\n");

	return 0;
}
