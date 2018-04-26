#include "rb_tree.h"

void
node_init(node_t *node, node_t *parent, node_t *left, node_t *right, int key)
{
	node->parent = parent;
	node->left = left;
	node->right = right;
	node->key = key;
}

int
main()
{
	node_t *root;
	node_t *node2 = malloc(sizeof(node_t));
	node_t *node1 = malloc(sizeof(node_t));
	node_t *node3 = malloc(sizeof(node_t));
	node_t *node4 = malloc(sizeof(node_t));
	node_t *node5 = malloc(sizeof(node_t));

	root = node2;
	node_init(node2, nil_p, node1, node4, 2);
	node_init(node1, root, nil_p, nil_p, 1);
	node_init(node4, root, node3, node5, 4);
	node_init(node3, node4, nil_p, nil_p, 3);
	node_init(node5, node4, nil_p, nil_p, 5);

	printf("original tree:         ");
	preorder_walk(root);
	printf("\n");

	left_rotate(&root, node2);
	printf("after left_rotate(2):  ");
	preorder_walk(root);
	printf("\n");

	right_rotate(&root, node4);
	printf("after right_rotate(4): ");
	preorder_walk(root);
	printf("\n");

	return 0;
}
