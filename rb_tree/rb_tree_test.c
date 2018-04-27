#include "rb_tree.h"

node_t *search(node_t *root, int key)
{
	node_t *x = root;

	while (x != nil_p) {
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
	rb_insert(root, z);
}

void delete(node_t **root, int key)
{
	node_t *z = search(*root, key);

	if (z == nil_p) {
		printf("%s: can't find node %d\n", __func__, key);
		assert(1);
	}

	rb_delete(root, z);
}

void insert_test()
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
}

void delete_test()
{
	node_t *root = nil_p;

	printf("rb tree delete test...\n");
	printf("    create rb tree: ");

	insert(&root, 41);
	insert(&root, 38);
	insert(&root, 31);
	insert(&root, 12);
	insert(&root, 19);
	insert(&root, 8);

	preorder_walk(root);
	printf("\n");

	printf("	delete node 12:  ");
	delete(&root, 12);
	preorder_walk(root);
	printf("\n");

}

int main()
{
	// insert_test();	
	delete_test();	
	return 0;
}
